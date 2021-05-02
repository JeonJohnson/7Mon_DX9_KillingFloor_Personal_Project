#pragma once
#include "afxwin.h"


// NaviMeshTool_Dialog ��ȭ �����Դϴ�.

class NaviMeshTool_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(NaviMeshTool_Dialog)

public:
	NaviMeshTool_Dialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~NaviMeshTool_Dialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NaviMesh_Dialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDeletevertexButton();

	void Update_Info();
	void Create_NaviPoint(const Vector3& _WorldPos);

public:
	int		m_iNaviPointIndex = 0;

	afx_msg void OnBnClickedCheckPointcreate();
	CButton m_checkPointCreate;
	bool	m_bPointCreate;
	CListBox m_PointList;
};
