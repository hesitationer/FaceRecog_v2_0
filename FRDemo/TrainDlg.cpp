// TrainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FRDemo.h"
#include "TrainDlg.h"
#include "ProjDefs.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CTrainDlg �Ի���

IMPLEMENT_DYNAMIC(CTrainDlg, CDialog)

CTrainDlg::CTrainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrainDlg::IDD, pParent)
	, m_bHasNormed(TRUE)
	, m_bSave2Model(TRUE)
{
}

CTrainDlg::~CTrainDlg()
{
}

void CTrainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_NORMED, m_bHasNormed);
	DDX_Check(pDX, IDC_SAVE2MODEL, m_bSave2Model);
	DDX_Text(pDX, IDC_TRAINFD, m_strTrainFd);
}


BEGIN_MESSAGE_MAP(CTrainDlg, CDialog)
	ON_BN_CLICKED(IDC_BROWSE_TRAINFD, &CTrainDlg::OnBnClickedBrowseTrainfd)
	ON_BN_CLICKED(IDC_IMPORT_MAT, &CTrainDlg::OnBnClickedImportMat)
	ON_BN_CLICKED(IDC_FROMLIST, &CTrainDlg::OnBnClickedFromlist)
END_MESSAGE_MAP()

BOOL CTrainDlg::OnInitDialog()
{
	m_strTrainFilelist = "";
	m_strTrainFd = "";
	CDialog::OnInitDialog();
	return TRUE;
}

// CTrainDlg ��Ϣ�������

void CTrainDlg::OnBnClickedBrowseTrainfd()
{
	//TCHAR str[501];
	//::GetCurrentDirectory(500, str);
	//m_strTrainFd = m_strTrainFd;
	bool ret = SelDirectory(NULL, "ѡ��ѵ��ͼƬ�����ļ���", m_strTrainFd);
	if (!ret) return;
	UpdateData(FALSE);
}

void CTrainDlg::OnBnClickedImportMat()
{
	CFileDialog dlgFile(TRUE, "frmat", "test", 
		OFN_NOCHANGEDIR | OFN_HIDEREADONLY, 
		"����ʶ������ļ� (*.frmat)|*.frmat||");
	if (dlgFile.DoModal() == IDOK)
	{
		CString path = dlgFile.GetPathName();
		//setlocale(LC_ALL, "Chinese-simplified"); //�������Ļ���
		ifstream is(path, ios::binary);
		if (!is)
		{
			::AfxMessageBox(CString(path)+"���޷���ȡ��");
			return;
		}

		if (g_faceMngr->ReadMatFromFile(is))
			::AfxMessageBox("������ɡ�\n��ע��ģ����ӿռ併ά����Ķ�Ӧ��", MB_OK | MB_ICONINFORMATION);

		is.close();
		// setlocale(LC_ALL, "C");// ��ԭ
	}
	OnCancel();
}

void CTrainDlg::OnBnClickedFromlist()
{
	//setlocale(LC_ALL, "Chinese-simplified"); //�������Ļ���

	CFileDialog fileDlg(TRUE, "txt", 0, OFN_NOCHANGEDIR | OFN_HIDEREADONLY,
		"image file list (*.txt)|*.txt||");
	int ret = fileDlg.DoModal();
	if (ret != IDOK)
	{
		// setlocale(LC_ALL, "C");// ��ԭ
		return;
	}
	m_strTrainFilelist = fileDlg.GetPathName();
	// setlocale(LC_ALL, "C");// ��ԭ
	OnOK();

}
