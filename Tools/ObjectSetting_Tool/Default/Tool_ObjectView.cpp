
// Tool_ObjectView.cpp : CTool_ObjectView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool_Object.h"
#endif

#include "Tool_ObjectDoc.h"
#include "Tool_ObjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTool_ObjectView

IMPLEMENT_DYNCREATE(CTool_ObjectView, CView)

BEGIN_MESSAGE_MAP(CTool_ObjectView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTool_ObjectView 생성/소멸

CTool_ObjectView::CTool_ObjectView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTool_ObjectView::~CTool_ObjectView()
{
}

BOOL CTool_ObjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTool_ObjectView 그리기

void CTool_ObjectView::OnDraw(CDC* /*pDC*/)
{
	CTool_ObjectDoc* pDoc = GetDocument();
	
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CTool_ObjectView 인쇄

BOOL CTool_ObjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTool_ObjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTool_ObjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CTool_ObjectView 진단

#ifdef _DEBUG
void CTool_ObjectView::AssertValid() const
{
	CView::AssertValid();
}

void CTool_ObjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool_ObjectDoc* CTool_ObjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool_ObjectDoc)));
	return (CTool_ObjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CTool_ObjectView 메시지 처리기
