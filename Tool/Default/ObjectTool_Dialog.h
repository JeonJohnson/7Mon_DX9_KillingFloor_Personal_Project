#pragma once
#include "afxwin.h"


// ObjectTool_Dialog 대화 상자입니다.

class ObjectTool_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(ObjectTool_Dialog)

public:
	ObjectTool_Dialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ObjectTool_Dialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Object_Dialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void Update_Info();


public:
	afx_msg void OnCbnSelchangeComboMeshlist();
	afx_msg void OnBnClickedButtonMeshload();
	afx_msg void OnBnClickedButtonDeletelist();
	afx_msg void OnEnChangeEditPosx();
	afx_msg void OnEnChangeEditPosy();
	afx_msg void OnEnChangeEditPosz();
	afx_msg void OnEnChangeEditScalex();
	afx_msg void OnEnChangeEditScaley();
	afx_msg void OnEnChangeEditScalez();
	afx_msg void OnEnChangeEditRotx();
	afx_msg void OnEnChangeEditRoty();
	afx_msg void OnEnChangeEditRotz();
	afx_msg void OnBnClickedButtonCamerareset();
	afx_msg void OnBnClickedButtonTransreset();

public:
	class GameObject*	m_pSelectObject;

	//transformation
	Vector3				m_vPos;
	Vector3				m_vScale;
	Vector3				m_vRot;

	CComboBox m_MeshList_Combo;
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

	


	afx_msg void OnBnClickedButtonLayoutsave();
	afx_msg void OnBnClickedButtonLayoutload();
};
