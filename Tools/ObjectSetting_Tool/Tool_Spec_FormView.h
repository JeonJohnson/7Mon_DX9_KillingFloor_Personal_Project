#pragma once




// Spec_FormView 폼 뷰입니다.

class Spec_FormView : public CFormView
{
	DECLARE_DYNCREATE(Spec_FormView)

protected:
	Spec_FormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~Spec_FormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPEC_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	void Update_Info();


	afx_msg void OnBnClickedButtonObjload();

	class GameObject*	m_pTest;
};


