// ../Cpp/ObjectSetting_DialogEx.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool_Object.h"
#include "../Header/ObjectSetting_DialogEx.h"
#include "afxdialogex.h"


// ObjectSetting_DialogEx ��ȭ �����Դϴ�.

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


// ObjectSetting_DialogEx �޽��� ó�����Դϴ�.
