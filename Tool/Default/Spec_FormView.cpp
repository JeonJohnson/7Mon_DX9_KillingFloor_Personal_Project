// Spec_FormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "Spec_FormView.h"
#include "Engine_Mother.h"
#include "Mesh_Renderer.h"
#include "GameObject.h"

// Spec_FormView

IMPLEMENT_DYNCREATE(Spec_FormView, CFormView)

Spec_FormView::Spec_FormView()
	: CFormView(IDD_SPEC_FORMVIEW)
	, m_PosX_Edit(_T(""))
	, m_PosY_Edit(_T(""))
	, m_PosZ_Edit(_T(""))
	, m_ScaleX_Edit(_T(""))
	, m_ScaleY_Edit(_T(""))
	, m_ScaleZ_Edit(_T(""))
	, m_RotX_Edit(_T(""))
	, m_RotY_Edit(_T(""))
	, m_RotZ_Edit(_T(""))
{



}

Spec_FormView::~Spec_FormView()
{
}

void Spec_FormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MeshList, m_MeshList_Combo);


	DDX_Text(pDX, IDC_EDIT_PosX, m_PosX_Edit);
	DDX_Text(pDX, IDC_EDIT_PosY, m_PosY_Edit);
	DDX_Text(pDX, IDC_EDIT_PosZ, m_PosZ_Edit);
	DDX_Text(pDX, IDC_EDIT_ScaleX, m_ScaleX_Edit);
	DDX_Text(pDX, IDC_EDIT_ScaleY, m_ScaleY_Edit);
	DDX_Text(pDX, IDC_EDIT_ScaleZ, m_ScaleZ_Edit);
	DDX_Text(pDX, IDC_EDIT_RotX, m_RotX_Edit);
	DDX_Text(pDX, IDC_EDIT_RotY, m_RotY_Edit);
	DDX_Text(pDX, IDC_EDIT_RotZ, m_RotZ_Edit);
}

BEGIN_MESSAGE_MAP(Spec_FormView, CFormView)

	ON_BN_CLICKED(IDC_BUTTON_MeshLoad, &Spec_FormView::OnBnClickedButtonMeshload)
	ON_CBN_SELCHANGE(IDC_COMBO_MeshList, &Spec_FormView::OnCbnSelchangeComboMeshlist)
	ON_EN_CHANGE(IDC_EDIT_PosX, &Spec_FormView::OnEnChangeEditPosx)
	ON_EN_CHANGE(IDC_EDIT_PosY, &Spec_FormView::OnEnChangeEditPosy)
	ON_EN_CHANGE(IDC_EDIT_PosZ, &Spec_FormView::OnEnChangeEditPosz)
	ON_EN_CHANGE(IDC_EDIT_ScaleX, &Spec_FormView::OnEnChangeEditScalex)
	ON_EN_CHANGE(IDC_EDIT_ScaleY, &Spec_FormView::OnEnChangeEditScaley)
	ON_EN_CHANGE(IDC_EDIT_ScaleZ, &Spec_FormView::OnEnChangeEditScalez)
	ON_EN_CHANGE(IDC_EDIT_RotX, &Spec_FormView::OnEnChangeEditRotx)
	ON_EN_CHANGE(IDC_EDIT_RotY, &Spec_FormView::OnEnChangeEditRoty)
	ON_EN_CHANGE(IDC_EDIT_RotZ, &Spec_FormView::OnEnChangeEditRotz)
	ON_BN_CLICKED(IDC_BUTTON_TransReset, &Spec_FormView::OnBnClickedButtonTransreset)
	ON_BN_CLICKED(IDC_BUTTON_CameraReset, &Spec_FormView::OnBnClickedButtonCamerareset)

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
	cs.cx = 320;
	cs.cy = 720;
	return CFormView::PreCreateWindow(cs);
}

void Spec_FormView::Update_Info()
{
	UpdateData(TRUE);

	if (m_pSelectObject != nullptr)
	{
		m_vPos = m_pSelectObject->Get_Position();
		m_vScale = m_pSelectObject->Get_Scale();
		m_vRot = m_pSelectObject->Get_Transform()->Get_Rotation_Euler();

		m_PosX_Edit.Format(L"%.2f", m_vPos.x);
		m_PosY_Edit.Format(L"%.2f", m_vPos.y);
		m_PosZ_Edit.Format(L"%.2f", m_vPos.z);

		m_ScaleX_Edit.Format(L"%.2f", m_vScale.x);
		m_ScaleY_Edit.Format(L"%.2f", m_vScale.y);
		m_ScaleZ_Edit.Format(L"%.2f", m_vScale.z);

		m_RotX_Edit.Format(L"%.2f", m_vRot.x);
		m_RotY_Edit.Format(L"%.2f", m_vRot.y);
		m_RotZ_Edit.Format(L"%.2f", m_vRot.z);
	
	}
	
	UpdateData(FALSE);
}

// Spec_FormView 메시지 처리기입니다.

void Spec_FormView::OnBnClickedButtonMeshload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CFileDialog Dlg(
		TRUE,
		nullptr,
		nullptr,
		OFN_OVERWRITEPROMPT,
		L".X|*.X",
		this);


	//1. 매쉬 로드 
	//리소스 폴더 찾아서 Modal 기본 폴더로 해주기.
	TCHAR	szDlg_First[256] = L"";
	GetCurrentDirectory(256, szDlg_First);
	PathRemoveFileSpec(szDlg_First);
	CString	 csResourcePath = szDlg_First;
	//상위폴더 두개 지워주기
	for (int i = 0; i < 1; ++i)
	{
		int pos = csResourcePath.ReverseFind('\\');
		csResourcePath = csResourcePath.Left(pos);
	}
	csResourcePath += L"\\Resource";
	Dlg.m_ofn.lpstrInitialDir = csResourcePath;

	//wstring szFilePath; //전체 주소.
	//wstring szFileName; //파일 이름만 저장할 (오브젝트 네임으로 쓸 예정.)
	//wstring szRelativePath; //그 

	wstring szMeshPath;
	wstring szMeshRelativePath;
	wstring szMeshName;
	//wstring szTexturePath;
	//wstring szTextureName;
	wstring szObjName;

	wstring temp = L"../../Resource/";
	int len = (int)temp.length();

	if (Dlg.DoModal() == IDOK)
	{
		szMeshPath = Dlg.GetPathName(); //절대경로로 받아옴.
		szMeshName = Dlg.GetFileName();

		szMeshRelativePath = szMeshPath;
		//int findpos = szMeshRelativePath.find(L"Resource\\");
		szMeshRelativePath.erase(0, szMeshRelativePath.find(L"Resource\\")+9);
		//이제 텍스쳐는 매쉬 내부에서 XFile에 있는 걸로 알아서 불러올 꺼임.  
		//szTextureName = szMeshName;
		//szTextureName.replace(szMeshName.find(L".X"), 2, L".png");

		szObjName = szMeshName;
		szObjName.erase(szObjName.find(L".X"), szObjName.length());
		//PathRemoveExtensionW((LPWSTR)szObjName.c_str());
		//지금 이거 .자리에 \0을 넣는거지 그 뒤에걸 erase해주지는 않네... ㅁㅊ새기

		//주소값 '\\'을 '/'로 바꾸기
		int iPos = -1;
		while (true)
		{
			iPos = szMeshRelativePath.find(L"\\");
			if (iPos == string::npos)
			{
				break;
			}

			szMeshRelativePath.replace(iPos, 1, L"/");		
		}
		//로드할때는 리소스밑에 있는 폴더명으로 넣 어줘야함.
		Engine_Mother::Get_Instance()->Load_Mesh(szMeshRelativePath,szObjName);
		GameObject* pTempObject = INSTANTIATE(0, szObjName);

		Mesh_Renderer::Desc Mesh_desc;
		Mesh_desc.szMeshName = szObjName;

		pTempObject->Add_Component<Mesh_Renderer>(&Mesh_desc);

		m_MeshList_Combo.AddString(szObjName.c_str());

	}
	else
	{

	}




	UpdateData(FALSE);
}


void Spec_FormView::OnCbnSelchangeComboMeshlist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_iMeshList_Index = m_MeshList_Combo.GetCurSel();
	m_MeshList_Combo.GetLBText(m_iMeshList_Index, m_csSelMeshName);

	//m_pSelectObject = EngineFunction->Get_GameObjectbyName(m_csSelMeshName.operator LPCWSTR());
	m_pSelectObject = EngineFunction->Get_GameObject(0,m_csSelMeshName.operator LPCWSTR());
	assert(L"GameObject find Failed at ComboBox"&&m_pSelectObject);

	m_vPos = m_pSelectObject->Get_Position();
	m_vScale = m_pSelectObject->Get_Scale();
	m_vRot = m_pSelectObject->Get_Transform()->Get_Rotation_Euler();



	UpdateData(FALSE);
}


void Spec_FormView::OnEnChangeEditPosx()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	if (m_pSelectObject != nullptr) 
	{
		m_vPos.x = atof((CStringA)m_PosX_Edit);

		m_pSelectObject->Set_Position(m_vPos);
	}
	UpdateData(FALSE);
}


void Spec_FormView::OnEnChangeEditPosy()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vPos.y = atof((CStringA)m_PosY_Edit);

		m_pSelectObject->Set_Position(m_vPos);
	}
	UpdateData(FALSE);
}


void Spec_FormView::OnEnChangeEditPosz()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vPos.z = atof((CStringA)m_PosZ_Edit);

		m_pSelectObject->Set_Position(m_vPos);
	}
	UpdateData(FALSE);
}


void Spec_FormView::OnEnChangeEditScalex()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_pSelectObject != nullptr)
	{
		m_vScale.x = atof((CStringA)m_ScaleX_Edit);

		m_pSelectObject->Set_Scale(m_vScale);
	}
	UpdateData(FALSE);
}


void Spec_FormView::OnEnChangeEditScaley()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vScale.y = atof((CStringA)m_ScaleY_Edit);

		m_pSelectObject->Set_Scale(m_vScale);
	}
	UpdateData(FALSE);
}


void Spec_FormView::OnEnChangeEditScalez()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vScale.z = (float)atof((CStringA)m_ScaleZ_Edit);

		m_pSelectObject->Set_Scale(m_vScale);
	}
	UpdateData(FALSE);
}


void Spec_FormView::OnEnChangeEditRotx()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vRot.x = atof((CStringA)m_RotX_Edit);

		m_pSelectObject->Set_RotationX(m_vRot.x);
	}

	UpdateData(FALSE);
}


void Spec_FormView::OnEnChangeEditRoty()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vRot.y = atof((CStringA)m_RotY_Edit);

		m_pSelectObject->Set_RotationY(m_vRot.y);
	}
	UpdateData(FALSE);
}


void Spec_FormView::OnEnChangeEditRotz()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vRot.z = atof((CStringA)m_RotZ_Edit);

		m_pSelectObject->Set_RotationZ(m_vRot.z);
	}
	UpdateData(FALSE);
}


void Spec_FormView::OnBnClickedButtonTransreset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		if (IDYES == AfxMessageBox(L"ㄹㅇ루다가 트랜스폼 초기화 허쉴..?", MB_YESNO | MB_ICONQUESTION))
		{
			m_vPos = { 0.f,0.f,0.f };
			m_vScale = { 1.f, 1.f, 1.f };
			m_vRot = { 0.f,0.f,0.f };

			m_pSelectObject->Set_Position(m_vPos);
			m_pSelectObject->Set_Scale(m_vScale);
			m_pSelectObject->Set_Rotation(m_vRot.x, m_vRot.y, m_vRot.z);

		}
		else { return; }
	}
	else { AfxMessageBox(L"초기화 할 거 없는데 지랄 ㄴ", MB_OK); }
	UpdateData(FALSE);
}


void Spec_FormView::OnBnClickedButtonCamerareset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);


	UpdateData(FALSE);
}


