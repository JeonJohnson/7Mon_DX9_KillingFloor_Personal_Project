// ../Cpp/ObjectSetting_DialogEx.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool_Object.h"
#include "../Header/ObjectSetting_DialogEx.h"
#include "afxdialogex.h"


// ObjectSetting_DialogEx 대화 상자입니다.

IMPLEMENT_DYNAMIC(ObjectSetting_DialogEx, CDialogEx)

ObjectSetting_DialogEx::ObjectSetting_DialogEx(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Setting, pParent)
{

}

ObjectSetting_DialogEx::~ObjectSetting_DialogEx()
{
}

void ObjectSetting_DialogEx::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ObjectSetting_DialogEx, CDialogEx)
END_MESSAGE_MAP()


// ObjectSetting_DialogEx 메시지 처리기입니다.
