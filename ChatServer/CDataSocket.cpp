// CDataSocket.cpp: 구현 파일
//

#include "pch.h"
#include "ChatServer.h"
#include "CDataSocket.h"
#include "ChatServerDlg.h"

extern CChatServerDlg* _pCChatServerDlg;
// CDataSocket

CDataSocket::CDataSocket(CChatServerDlg* pDlg)
{
	m_pDlg = pDlg;  // 생성자 호출하여 만들어진 객체는 m_pDlg 멤버변수로 다이얼로그 객체에 접근가능.
	// CDataSocket 생성자에서 만들어진 객체는 m_pDlg를 멤버로 가지고 있고, m_pDlg는 다이얼로그 클래스에 접근 가능
}

CDataSocket::~CDataSocket()
{
}


// CDataSocket 멤버 함수


void CDataSocket::OnReceive(int nErrorCode) // 클라이언트에서 데이터가 도착하면 OnReceive함수 호출
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	TCHAR buf[256 + 1];
	int nbytes = _pCChatServerDlg->m_pDataSocket->Receive(buf, 256); // Receive는 받은 데이터가 없어도 리턴함. 받은 데이터를 nbytes에 넣는다.
	buf[nbytes] = _T('\0'); // \0 = 문자열의 끝을 의미함
	_pCChatServerDlg->m_list.AddString(buf); // 리스트에 버퍼에 들어있는 데이터 출력

	CSocket::OnReceive(nErrorCode);
}


void CDataSocket::OnClose(int nErrorCode) // 클라이언트 접속 종료 시 소켓을 닫는다.
{
	_pCChatServerDlg->m_pDataSocket->Close(); // 클라이언트 소켓 종료
	delete _pCChatServerDlg->m_pDataSocket; // 소켓 삭제
	_pCChatServerDlg->m_pDataSocket  = NULL; // 소켓을 NULL값으로 초기화
	AfxMessageBox(_T("DISCONNECT"));

	CSocket::OnClose(nErrorCode);
}
