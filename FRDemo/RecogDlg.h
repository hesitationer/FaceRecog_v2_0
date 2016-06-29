#pragma once

#include "../FaceMngr/FaceMngr.h"

// CRecogDlg �Ի���ʶ�����

class CRecogDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecogDlg)

public:
	CRecogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	 ~CRecogDlg();

	//////////////////////////////////////////////////////////////////////////
	// user defined

	BOOL OnInitDialog();

	UINT ShowMatch();
	void ShowMatchRun();
	void InitWindows(); // ��ʼ��OpenCVͼ����ʾ���ڣ���Ƕ��Ի���

	void Release();


	bool		m_bMatchStarted;
	bool		m_bFoundFace;

	CWinThread	*m_thrdMatch;

	IplImage	*m_frame;
	CvMat		*faceImg8;
	IplImage	*noface, *resss; // ������ͼ�����ڸ����û�һЩ��Ϣ

	CvSize		faceSz;
	SMatch		matchInfo;
	CString		strFd;

	BOOL		m_bUseBuf; // ���ȶ�ͫ�׶�λ����ѡ��
	CvSize		showSz;

// �Ի�������
	enum { IDD = IDD_RECOG };

protected:
	 void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedPicRecog();
	afx_msg void OnBnClickedUsebuf();
	//afx_msg void OnNMClickFilepath(NMHDR *pNMHDR, LRESULT *pResult);

};

UINT ShowMatchProc(LPVOID pParam);
