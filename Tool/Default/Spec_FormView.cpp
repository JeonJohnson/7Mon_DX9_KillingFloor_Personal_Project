// Spec_FormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "Spec_FormView.h"
#include "Engine_Mother.h"
#include "Mesh_Renderer.h"


// Spec_FormView

IMPLEMENT_DYNCREATE(Spec_FormView, CFormView)

Spec_FormView::Spec_FormView()
	: CFormView(IDD_SPEC_FORMVIEW)
{



}

Spec_FormView::~Spec_FormView()
{
}

void Spec_FormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Spec_FormView, CFormView)



	ON_BN_CLICKED(IDC_BUTTON_MeshLoad, &Spec_FormView::OnBnClickedButtonMeshload)
END_MESSAGE_MAP()


// Spec_FormView �����Դϴ�.

#ifdef _DEBUG
void Spec_FormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Spec_FormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

BOOL Spec_FormView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	cs.cx = 320;
	cs.cy = 720;
	return CFormView::PreCreateWindow(cs);
}

void Spec_FormView::Update_Info()
{


}

// Spec_FormView �޽��� ó�����Դϴ�.

void Spec_FormView::OnBnClickedButtonMeshload()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	CFileDialog Dlg(
		TRUE,
		nullptr,
		nullptr,
		OFN_OVERWRITEPROMPT,
		L".X|*.X",
		this);


	//1. �Ž� �ε� 
	//���ҽ� ���� ã��.
	TCHAR	szDlg_First[256] = L"";
	GetCurrentDirectory(256, szDlg_First);
	PathRemoveFileSpec(szDlg_First);
	CString	 csResourcePath = szDlg_First;
	//�������� �ΰ� �����ֱ�
	for (int i = 0; i < 1; ++i)
	{
		int pos = csResourcePath.ReverseFind('\\');
		csResourcePath = csResourcePath.Left(pos);
	}
	csResourcePath += L"\\Resource";
	Dlg.m_ofn.lpstrInitialDir = csResourcePath;

	//wstring szFilePath; //��ü �ּ�.
	//wstring szFileName; //���� �̸��� ������ (������Ʈ �������� �� ����.)
	//wstring szRelativePath; //�� 

	wstring szMeshPath;
	wstring szMeshName;
	wstring szTexturePath;
	wstring szTextureName;
	wstring szObjName;

	wstring temp = L"../../Resource/";
	int len = temp.length();

	if (Dlg.DoModal() == IDOK)
	{
		szMeshPath = Dlg.GetPathName();
		
		szMeshName = Dlg.GetFileName();
		szTextureName = szMeshName;
		szTextureName.replace(szMeshName.find(L".X"), 2, L".png");

		szObjName = szTextureName;
		PathRemoveExtensionW((LPWSTR)szObjName.c_str());

		wstring path = L"Test/StaticMesh/";

		Engine_Mother::Get_Instance()->Load_StaticMesh(path+szMeshName,
			path+szTextureName, szObjName);

		m_pTest = INSTANTIATE(0, L"Tool_Test");

		Mesh_Renderer::Desc Mesh_desc;
		Mesh_desc.szMeshName = szObjName;

		m_pTest->Add_Component<Mesh_Renderer>(&Mesh_desc);
	}
	else
	{

	}




	UpdateData(FALSE);
}
