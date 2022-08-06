
// ChatServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "afxdialogex.h"
#include "CListenSocket.h"
#include "CDataSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CChatServerDlg* _pCChatServerDlg = NULL;  //  이 포인터 변수로 다른 클래스에서 다이얼로그 클래스로 접근 시킬거임

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatServerDlg 대화 상자



CChatServerDlg::CChatServerDlg(CWnd* pParent /*=nullptr*/)   // 생성자
	: CDialogEx(IDD_CHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	_pCChatServerDlg = this;       // 생성된 객체는 자기자신의 주소를 가진다.
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_SEND, m_send);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT1, &CChatServerDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_SEND, &CChatServerDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CChatServerDlg 메시지 처리기


BOOL CChatServerDlg::OnInitDialog() // 다이얼 로그 초기화.
{
	m_pListenSocket = NULL; // 다이얼 로그를 초기화하면서 소켓 객체도 초기화한다.
	m_pDataSocket = NULL;
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	ASSERT(m_pListenSocket == NULL); // ASSERT -> 오류 발생시 프로그램 종료. 정상일 경우 무시하고 진행
	m_pListenSocket = new CListenSocket(this);    // ListenSocket 객체 생성
	if (m_pListenSocket->Create(8000)) {          // 포트번호 8000으로 Create
		if (m_pListenSocket->Listen()) {          // 소켓이 연결 요청 대기 상태라면
			AfxMessageBox(_T("SERVER START"), MB_ICONINFORMATION);
			return TRUE;
		}
	}

	//연결 요청 대기 상태가 아닐경우. 이미 연결 되어있는 경우
	AfxMessageBox(_T("ALREADY SERVER EXECUTION") _T("SERVER END"), MB_ICONERROR);
	return FALSE;
	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString str;

void CChatServerDlg::OnEnChangeEdit1()
{
	m_edit.GetWindowText(str);
}


void CChatServerDlg::OnBnClickedSend()
{
	m_list.SetWindowText(str);
	GetDlgItemText(IDC_EDIT1, str); // IDC_EDIT1에 입력된 문자열을 str에 복사
	m_list.InsertString(-1, str); // 복사된 문자열 list에 삽입

	m_edit.GetWindowText(str);
	str += _T("\r\n");
	m_pDataSocket->Send((LPCTSTR)str, (str.GetLength() + 1) * sizeof(TCHAR));
	m_edit.SetWindowText(_T(""));
	m_edit.SetFocus();
}


void CChatServerDlg::OnDestroy() // 다이얼로그 종료 시 소켓 객체도 같이 삭제한다.
{
	CDialogEx::OnDestroy();
	if (m_pListenSocket != NULL)
		delete m_pListenSocket; 

	if (m_pDataSocket != NULL)
		delete m_pDataSocket;

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
