// NaviMeshTool_Dialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "NaviMeshTool_Dialog.h"
#include "afxdialogex.h"


// NaviMeshTool_Dialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(NaviMeshTool_Dialog, CDialogEx)

NaviMeshTool_Dialog::NaviMeshTool_Dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NaviMesh_Dialog, pParent)
	, m_bNaviPointCreate(false)
{

}

NaviMeshTool_Dialog::~NaviMeshTool_Dialog()
{
}

void NaviMeshTool_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NaviMeshTool_Dialog, CDialogEx)
	ON_BN_CLICKED(IDC_DeleteVertex_BUTTON, &NaviMeshTool_Dialog::OnBnClickedDeletevertexButton)
	
	ON_BN_CLICKED(IDC_RADIO_VerCreate, &NaviMeshTool_Dialog::OnBnClickedRadioVercreate)
END_MESSAGE_MAP()


// NaviMeshTool_Dialog �޽��� ó�����Դϴ�.


void NaviMeshTool_Dialog::OnBnClickedDeletevertexButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}





void NaviMeshTool_Dialog::OnBnClickedRadioVercreate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
