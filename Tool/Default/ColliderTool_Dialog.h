#pragma once


// ColliderTool_Dialog ��ȭ �����Դϴ�.

class ColliderTool_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(ColliderTool_Dialog)

public:
	ColliderTool_Dialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ColliderTool_Dialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Collider_Dialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	void Update_Info();
};
