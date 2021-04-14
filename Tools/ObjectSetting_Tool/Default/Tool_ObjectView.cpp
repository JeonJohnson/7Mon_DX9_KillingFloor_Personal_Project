
// Tool_ObjectView.cpp : CTool_ObjectView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTool_ObjectView ����/�Ҹ�

CTool_ObjectView::CTool_ObjectView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTool_ObjectView::~CTool_ObjectView()
{
}

BOOL CTool_ObjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTool_ObjectView �׸���

void CTool_ObjectView::OnDraw(CDC* /*pDC*/)
{
	CTool_ObjectDoc* pDoc = GetDocument();
	
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CTool_ObjectView �μ�

BOOL CTool_ObjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTool_ObjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTool_ObjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CTool_ObjectView ����

#ifdef _DEBUG
void CTool_ObjectView::AssertValid() const
{
	CView::AssertValid();
}

void CTool_ObjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool_ObjectDoc* CTool_ObjectView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool_ObjectDoc)));
	return (CTool_ObjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CTool_ObjectView �޽��� ó����
