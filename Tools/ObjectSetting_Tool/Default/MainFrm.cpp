
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Tool_Object.h"

#include "MainFrm.h"
#include "Tool_ObjectView.h"
#include "Spec_FormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//2번째로 호출
	//윈도우 창이 생성 될 떄.

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
#pragma region Default
	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("도구 모음을 만들지 못했습니다.\n");
	//	return -1;      // 만들지 못했습니다.
	//}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("상태 표시줄을 만들지 못했습니다.\n");
	//	return -1;      // 만들지 못했습니다.
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
#pragma endregion

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	//첫번째로 호출.
	//윈도우 창이 만들어지기 전에

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style &= ~FWS_ADDTOTITLE ;//타이틀에 "제목없음" 없애기
	//cs.style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);//mainFrame창 조절 기능 없애기
	

	m_tClientRect = { 0,0,1600,720 };
	AdjustWindowRect(&m_tClientRect, WS_OVERLAPPEDWINDOW, FALSE);

	cs.cx = m_tClientRect.right- m_tClientRect.left;
	cs.cy = m_tClientRect.bottom - m_tClientRect.top;
	
	
		

	SetTitle(L"Johnson3D_ObjectTool"); //타이틀 바꾸기

	return TRUE;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	//세번째로 호출
	//클라이언트가 만들어 질 때.
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	g_pMainFrame = this;
	
	//창나누기
	m_wndSplitter.CreateStatic(this, 1, 2);

	m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(Spec_FormView), CSize(320, 720), pContext);
	g_pSpec_FormView = (Spec_FormView*)(m_wndSplitter.GetPane(0, 0));

	m_wndSplitter.CreateView(0, 1, 
		RUNTIME_CLASS(CTool_ObjectView), CSize(1280, 720), pContext);
	g_pDefaultView = (CTool_ObjectView*)(m_wndSplitter.GetPane(0, 1));


	CRect temp;
	GetClientRect(&temp);
	
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;
}



// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//lpMMI->ptMinTrackSize.x = 1600;
	//lpMMI->ptMinTrackSize.y = 720;
	//lpMMI->ptMaxTrackSize.x = 1600;
	//lpMMI->ptMaxTrackSize.y = 720;

	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}
