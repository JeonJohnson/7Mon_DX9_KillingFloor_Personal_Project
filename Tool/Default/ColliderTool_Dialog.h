#pragma once


// ColliderTool_Dialog 대화 상자입니다.

class ColliderTool_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(ColliderTool_Dialog)

public:
	ColliderTool_Dialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ColliderTool_Dialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Collider_Dialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void Update_Info();
};
