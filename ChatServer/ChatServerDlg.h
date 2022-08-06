
// ChatServerDlg.h: 헤더 파일
//

#pragma once

#include "CDataSocket.h"
#include "CListenSocket.h"

// CChatServerDlg 대화 상자
class CChatServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list;
	CEdit m_edit;
	CButton m_send;
	CListenSocket* m_pListenSocket;  // CListenSocket,CDataSocket의 포인터 변수를 선언함으로서 다이얼로그에서 
	CDataSocket* m_pDataSocket;      // CListenSocket,CDataSocket에 접근 가능
	afx_msg void OnDestroy();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedSend();
};
