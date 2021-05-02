// Spec_FormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "Spec_FormView.h"
#include "Engine_Mother.h"
#include "Mesh_Renderer.h"
#include "GameObject.h"
#include "..\..\Engine\Header\Engine_Struct.h"
#include "..\..\Engine\Header\Function_String.h"
#include "..\..\Engine\Header\SaveInfo.h"

#include "ObjectTool_Dialog.h"
#include "NaviMeshTool_Dialog.h"
#include "ColliderTool_Dialog.h"

// Spec_FormView

IMPLEMENT_DYNCREATE(Spec_FormView, CFormView)

Spec_FormView::Spec_FormView()
	: CFormView(IDD_SPEC_FORMVIEW)
	//, m_PosX_Edit(_T(""))
	//, m_PosY_Edit(_T(""))
	//, m_PosZ_Edit(_T(""))
	//, m_ScaleX_Edit(_T(""))
	//, m_ScaleY_Edit(_T(""))
	//, m_ScaleZ_Edit(_T(""))
	//, m_RotX_Edit(_T(""))
	//, m_RotY_Edit(_T(""))
	//, m_RotZ_Edit(_T(""))
	, m_csCamStatus(_T(""))
	, m_csMouseStatus(_T(""))
{



}

Spec_FormView::~Spec_FormView()
{
}

void Spec_FormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO_MeshList, m_MeshList_Combo);
	//DDX_Text(pDX, IDC_EDIT_PosX, m_PosX_Edit);
	//DDX_Text(pDX, IDC_EDIT_PosY, m_PosY_Edit);
	//DDX_Text(pDX, IDC_EDIT_PosZ, m_PosZ_Edit);
	//DDX_Text(pDX, IDC_EDIT_ScaleX, m_ScaleX_Edit);
	//DDX_Text(pDX, IDC_EDIT_ScaleY, m_ScaleY_Edit);
	//DDX_Text(pDX, IDC_EDIT_ScaleZ, m_ScaleZ_Edit);
	//DDX_Text(pDX, IDC_EDIT_RotX, m_RotX_Edit);
	//DDX_Text(pDX, IDC_EDIT_RotY, m_RotY_Edit);
	//DDX_Text(pDX, IDC_EDIT_RotZ, m_RotZ_Edit);
	DDX_Control(pDX, IDC_Tools_Tab, m_tabTools);
	DDX_Text(pDX, IDC_CamStatus, m_csCamStatus);
	DDX_Text(pDX, IDC_MouseStatus, m_csMouseStatus);
}

BEGIN_MESSAGE_MAP(Spec_FormView, CFormView)

	//ON_BN_CLICKED(IDC_BUTTON_MeshLoad, &Spec_FormView::OnBnClickedButtonMeshload)
	//ON_CBN_SELCHANGE(IDC_COMBO_MeshList, &Spec_FormView::OnCbnSelchangeComboMeshlist)
	//ON_EN_CHANGE(IDC_EDIT_PosX, &Spec_FormView::OnEnChangeEditPosx)
	//ON_EN_CHANGE(IDC_EDIT_PosY, &Spec_FormView::OnEnChangeEditPosy)
	//ON_EN_CHANGE(IDC_EDIT_PosZ, &Spec_FormView::OnEnChangeEditPosz)
	//ON_EN_CHANGE(IDC_EDIT_ScaleX, &Spec_FormView::OnEnChangeEditScalex)
	//ON_EN_CHANGE(IDC_EDIT_ScaleY, &Spec_FormView::OnEnChangeEditScaley)
	//ON_EN_CHANGE(IDC_EDIT_ScaleZ, &Spec_FormView::OnEnChangeEditScalez)
	//ON_EN_CHANGE(IDC_EDIT_RotX, &Spec_FormView::OnEnChangeEditRotx)
	//ON_EN_CHANGE(IDC_EDIT_RotY, &Spec_FormView::OnEnChangeEditRoty)
	//ON_EN_CHANGE(IDC_EDIT_RotZ, &Spec_FormView::OnEnChangeEditRotz)
	//ON_BN_CLICKED(IDC_BUTTON_TransReset, &Spec_FormView::OnBnClickedButtonTransreset)
	//ON_BN_CLICKED(IDC_BUTTON_CameraReset, &Spec_FormView::OnBnClickedButtonCamerareset)

	//ON_BN_CLICKED(IDC_BUTTON_DeleteList, &Spec_FormView::OnBnClickedButtonDeletelist)
	//ON_BN_CLICKED(IDC_BUTTON_LayoutSave, &Spec_FormView::OnBnClickedButtonLayoutsave)
	//ON_BN_CLICKED(IDC_BUTTON_LayoutLoad, &Spec_FormView::OnBnClickedButtonLayoutload)
	ON_WM_CREATE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_Tools_Tab, &Spec_FormView::OnTcnSelchangeToolsTab)
	ON_BN_CLICKED(IDC_CameraReset_Button, &Spec_FormView::OnBnClickedCameraresetButton)
	ON_BN_CLICKED(IDC_CamMoveToSelObj_Button, &Spec_FormView::OnBnClickedCammovetoselobjButton)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Spec_FormView 진단입니다.

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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	cs.cx = 350;
	cs.cy = 720;


	return CFormView::PreCreateWindow(cs);
}

void Spec_FormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	//UpdateData(FALSE);

	m_tFormViewSize.x = cx;
	m_tFormViewSize.y = cy;

	//UpdateData(TRUE);
}

void Spec_FormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_tabTools.InsertItem(0, L"객체 배치 도구");
	m_tabTools.InsertItem(1, L"항해 망사 도구");
	m_tabTools.InsertItem(2, L"충돌체 배치 도구");
	
	m_tabTools.GetWindowRect(&m_rectToolsTab);

	if (m_ObjectTool == nullptr)
	{
		m_ObjectTool = new ObjectTool_Dialog;
		m_ObjectTool->Create(IDD_Object_Dialog, &m_tabTools);
		g_pObjectTool_Dialog = m_ObjectTool;
	}
	
	if (m_NaviMeshTool == nullptr)
	{
		m_NaviMeshTool = new NaviMeshTool_Dialog;
		m_NaviMeshTool->Create(IDD_NaviMesh_Dialog, &m_tabTools);
		g_pNaviMeshTool_Dialog = m_NaviMeshTool;
	}

	if (m_ColliderTool == nullptr)
	{
		m_ColliderTool = new ColliderTool_Dialog;
		m_ColliderTool->Create(IDD_Collider_Dialog, &m_tabTools);
		g_pColliderTool_Dialog = m_ColliderTool;
	}

	m_ObjectTool->MoveWindow(0, 25, m_rectToolsTab.Width(), m_rectToolsTab.Height());
	m_ObjectTool->ShowWindow(SW_SHOW);
	m_NaviMeshTool->ShowWindow(SW_HIDE);
	m_ColliderTool->ShowWindow(SW_HIDE);
	m_tabTools.SetCurSel(0);
	m_iOpenTabIndex = m_tabTools.GetCurSel();
}


void Spec_FormView::OnTcnSelchangeToolsTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_tabTools.GetWindowRect(&m_rectToolsTab);

	int		m_iOpenTabIndex = m_tabTools.GetCurSel();

	switch (m_iOpenTabIndex)
	{
	case 0:
	{
		m_ObjectTool->MoveWindow(0, 25, m_rectToolsTab.Width(), m_rectToolsTab.Height());
		
		m_ObjectTool->ShowWindow(SW_SHOW);
		m_NaviMeshTool->ShowWindow(SW_HIDE);
		m_ColliderTool->ShowWindow(SW_HIDE);
	}
	break;

	case 1:
	{	
		m_NaviMeshTool->MoveWindow(0, 25, m_rectToolsTab.Width(), m_rectToolsTab.Height());
		
		m_NaviMeshTool->ShowWindow(SW_SHOW);
		m_ObjectTool->ShowWindow(SW_HIDE); 
		m_ColliderTool->ShowWindow(SW_HIDE);
	}
	break;

	case 2:
	{
		m_ColliderTool->MoveWindow(0, 25, m_rectToolsTab.Width(), m_rectToolsTab.Height());

		m_ColliderTool->ShowWindow(SW_SHOW);
		m_ObjectTool->ShowWindow(SW_HIDE);
		m_NaviMeshTool->ShowWindow(SW_HIDE);
	}
	break;

	default:
		break;
	}

	*pResult = 0;

	UpdateData(FALSE);
}

void Spec_FormView::Update_Info()
{
	UpdateData(TRUE);

	
	if (EngineFunction->Get_MainCamera() != nullptr)
	{
		m_vCamPos = EngineFunction->Get_MainCamera()->Get_Transform()->Get_Position();

		m_csCamPosX.Format(L"%.2f", m_vCamPos.x);
		m_csCamPosY.Format(L"%.2f", m_vCamPos.y);
		m_csCamPosZ.Format(L"%.2f", m_vCamPos.z);

		m_csCamStatus = L"영사기 위치\n좌우 : " + m_csCamPosX
			+ L"\n상하 : " + m_csCamPosY
			+ L"\n전후 : " + m_csCamPosZ;
	}

	m_tMousePos =  g_pDefaultView->m_tMousePos_View;

	m_csMousePosX.Format(L"%d", m_tMousePos.x);
	m_csMousePosY.Format(L"%d", m_tMousePos.y);
	m_csMouseStatus = L"쥐 위치\n좌우 : " + m_csMousePosX
		+ L"\n상하 : " + m_csMousePosY;


	UpdateData(FALSE);
}

void Spec_FormView::OnBnClickedCameraresetButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Spec_FormView::OnBnClickedCammovetoselobjButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



#pragma  region Olds
//void Spec_FormView::Update_Info()
//{
//	UpdateData(TRUE);
//
//	if (m_pSelectObject != nullptr)
//	{
//		m_MeshList_Combo.GetLBText(m_iMeshList_Index, m_csSelMeshName);
//
//		m_vPos = m_pSelectObject->Get_Position();
//		m_vScale = m_pSelectObject->Get_Scale();
//		m_vRot = m_pSelectObject->Get_Transform()->Get_Rotation_Euler();
//
//		m_PosX_Edit.Format(L"%.2f", m_vPos.x);
//		m_PosY_Edit.Format(L"%.2f", m_vPos.y);
//		m_PosZ_Edit.Format(L"%.2f", m_vPos.z);
//
//		m_ScaleX_Edit.Format(L"%.2f", m_vScale.x);
//		m_ScaleY_Edit.Format(L"%.2f", m_vScale.y);
//		m_ScaleZ_Edit.Format(L"%.2f", m_vScale.z);
//
//		m_RotX_Edit.Format(L"%.2f", m_vRot.x);
//		m_RotY_Edit.Format(L"%.2f", m_vRot.y);
//		m_RotZ_Edit.Format(L"%.2f", m_vRot.z);
//	}
//	else
//	{
//		m_PosY_Edit = L"객체를 선택해 주십시오.";
//		m_PosX_Edit = L"객체를 선택해 주십시오.";
//		m_PosZ_Edit = L"객체를 선택해 주십시오.";
//
//		m_ScaleX_Edit = L"객체를 선택해 주십시오.";
//		m_ScaleY_Edit = L"객체를 선택해 주십시오.";
//		m_ScaleZ_Edit = L"객체를 선택해 주십시오.";
//
//		m_RotX_Edit = L"객체를 선택해 주십시오.";
//		m_RotY_Edit = L"객체를 선택해 주십시오.";
//		m_RotZ_Edit = L"객체를 선택해 주십시오.";
//	
//	}
//	
//	UpdateData(FALSE);
//}
//
//// Spec_FormView 메시지 처리기입니다.
//
//void Spec_FormView::OnBnClickedButtonMeshload()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	UpdateData(TRUE);
//
//	CFileDialog Dlg(
//		TRUE,
//		nullptr,
//		nullptr,
//		OFN_OVERWRITEPROMPT,
//		L".X|*.X",
//		this);
//
//
//	//1. 매쉬 로드 
//	//리소스 폴더 찾아서 Modal 기본 폴더로 해주기.
//	TCHAR	szDlg_First[256] = L"";
//	GetCurrentDirectory(256, szDlg_First);
//	PathRemoveFileSpec(szDlg_First);
//	CString	 csResourcePath = szDlg_First;
//	//상위폴더 두개 지워주기
//	for (int i = 0; i < 1; ++i)
//	{
//		int pos = csResourcePath.ReverseFind('\\');
//		csResourcePath = csResourcePath.Left(pos);
//	}
//	csResourcePath += L"\\Resource";
//	Dlg.m_ofn.lpstrInitialDir = csResourcePath;
//
//	//wstring szFilePath; //전체 주소.
//	//wstring szFileName; //파일 이름만 저장할 (오브젝트 네임으로 쓸 예정.)
//	//wstring szRelativePath; //그 
//
//	wstring szMeshPath;
//	wstring szMeshRelativePath;
//	wstring szMeshName;
//	//wstring szTexturePath;
//	//wstring szTextureName;
//	wstring szObjName;
//
//	wstring temp = L"../../Resource/";
//	int len = (int)temp.length();
//
//	if (Dlg.DoModal() == IDOK)
//	{
//		szMeshPath = Dlg.GetPathName(); //절대경로로 받아옴.
//		szMeshName = Dlg.GetFileName();
//
//		szMeshRelativePath = szMeshPath;
//		//int findpos = szMeshRelativePath.find(L"Resource\\");
//		szMeshRelativePath.erase(0, szMeshRelativePath.find(L"Resource\\")+9);
//		//이제 텍스쳐는 매쉬 내부에서 XFile에 있는 걸로 알아서 불러올 꺼임.  
//		//szTextureName = szMeshName;
//		//szTextureName.replace(szMeshName.find(L".X"), 2, L".png");
//
//		szObjName = szMeshName;
//		szObjName.erase(szObjName.find(L".X"), szObjName.length());
//		//PathRemoveExtensionW((LPWSTR)szObjName.c_str());
//		//지금 이거 .자리에 \0을 넣는거지 그 뒤에걸 erase해주지는 않네... ㅁㅊ새기
//
//		//주소값 '\\'을 '/'로 바꾸기
//		size_t iPos = -1;
//		while (true)
//		{
//			iPos = szMeshRelativePath.find(L"\\");
//			if (iPos == string::npos)
//			{
//				break;
//			}
//
//			szMeshRelativePath.replace(iPos, 1, L"/");		
//		}
//		//로드할때는 리소스밑에 있는 폴더명으로 넣 어줘야함.
//		Engine_Mother::Get_Instance()->Load_Mesh(szMeshRelativePath,szObjName);
//		GameObject* pTempObject = INSTANTIATE(OBJECT_TAG_TERRAIN, szObjName);
//
//		Mesh_Renderer::Desc Mesh_desc;
//		Mesh_desc.szMeshName = szObjName;
//		pTempObject->Add_Component<Mesh_Renderer>(&Mesh_desc);
//
//		SaveInfo::Desc Save_desc;
//		Save_desc.szMeshPath = szMeshRelativePath;
//		Save_desc.szObjName = szObjName;
//		pTempObject->Add_Component<SaveInfo>(&Save_desc);
//		
//		
//		m_MeshList_Combo.AddString(szObjName.c_str());
//
//#pragma region stringsTest
//		//const TCHAR* tcTemp = L"";
//		//TCHAR arrTemp[255];
//		//tcTemp = (wchar_t*)szMeshRelativePath.c_str();
//		//_tcscpy_s(arrTemp, tcTemp);
//		//wstring wstrTemp;
//		//Function_String::TCHAR2wstring(arrTemp, wstrTemp);
//
//		//TCHAR arrTemp2[255] = L"";
//		//Function_String::wstring2TCHAR(wstrTemp, arrTemp2);
//		////strcpy_s((char*)arrTemp, strlen((char*)),(char*)tcTemp);
//		////Function_String::wstring2TCHAR(szMeshRelativePath, tcTemp);
//
//		//Save_TerrainLayout* pTempSaveInfo = new Save_TerrainLayout;
//		//ZeroMemory(pTempSaveInfo, sizeof(Save_TerrainLayout));
//		//Function_String::wstring2TCHAR(szMeshRelativePath, pTempSaveInfo->szMeshPath);
//#pragma endregion
//	}
//	else
//	{
//
//	}
//
//
//
//
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnCbnSelchangeComboMeshlist()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//	m_iMeshList_Index = m_MeshList_Combo.GetCurSel();
//	m_MeshList_Combo.GetLBText(m_iMeshList_Index, m_csSelMeshName);
//
//	//m_pSelectObject = EngineFunction->Get_GameObjectbyName(m_csSelMeshName.operator LPCWSTR());
//	m_pSelectObject = EngineFunction->Get_GameObject(1,m_csSelMeshName.operator LPCWSTR());
//	assert(L"GameObject find Failed at ComboBox"&&m_pSelectObject);
//
//	m_vPos = m_pSelectObject->Get_Position();
//	m_vScale = m_pSelectObject->Get_Scale();
//	m_vRot = m_pSelectObject->Get_Transform()->Get_Rotation_Euler();
//
//
//
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnEnChangeEditPosx()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	UpdateData(TRUE);
//	if (m_pSelectObject != nullptr) 
//	{
//		m_vPos.x = (float)atof((CStringA)m_PosX_Edit);
//
//		m_pSelectObject->Set_Position(m_vPos);
//	}
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnEnChangeEditPosy()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//	if (m_pSelectObject != nullptr)
//	{
//		m_vPos.y = (float)atof((CStringA)m_PosY_Edit);
//
//		m_pSelectObject->Set_Position(m_vPos);
//	}
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnEnChangeEditPosz()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	UpdateData(TRUE);
//	if (m_pSelectObject != nullptr)
//	{
//		m_vPos.z = (float)atof((CStringA)m_PosZ_Edit);
//
//		m_pSelectObject->Set_Position(m_vPos);
//	}
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnEnChangeEditScalex()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//
//	if (m_pSelectObject != nullptr)
//	{
//		m_vScale.x = (float)atof((CStringA)m_ScaleX_Edit);
//
//		m_pSelectObject->Set_Scale(m_vScale);
//	}
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnEnChangeEditScaley()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//	if (m_pSelectObject != nullptr)
//	{
//		m_vScale.y = (float)atof((CStringA)m_ScaleY_Edit);
//
//		m_pSelectObject->Set_Scale(m_vScale);
//	}
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnEnChangeEditScalez()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//	if (m_pSelectObject != nullptr)
//	{
//		m_vScale.z = (float)atof((CStringA)m_ScaleZ_Edit);
//
//		m_pSelectObject->Set_Scale(m_vScale);
//	}
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnEnChangeEditRotx()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	UpdateData(TRUE);
//	if (m_pSelectObject != nullptr)
//	{
//		m_vRot.x = (float)atof((CStringA)m_RotX_Edit);
//
//		m_pSelectObject->Set_RotationX(m_vRot.x);
//	}
//
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnEnChangeEditRoty()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	UpdateData(TRUE);
//	if (m_pSelectObject != nullptr)
//	{
//		m_vRot.y = (float)atof((CStringA)m_RotY_Edit);
//
//		m_pSelectObject->Set_RotationY(m_vRot.y);
//	}
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnEnChangeEditRotz()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	UpdateData(TRUE);
//	if (m_pSelectObject != nullptr)
//	{
//		m_vRot.z = (float)atof((CStringA)m_RotZ_Edit);
//
//		m_pSelectObject->Set_RotationZ(m_vRot.z);
//	}
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnBnClickedButtonTransreset()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//	if (m_pSelectObject != nullptr)
//	{
//		if (IDYES == AfxMessageBox(L"ㄹㅇ루다가 트랜스폼 초기화 허쉴..?", MB_YESNO | MB_ICONQUESTION))
//		{
//			m_vPos = { 0.f,0.f,0.f };
//			m_vScale = { 1.f, 1.f, 1.f };
//			m_vRot = { 0.f,0.f,0.f };
//
//			m_pSelectObject->Set_Position(m_vPos);
//			m_pSelectObject->Set_Scale(m_vScale);
//			m_pSelectObject->Set_Rotation(m_vRot.x, m_vRot.y, m_vRot.z);
//
//		}
//		else { return; }
//	}
//	else { AfxMessageBox(L"초기화 할 거 없는데 지랄 ㄴ", MB_OK); }
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnBnClickedButtonCamerareset()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//
//
//
//	UpdateData(FALSE);
//}
//
//
//
//
//void Spec_FormView::OnBnClickedButtonDeletelist()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//	
//	if (m_pSelectObject == nullptr)
//	{
//		AfxMessageBox(L"삭제할거 선택하삼", MB_OK | MB_ICONQUESTION);
//	}
//	else 
//	{
//		if (IDYES == AfxMessageBox(L"ㄹㅇ루다가 해당 오브젝트 삭제 허쉴?", MB_YESNO | MB_ICONQUESTION))
//		{
//			m_MeshList_Combo.DeleteString(m_iMeshList_Index);
//			m_iMeshList_Index = -1;
//			m_csSelMeshName = L"";
//
//			GameObject::Destory(m_pSelectObject);
//			m_pSelectObject = nullptr;
//
//			AfxMessageBox(L"삭제 됬음. ㅅㄱ", MB_OK | MB_ICONQUESTION);
//		}
//	}
//
//
//
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnBnClickedButtonLayoutsave()
//{
//	//레이아웃 저장
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//
//	CFileDialog Dlg(FALSE,
//		L"dat",
//		L"",
//		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//		L"Data File(*.bin)|*.bin||", this);
//
//	TCHAR	szDlg_First[256] = L"";
//	GetCurrentDirectory(256, szDlg_First);
//	PathRemoveFileSpec(szDlg_First);
//	CString	 csResourcePath = szDlg_First;
//
//	//상위폴더 두개 지워주기
//	for (int i = 0; i < 1; ++i)
//	{
//		int pos = csResourcePath.ReverseFind('\\');
//		csResourcePath = csResourcePath.Left(pos);
//	}
//	csResourcePath += L"/Resource/Data";
//	Dlg.m_ofn.lpstrInitialDir = csResourcePath;
//
//	if (Dlg.DoModal())
//	{
//		CString csFilePath = Dlg.GetPathName();
//
//		HANDLE	hFile = CreateFile(csFilePath, GENERIC_WRITE, 0, 0,
//			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
//
//		if (hFile == INVALID_HANDLE_VALUE)
//		{
//			AfxMessageBox(L"저장이 핸들 생성에서 실패 했읍니다. ㅅㄱ", MB_OK);
//			return;
//		}
//
//		DWORD	dwByte = 0;
//
//		list<GameObject*> TempList = EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_TERRAIN);
//
//		for (auto& obj : TempList)
//		{
//			Save_TerrainLayout SaveData = obj->Get_Component<SaveInfo>()->Get_TerrainSave();
//			WriteFile(hFile, &SaveData, sizeof(Save_TerrainLayout), &dwByte, nullptr);
//		}
//		AfxMessageBox(L"저장완료", MB_ICONASTERISK);
//		CloseHandle(hFile);
//		
//
//	}
//
//
//	//if (Dlg.DoModal())
//	//{
//	//	CString csFilePath = Dlg.GetPathName();
//
//	//	HANDLE hFile = CreateFile(csFilePath, GENERIC_WRITE, 0, 0,
//	//		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
//
//	//	if (INVALID_HANDLE_VALUE == hFile)
//	//	{
//	//		AfxMessageBox(L"핸들 생성에서 저장이 실패 했읍니다. ㅅㄱ", MB_OK);
//	//	}
//
//	//	DWORD dwByte = 0;
//
//	//	int iSize = CMainApp::Get_Instance()->Get_SortSize();
//	//	int iCap = CMainApp::Get_Instance()->Get_VecSprite().capacity();
//
//	//	for (auto& element : CMainApp::Get_Instance()->Get_VecSprite())
//	//	{
//	//		//element->Sprite_Info.tFrameInfo.fFrameCurrent = 0.f;
//	//		//이거떄매 좆씨팔 오류 나는거 였음.
//
//	//		SAVE_INFO temp = element->Sprite_Info;
//	//		temp.tFrameInfo.fFrameCurrent = 0.f;
//	//		WriteFile(hFile, &temp, sizeof(SAVE_INFO), &dwByte, nullptr);
//	//	}
//	//	AfxMessageBox(L"저장완료", MB_ICONASTERISK);
//	//	CloseHandle(hFile);
//	//}
//
//
//
//
//	UpdateData(FALSE);
//}
//
//
//void Spec_FormView::OnBnClickedButtonLayoutload()
//{
//	//레이아웃 로드
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//
//	CFileDialog Dlg(
//		TRUE,
//		nullptr,
//		nullptr,
//		OFN_OVERWRITEPROMPT,
//		L".bin|*bin||",
//		this);
//
//	TCHAR	szDlg_First[256] = L"";
//	GetCurrentDirectory(256, szDlg_First); //현재 문서 위치 받아오기
//	PathRemoveFileSpec(szDlg_First); //맨 마지막 파일 이름 지움 -> 프로젝트 파일 있는 곳
//	CString	 csDataFolderPath = szDlg_First;
//	//상위폴더 두개 지워주기
//	for (int i = 0; i < 1; ++i)
//	{
//		int pos = csDataFolderPath.ReverseFind('\\');
//		csDataFolderPath = csDataFolderPath.Left(pos);
//	}
//	csDataFolderPath += L"/Resource/Data";
//	Dlg.m_ofn.lpstrInitialDir = csDataFolderPath;
//
//
//	if (Dlg.DoModal())
//	{
//		CString csFilePath = Dlg.GetPathName();
//
//		HANDLE hFile = CreateFile(csFilePath, GENERIC_READ, 0, nullptr,
//			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
//
//		if (hFile == INVALID_HANDLE_VALUE)
//		{
//			AfxMessageBox(L"로드가 핸들 생성에서 실패했읍니다. ㅅㄱㅂ", MB_OK);
//		}
//
//		DWORD dwByte = 0;
//		
//		while (true)
//		{
//			Save_TerrainLayout	LoadTemp;
//
//			ReadFile(hFile, 
//				&LoadTemp, 
//				sizeof(Save_TerrainLayout), 
//				&dwByte, 
//				nullptr);
//
//			if (dwByte == 0)
//			{
//				break;
//			}
//			
//			wstring MeshPath;
//			wstring ObjName;
//
//			Function_String::TCHAR2wstring(LoadTemp.szMeshPath, MeshPath);
//			Function_String::TCHAR2wstring(LoadTemp.szObjName, ObjName);
//
//			Engine_Mother::Get_Instance()->Load_Mesh(MeshPath, ObjName);
//		
//			GameObject* pGameObject = INSTANTIATE(OBJECT_TAG_TERRAIN, ObjName);
//			pGameObject->Set_Position(LoadTemp.vPosition);
//			pGameObject->Set_Scale(LoadTemp.vScale);
//			pGameObject->Set_Rotation(LoadTemp.vRotation);
//
//			Mesh_Renderer::Desc Mesh_desc;
//			Mesh_desc.szMeshName = ObjName;
//			pGameObject->Add_Component<Mesh_Renderer>(&Mesh_desc);
//
//			SaveInfo::Desc Save_desc;
//			Save_desc.szMeshPath = MeshPath;
//			Save_desc.szObjName = ObjName;
//			pGameObject->Add_Component<SaveInfo>(&Save_desc);
//
//
//			m_MeshList_Combo.AddString(ObjName.c_str());
//
//			//sprite = new CSprite;
//			//sprite->Load(temp);
//			//wstring Path = sprite->Sprite_Info.szFilePath;
//			//CTextureManager::Get_Instance()->Insert_Texture(
//			//	sprite->type,
//			//	Path,
//			//	sprite->objKey,
//			//	sprite->objStateKey,
//			//	sprite->Sprite_Info.tFrameInfo.fFrameMax
//			//);
//
//
//
//			//CMainApp::Get_Instance()->Load(sprite);
//
//
//			//CString temp1 = sprite->objKey.c_str();
//			//CString temp2 = sprite->objStateKey.c_str();
//
//			//if (temp.iType == 1)
//			//{
//			//	m_NameCombo.AddString(temp1 + L"_" + temp2);
//			//}
//			//else if (temp.iType == 0)
//			//{
//			//	m_NameCombo.AddString(temp1);
//			//}
//
//		}
//
//		AfxMessageBox(L"레이아웃 로드 완료", MB_ICONASTERISK);
//		CloseHandle(hFile);
//
//	}
//
//
//
//	UpdateData(FALSE);
//}
#pragma endregion








