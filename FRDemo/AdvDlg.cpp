// AdvDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FRDemo.h"
#include "AdvDlg.h"
#include "ProjDefs.h"
#include "Utils.h"

// CAdvDlg �Ի���

IMPLEMENT_DYNAMIC(CAdvDlg, CDialog)

CAdvDlg::CAdvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvDlg::IDD, pParent)
{

}

CAdvDlg::~CAdvDlg()
{
}

void CAdvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdvDlg, CDialog)
	ON_BN_CLICKED(IDC_CLEAR_LIB, &CAdvDlg::OnBnClickedClearLib)
END_MESSAGE_MAP()


// CAdvDlg ��Ϣ�������

void CAdvDlg::OnBnClickedClearLib()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_faceMngr->ClearList();
	//g_lstName.clear();
	::AfxMessageBox("OK.", MB_OK | MB_ICONINFORMATION);
}

BOOL CAdvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	return TRUE;
}