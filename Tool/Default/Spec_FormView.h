#pragma once
#include "afxwin.h"
#include "afxcmn.h"




// Spec_FormView 폼 뷰입니다.
class ObjectTool_Dialog;
class NaviMeshTool_Dialog;
class ColliderTool_Dialog;

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
	virtual void OnInitialUpdate();

public:
	//void Update_Info();

	//afx_msg void OnBnClickedButtonMeshload();
	//afx_msg void OnCbnSelchangeComboMeshlist();

	//afx_msg void OnEnChangeEditPosx();
	//afx_msg void OnEnChangeEditPosy();
	//afx_msg void OnEnChangeEditPosz();
	//afx_msg void OnEnChangeEditScalex();
	//afx_msg void OnEnChangeEditScaley();
	//afx_msg void OnEnChangeEditScalez();
	//afx_msg void OnEnChangeEditRotx();
	//afx_msg void OnEnChangeEditRoty();
	//afx_msg void OnEnChangeEditRotz();
	//afx_msg void OnBnClickedButtonTransreset();
	//afx_msg void OnBnClickedButtonCamerareset();
	//afx_msg void OnBnClickedButtonDeletelist();
	//afx_msg void OnBnClickedButtonLayoutsave();
	//afx_msg void OnBnClickedButtonLayoutload();

public:

	afx_msg void OnTcnSelchangeToolsTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void Update_Info();
public:
	POINT						m_tFormViewSize;

	CTabCtrl					m_tabTools;
	CRect						m_rectToolsTab;
		

	ObjectTool_Dialog*			m_ObjectTool = nullptr;
	NaviMeshTool_Dialog*		m_NaviMeshTool = nullptr;
	ColliderTool_Dialog*		m_ColliderTool = nullptr;
	int							m_iOpenTabIndex = -1;

	Camera*		m_pMainCam = nullptr;
	Vector3	m_vCamPos;
	CString	m_csCamPosX;
	CString m_csCamPosY;
	CString m_csCamPosZ;
	CString m_csCamStatus;

	afx_msg void OnBnClickedCameraresetButton();
	afx_msg void OnBnClickedCammovetoselobjButton();

	POINT	m_tMousePos;
	CString	m_csMousePosX;
	CString	m_csMousePosY;
	CString m_csMouseStatus;

public:


	//class GameObject*	m_pSelectObject;

	////transformation
	//Vector3				m_vPos;
	//Vector3				m_vScale;
	//Vector3				m_vRot;

	//CComboBox			m_MeshList_Combo;
	//int					m_iMeshList_Index = 0;
	//CString				m_csSelMeshName;

	//CString m_PosX_Edit;
	//CString m_PosY_Edit;
	//CString m_PosZ_Edit;

	//CString m_ScaleX_Edit;
	//CString m_ScaleY_Edit;
	//CString m_ScaleZ_Edit;

	//CString m_RotX_Edit;
	//CString m_RotY_Edit;
	//CString m_RotZ_Edit;
	



	
};


