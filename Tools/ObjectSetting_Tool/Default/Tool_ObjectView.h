
// Tool_ObjectView.h : CTool_ObjectView 클래스의 인터페이스
//

#pragma once


class CTool_ObjectView : public CView
{
protected: // serialization에서만 만들어집니다.
	CTool_ObjectView();
	DECLARE_DYNCREATE(CTool_ObjectView)

// 특성입니다.
public:
	class CTool_ObjectDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CTool_ObjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Tool_ObjectView.cpp의 디버그 버전
inline CTool_ObjectDoc* CTool_ObjectView::GetDocument() const
   { return reinterpret_cast<CTool_ObjectDoc*>(m_pDocument); }
#endif

