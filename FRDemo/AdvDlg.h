#pragma once


// CAdvDlg �Ի���ע�����->�߼�

class CAdvDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdvDlg)

public:
	CAdvDlg(CWnd* pParent = NULL);   // ��׼���캯��
	 ~CAdvDlg();

// �Ի�������
	enum { IDD = IDD_ADV };

protected:
	 void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedClearLib();
	BOOL OnInitDialog();
};
