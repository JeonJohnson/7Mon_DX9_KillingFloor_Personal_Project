#pragma once


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


public:

	bool m_bNaviPointCreate;
	afx_msg void OnBnClickedRadioVercreate();
};
