#pragma once


// ObjectSetting_DialogEx ��ȭ �����Դϴ�.

class ObjectSetting_DialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(ObjectSetting_DialogEx)

public:
	ObjectSetting_DialogEx(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ObjectSetting_DialogEx();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Setting };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
