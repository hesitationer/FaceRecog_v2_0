#pragma once


// CTrainDlg �Ի���ѵ������

class CTrainDlg : public CDialog
{
	DECLARE_DYNAMIC(CTrainDlg)

public:
	CTrainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	 ~CTrainDlg();

// �Ի�������
	enum { IDD = IDD_TRAIN };

protected:
	 void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bHasNormed;
	BOOL m_bSave2Model;
	CString m_strTrainFd;
	CString m_strTrainFilelist;

	BOOL OnInitDialog();
	afx_msg void OnBnClickedBrowseTrainfd();
	afx_msg void OnBnClickedImportMat();
	afx_msg void OnBnClickedFromlist();
};
