// ColliderTool_Dialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ColliderTool_Dialog.h"
#include "afxdialogex.h"


// ColliderTool_Dialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(ColliderTool_Dialog, CDialogEx)

ColliderTool_Dialog::ColliderTool_Dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Collider_Dialog, pParent)
{

}

ColliderTool_Dialog::~ColliderTool_Dialog()
{
}

void ColliderTool_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ColliderTool_Dialog, CDialogEx)
END_MESSAGE_MAP()


// ColliderTool_Dialog 메시지 처리기입니다.
