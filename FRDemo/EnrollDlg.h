#pragma once

#include "../FaceMngr/FaceMngr.h"
#include "AdvDlg.h"

// CEnrollDlg �Ի���ע�����

class CEnrollDlg : public CDialog
{
	DECLARE_DYNAMIC(CEnrollDlg)

public:
	CEnrollDlg(CWnd* pParent = NULL);   // ��׼���캯��
	~CEnrollDlg();

	//////////////////////////////////////////////////////////////////////////
	// user defined

	BOOL OnInitDialog();
	UINT ShowFace();
	void Release();

	void SaveShootPics(bool bSave2Model);

	bool		m_bFaceStarted;
	bool		m_bFoundFace;
	CWinThread	*m_thrdFace;

	IplImage	*m_frame;
	CvMat		*faceImg8;

	int			m_nShootNum;
	CvSize		faceSz;
	IplImage	*m_noface;

	CList<IplImage *>	m_lstPic;
	CList<CvMat *>		m_lstFace;
	
	CString		m_strName;
	BOOL		m_bSaveSmallImg;
	CAdvDlg		m_dlgAdv;
	CvSize		showSz;
// �Ի�������
	enum { IDD = IDD_ENROLL };

protected:
	 void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedShoot();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedEnrollPic(); // ���Ѿ�ѵ����ǰ����
	afx_msg void OnBnClickedImportModels();
	afx_msg void OnBnClickedAdv();
	afx_msg void OnBnClickedDelShoot();
};

UINT ShowFaceProc(LPVOID pParam);
