#pragma once
#include "afxwin.h"




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

	afx_msg void OnBnClickedButtonMeshload();
	afx_msg void OnCbnSelchangeComboMeshlist();

	afx_msg void OnEnChangeEditPosx();
	afx_msg void OnEnChangeEditPosy();
	afx_msg void OnEnChangeEditPosz();
	afx_msg void OnEnChangeEditScalex();
	afx_msg void OnEnChangeEditScaley();
	afx_msg void OnEnChangeEditScalez();
	afx_msg void OnEnChangeEditRotx();
	afx_msg void OnEnChangeEditRoty();
	afx_msg void OnEnChangeEditRotz();

public:
	class GameObject*	m_pSelectObject;

	//transformation
	Vector3				m_vPos;
	Vector3				m_vScale;
	Vector3				m_vRot;




	CComboBox			m_MeshList_Combo;
	int					m_iMeshList_Index = 0;
	CString				m_csSelMeshName;

	CString m_PosX_Edit;
	CString m_PosY_Edit;
	CString m_PosZ_Edit;

	CString m_ScaleX_Edit;
	CString m_ScaleY_Edit;
	CString m_ScaleZ_Edit;

	CString m_RotX_Edit;
	CString m_RotY_Edit;
	CString m_RotZ_Edit;
	afx_msg void OnBnClickedButtonTransreset();
	afx_msg void OnBnClickedButtonCamerareset();
};


