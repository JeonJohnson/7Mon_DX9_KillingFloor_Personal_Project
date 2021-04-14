
// Tool_ObjectView.h : CTool_ObjectView Ŭ������ �������̽�
//

#pragma once


class CTool_ObjectView : public CView
{
protected: // serialization������ ��������ϴ�.
	CTool_ObjectView();
	DECLARE_DYNCREATE(CTool_ObjectView)

// Ư���Դϴ�.
public:
	class CTool_ObjectDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CTool_ObjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Tool_ObjectView.cpp�� ����� ����
inline CTool_ObjectDoc* CTool_ObjectView::GetDocument() const
   { return reinterpret_cast<CTool_ObjectDoc*>(m_pDocument); }
#endif

