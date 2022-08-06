#pragma once

class CChatServerDlg;

// CDataSocket 명령 대상

class CDataSocket : public CSocket
{
public:
	CDataSocket(CChatServerDlg* pDlg);  // 변환 생성자. CListenSocket 클래스에 Dlg클래스의 포인터 변수pDlg를 대입
	virtual ~CDataSocket();
	CChatServerDlg* m_pDlg;  // 포인터 변수를 선언하는 이유는 다이얼로그 클래스에 접근하기위함(다이얼 로그에서 작업해야되니까)
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


