/* 
	һЩ�������ڵĺ���
*/

#pragma once
#include "stdafx.h"
#include "../FaceMngr/FaceMngr.h"


// ����һ����ΪstrWndName��OpenCV Window������Ƕ�뵽pWnd���������ߴ�
void EmbedCvWindow(HWND pWnd, CString strWndName, int w, int h);


/*
	ѡ��Ŀ¼
	hWnd: could be NULL
	strTitle: ���ڱ���
	[IN][OUT] CString &strDir: Ĭ�Ͼ���·����ѡ��õ���Ŀ¼
*/
bool SelDirectory ( HWND hWnd, LPCTSTR strTitle, CString &strDir );


/*
	��folder���ҳ����е�һ���ַ�����!���ļ���������list���� FaceMngr::Train ���á�
	�����ļ���������name��name��ͬ��Ϊһ��class��classIdͬ������list��ѵ��ʱʹ�á�
*/
void GenFileList(CString folder, vector<SFInfo> &list);
void GenFileListFromFile( CString fn, vector<SFInfo> &list );


/*
	�����ļ�����ȡ�����������ǣ��ļ���������ߵ��»�����ߵ��ַ���
	���û���»��ߣ������ļ��������ұߵĵ�����ַ�����û�У�����ȫ���ļ�����
	��ͼƬ�����������ǣ�{name}_{something}.ext�����磺����_0.jpg������_smile.bmp����
*/
CString FindName(CString fn);


//inline void operator /=(CvSize &a, double b)
//{
//	a.height = int(a.height / b);
//	a.width = int(a.width / b);
//}
//
//inline void operator *=(CvSize &a, double b)
//{
//	a.height = int(a.height * b);
//	a.width = int(a.width * b);
//}
//
//inline CvSize operator *(CvSize a, double b)
//{
//	return cvSize(int(a.width * b), int(a.height * b));
//}
//
//inline CvSize operator /(CvSize a, double b)
//{
//	return cvSize(int(a.width / b), int(a.height / b));
//}
//
//void tic(); // start timer
//
//double toc(); // return the elapsed seconds from the last TIC
