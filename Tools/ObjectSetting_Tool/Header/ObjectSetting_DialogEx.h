#pragma once


// ObjectSetting_DialogEx 대화 상자입니다.

class ObjectSetting_DialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(ObjectSetting_DialogEx)

public:
	ObjectSetting_DialogEx(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ObjectSetting_DialogEx();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Setting };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
