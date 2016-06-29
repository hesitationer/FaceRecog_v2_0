
// FRDemoDlg.h : ͷ�ļ�
//

#pragma once


#include "Resource.h"
#include "EnrollDlg.h"
#include "TrainDlg.h"
#include "RecogDlg.h"
#include "../FaceMngr/FaceMngr.h"

#pragma comment(lib, "../bin/tools.lib")
#pragma comment(lib, "../bin/FaceMngr.lib")
//#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib") // will cause "�޷�������ϵͳ"


// CFRDemoDlg �Ի���������
class CFRDemoDlg : public CDialog
{
// ����
public:
	CFRDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FRDemo_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//////////////////////////////////////////////////////////////////////////
	// User defined
public:
	bool InitSys();
	UINT ShowFrame();
	void ReadIni();


	CWinThread	*m_thrdFrame;
	bool		m_bFrameStarted;
	CEnrollDlg	m_dlgEnroll;
	CTrainDlg	m_dlgTrain;
	CRecogDlg	m_dlgRecog;
	IplImage	*m_frame; // �洢����ͷ�ĵ��Ļ���

	vector<LPTSTR>	m_dllList;

// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	 BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedEnroll();
	afx_msg void OnBnClickedTrain();
	afx_msg void OnBnClickedRecog();
	afx_msg void OnBnClickedExport();
};

UINT ShowFrameProc(LPVOID pParam);
UINT InitMngrProc(LPVOID pParam);