// ../Cpp/Spec_FormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool_Object.h"
#include "../Header/Spec_FormView.h"


// Spec_FormView

IMPLEMENT_DYNCREATE(Spec_FormView, CFormView)

Spec_FormView::Spec_FormView()
	: CFormView(IDD_SPEC_FORMVIEW)
{

}

Spec_FormView::~Spec_FormView()
{
}

void Spec_FormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Spec_FormView, CFormView)
END_MESSAGE_MAP()


// Spec_FormView 진단입니다.

#ifdef _DEBUG
void Spec_FormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Spec_FormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

BOOL Spec_FormView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	cs.cx = 400;
	cs.cy = 720;
	return CFormView::PreCreateWindow(cs);
}



// Spec_FormView 메시지 처리기입니다.
