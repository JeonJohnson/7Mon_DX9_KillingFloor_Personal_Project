#pragma once




// Spec_FormView �� ���Դϴ�.

class Spec_FormView : public CFormView
{
	DECLARE_DYNCREATE(Spec_FormView)

protected:
	Spec_FormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	void Update_Info();


	afx_msg void OnBnClickedButtonObjload();

	class GameObject*	m_pTest;
};


