// CListenSocket.cpp: 구현 파일
//

#include "pch.h"
#include "ChatServer.h"
#include "CListenSocket.h"
#include "ChatServerDlg.h"

extern CChatServerDlg* _pCChatServerDlg; // 외부 변수 선언

// CListenSocket

CListenSocket::CListenSocket(CChatServerDlg* pDlg)
{
	m_pDlg = pDlg; // 생성자 호출하여 만들어진 객체는 m_pDlg 멤버변수로 다이얼로그 객체에 접근가능.
	// CListenSocket 생성자에서 만들어진 객체는 m_pDlg를 멤버로 가지고 있고, m_pDlg는 다이얼로그 클래스에 접근 가능
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode)
{
	CSocket::OnAccept(nErrorCode);

	CString PeerAddr;
	UINT PeerPort;
	CString str;

	ASSERT(nErrorCode == 0);
	if (_pCChatServerDlg->m_pDataSocket == NULL) { // 클라이언트 소켓이 없다면
		_pCChatServerDlg->m_pDataSocket = new CDataSocket(_pCChatServerDlg); //(다이얼로그의) 클라이언트 소켓 객체를 생성한다.
		if (_pCChatServerDlg->m_pListenSocket->Accept(*_pCChatServerDlg->m_pDataSocket)) { // 클라이언트 소켓이 연결 대기중이라면
			_pCChatServerDlg->m_pDataSocket->GetPeerName(PeerAddr, PeerPort);
			str.Format(_T("IPADDRESS : %s, PORTNUM : %d \r\n"), PeerAddr, PeerPort);
			AfxMessageBox(str);
		}
		else {
			delete _pCChatServerDlg->m_pDataSocket;
			_pCChatServerDlg->m_pDataSocket = NULL;
		}
	}
}
