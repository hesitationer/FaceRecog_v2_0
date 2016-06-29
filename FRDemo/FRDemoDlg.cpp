
// FRDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FRDemo.h"
#include "FRDemoDlg.h"
#include "Utils.h"
#include "ProjDefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFaceMngr	*g_faceMngr;
CWebCam		g_webcam;
bool		g_bHasWebcam;

CString		g_strPicPath, g_strFacePath;
CString		g_strDefMat, g_strDefModel;


bool CFRDemoDlg::InitSys()
{
	RECT rc;
	GetWindowRect(&rc);
	SetWindowPos(NULL, rc.left, 100, 0,0, SWP_NOSIZE | SWP_NOZORDER);

	ReadIni();
	g_bHasWebcam = g_webcam.Init();
	setlocale(LC_ALL, ""); // set locale automatically

	if (g_bHasWebcam)
	{
		CWnd *pWnd = GetDlgItem(IDC_VIDEO);
		CvSize frameSz = g_webcam.GetFrameSize(), showSz = frameSz;
		if (showSz.height != 240) // (240,320) is the preset show size, if frameSz != (240,320), then adjust showSz
			showSz *= (240.0/showSz.height);
		if (showSz.width > 320)
			showSz *= (320.0/showSz.width);
		EmbedCvWindow(pWnd->m_hWnd, "video", showSz.width, showSz.height);
		pWnd->SetWindowPos(NULL, 0,0, showSz.width+10, showSz.height+10, SWP_NOZORDER | SWP_NOMOVE);

		m_frame = cvCreateImage(frameSz, IPL_DEPTH_8U, 3);
		m_bFrameStarted = true;
		m_thrdFrame = ::AfxBeginThread(ShowFrameProc, this);
	}

	m_dlgTrain.m_strTrainFd = g_strPicPath;
	::AfxBeginThread(InitMngrProc, this);
	return true;
}

void CFRDemoDlg::ReadIni()
{
	TCHAR progname[MAX_PATH + 1];
	GetModuleFileName( NULL, progname, MAX_PATH );
	CString curFn = progname;
	int idx = curFn.ReverseFind('\\');
	CString fn = curFn.Left(idx) + "\\config.ini"; // there should be a '.\\' in file name

	CString sn1 = "folders", sn2 = "files", sn3 = "modules";
	::GetPrivateProfileString(sn1, "default_pic_path", DEF_PIC_PATH, 
		g_strPicPath.GetBuffer(MAX_PATH), MAX_PATH, fn);
	g_strPicPath.ReleaseBuffer();
	::GetPrivateProfileString(sn2, "default_frmat", "", 
		g_strDefMat.GetBuffer(MAX_PATH), MAX_PATH, fn);
	g_strDefMat.ReleaseBuffer();
	::GetPrivateProfileString(sn2, "default_frmodel", "", 
		g_strDefModel.GetBuffer(MAX_PATH), MAX_PATH, fn);
	g_strDefModel.ReleaseBuffer();
	g_strFacePath = g_strPicPath;
	g_strFacePath.TrimRight('\\');
	g_strFacePath += '\\';
	g_strFacePath += FACE_REL_PATH;

	for (int i = 0;i<4;i++)
	{
		TCHAR *a = new TCHAR[MAX_PATH];
		m_dllList.push_back(a);
	}

	::GetPrivateProfileString(sn3, "FaceAlign_dll", "", m_dllList[0], MAX_PATH, fn);
	::GetPrivateProfileString(sn3, "LightPrep_dll", "", m_dllList[1], MAX_PATH, fn);
	::GetPrivateProfileString(sn3, "FaceFeature_dll", "", m_dllList[2], MAX_PATH, fn);
	::GetPrivateProfileString(sn3, "Subspace_dll", "", m_dllList[3], MAX_PATH, fn);
}

UINT CFRDemoDlg::ShowFrame()
{
	while(m_bFrameStarted)
	{
		g_webcam.GetFrame(m_frame);
		cvShowImage("video", m_frame);
		cvWaitKey(1);
		Sleep(100);
	}

	return 0;
}

void CFRDemoDlg::OnBnClickedEnroll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_dlgEnroll.DoModal();
}

void CFRDemoDlg::OnBnClickedTrain()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nRet = m_dlgTrain.DoModal();
	ShowWindow(SW_SHOWNORMAL);
	if (nRet == IDOK)
	{
		SetDlgItemText(IDC_STATE, "ѵ����...");
		tic();//double t = (double)cvGetTickCount();
		vector<SFInfo> paths;
		CString rootFd;

		if (! m_dlgTrain.m_strTrainFilelist.IsEmpty())
		{
			rootFd = "";
			::GenFileListFromFile(m_dlgTrain.m_strTrainFilelist, paths);
		}
		else if (! m_dlgTrain.m_strTrainFd.IsEmpty())
		{
			rootFd = m_dlgTrain.m_strTrainFd;
			::GenFileList(rootFd, paths);
		}

		DWORD flag = FM_DO_NOT_NORM;
		if (m_dlgTrain.m_bSave2Model > 0) flag |= FM_TRAIN_SAVE2MODEL;
		if (m_dlgTrain.m_bHasNormed == 0) flag |= (FM_DO_NORM | FM_SAVE_NORM_FACE);
		bool ret = g_faceMngr->Train(rootFd, paths, flag);

		SetDlgItemText(IDC_STATE, "");
		if (ret)
		{
			double t1 = toc(); // ((double)cvGetTickCount() - t) / ((double)cvGetTickFrequency()*1e6);
			CString msg;
			msg.Format("����%d�˵�%d��ͼƬ�μ�ѵ�����õ�����%dά����ά��Ϊ%dά��ѵ����ɣ���ʱ%fs��",
				g_faceMngr->m_trainclsNum, g_faceMngr->m_trainNum, 
				g_faceMngr->m_featureSz, g_faceMngr->m_modelSz, t1);
			::AfxMessageBox(msg, MB_OK | MB_ICONINFORMATION);
		}
		paths.clear();
	}
}

void CFRDemoDlg::OnBnClickedRecog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (! g_faceMngr->HasTrained())
	{
		::AfxMessageBox("����ѵ����");
		return;
	}
	if (g_faceMngr->GetModelCount() == 0)
	{
		::AfxMessageBox("����ע�ᡣ");
		return;
	}
	m_dlgRecog.DoModal();
	ShowWindow(SW_SHOWNORMAL);
}

void CFRDemoDlg::OnBnClickedExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bool ret1 = false;
	//setlocale(LC_ALL, "Chinese-simplified"); //�������Ļ���

	if (g_faceMngr->HasTrained())
	{
		ret1 = true;
		CFileDialog dlgFile(FALSE, "frmat", "test", 
			OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT , "����ʶ������ļ� (*.frmat)|*.frmat||");
		if (dlgFile.DoModal() == IDOK)
		{
			CString path = dlgFile.GetPathName();
			ofstream os(path, ios::binary);
			if (!os)
			{
				::AfxMessageBox(CString(path)+"���޷���ȡ��");
				return;
			}
			else
			{
				g_faceMngr->WriteMatToFile(os);
				os.close();
			}
		}
	}

	if (g_faceMngr->GetModelCount() > 0)
	{
		ret1 = true;
		CFileDialog dlgFile1(FALSE, "frmodel", "test", 
			OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT, "����ģ���ļ� (*.frmodel)|*.frmodel||");
		if (dlgFile1.DoModal() == IDOK)
		{
			CString path = dlgFile1.GetPathName();
			ofstream os(path, ios::binary);
			if (!os)
			{
				::AfxMessageBox(CString(path)+"���޷���ȡ��");
				return;
			}
			else
			{
				g_faceMngr->WriteModelToFile(os);
				os.close();
			}
		}
	}

	// setlocale(LC_ALL, "C");// ��ԭ

	if ( !ret1 )
	{
		::AfxMessageBox("ûʲôҪ��ģ�");
		return;
	}

	::AfxMessageBox("������ɡ�\n ÿ������ģ���ļ���Ӧ����Ψһ��Ӧ�ľ����ļ�������ʱ�벻ҪŪ�졣", MB_OK | MB_ICONINFORMATION);
}

void CFRDemoDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//_CrtDumpMemoryLeaks(); // ��������ͷź���֮ǰ�Ͱ����пռ��ͷŵ�����������Memory leak!
	for (int i = 0;i < 4;i++)
	{
		delete []m_dllList[i];
	}
	if (g_bHasWebcam)
	{
		m_bFrameStarted = false;
		if (m_thrdFrame) ::WaitForSingleObject(m_thrdFrame->m_hThread, 1000);
		cvReleaseImage(&m_frame);
		cvDestroyWindow("video");
	}
	delete g_faceMngr;
	
	setlocale(LC_ALL, "C"); // return locale to "C"
	
	OnCancel();
}

UINT ShowFrameProc( LPVOID pParam )
{
	CFRDemoDlg *pDlg = (CFRDemoDlg *)pParam;
	return pDlg->ShowFrame();
}

UINT InitMngrProc( LPVOID pParam )
{
	CFRDemoDlg *pDlg = (CFRDemoDlg*)pParam;
	g_faceMngr = new CFaceMngr;

	CString msg;
	
	if (! g_faceMngr->InitMngr(pDlg->m_dllList)) // ��ʼ��ʧ��
	{
		CFRDemoDlg *pdlg = (CFRDemoDlg *)pParam;
		pdlg->GetDlgItem(IDC_ENROLL)->EnableWindow(FALSE);
		pdlg->GetDlgItem(IDC_TRAIN)->EnableWindow(FALSE);
		pdlg->GetDlgItem(IDC_RECOG)->EnableWindow(FALSE);
		pdlg->GetDlgItem(IDC_EXPORT)->EnableWindow(FALSE);
		return 1;
	}

	if (! g_strDefMat.IsEmpty())
	{
		ifstream is(g_strDefMat, ios::binary);
		if (!is)
			::AfxMessageBox(g_strDefMat + "���޷���ȡ��");
		else
		{
			if (! g_faceMngr->ReadMatFromFile(is)) 
				::AfxMessageBox("Ĭ��frmat�ļ���ȡʧ�ܡ�");
			is.close();
		}
	}

	if (! g_strDefModel.IsEmpty())
	{
		ifstream is(g_strDefModel, ios::binary);
		if (!is)
			::AfxMessageBox(g_strDefModel + "���޷���ȡ��");
		else
		{		
			int readNum = g_faceMngr->ReadModelFromFile(is);
			CString msg;
			msg.Format("������%d��ģ�壬����%d��ģ�塣\n��ע��ģ����ӿռ併ά����Ķ�Ӧ��", 
				readNum, g_faceMngr->GetModelCount());
			::AfxMessageBox(msg, MB_OK | MB_ICONINFORMATION);
			is.close();
		}
	}

	// setlocale(LC_ALL, "C");// ��ԭ
	return 0;
}