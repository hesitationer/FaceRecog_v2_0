
// FRDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CFRDemoApp:
// �йش����ʵ�֣������ FRDemo.cpp
//

class CFRDemoApp : public CWinAppEx
{
public:
	CFRDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFRDemoApp theApp;