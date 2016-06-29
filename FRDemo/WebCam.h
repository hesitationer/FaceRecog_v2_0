//#include "../tools/tools.h"
#include "stdafx.h"
#include "../FaceMngr/FaceMngr.h"

/*
	OpenCV2.0����ͷ�����ķ�װ
	�÷�����Init��ʼ������ͷ��ź��Ƿ����Ҿ�����GetFrame��ȡ��ǰ֡���Զ�Release
	�����̻߳�ȡͬһ����ͷ���ݣ����ʹ��һ������ʵ����ʹ��GetFrameʱ������һ����ʼ���õ�IplImage
	������GetFrame���Ὣͼ���Ƶ�IplImage���Է����̳߳�ͻ
*/
class CWebCam
{
public:
	CWebCam(void);
	~CWebCam(void);

private:
	CvCapture	*m_capture;
	int			m_interval;
	bool		m_bStarted, m_bMirrorLike;
	double		m_fLastFrameTime, m_fFrameFreq;
	CWinThread	*m_thrdShow;
	HWND		prtHwnd;
	HANDLE		m_hEvntPause;
	CCriticalSection	m_csCap;

public:
	bool Init(int camIndex = 0, bool bMirrorLike = true);
	void Release();

	IplImage	*GetFrame(IplImage *frame = NULL); // ��frame=NULL,�򷵻����õ�IplImageָ��
	double		GetRealFrameFreq(); // ǰ������GetFrame�ļ���ĵ���
	CvSize		GetFrameSize();

	// ���ڵ���һ���̣߳�������interval������ͷ��׽���Ļ�����ʾ��parentHwnd
	void		RealtimeShow(int interval = 0, HWND parentHwnd = NULL);
	void		RealtimePause(bool pause);
	void		RealtimeShut();

	UINT RunShow();
};

UINT WebCamShowProc(LPVOID pParam); // CWebCam���õ���ʽ�̺߳���