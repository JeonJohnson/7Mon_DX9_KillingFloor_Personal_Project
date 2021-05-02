// ObjectTool_Dialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjectTool_Dialog.h"
#include "afxdialogex.h"
#include "..\..\Engine\Header\SaveInfo.h"
#include "..\..\Engine\Header\Mesh_Renderer.h"
#include "GameObject.h"


// ObjectTool_Dialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ObjectTool_Dialog, CDialogEx)

ObjectTool_Dialog::ObjectTool_Dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Object_Dialog, pParent)
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

ObjectTool_Dialog::~ObjectTool_Dialog()
{
}

void ObjectTool_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
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


BEGIN_MESSAGE_MAP(ObjectTool_Dialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_MeshList, &ObjectTool_Dialog::OnCbnSelchangeComboMeshlist)
	ON_BN_CLICKED(IDC_BUTTON_MeshLoad, &ObjectTool_Dialog::OnBnClickedButtonMeshload)
	ON_BN_CLICKED(IDC_BUTTON_DeleteList, &ObjectTool_Dialog::OnBnClickedButtonDeletelist)
	ON_EN_CHANGE(IDC_EDIT_PosX, &ObjectTool_Dialog::OnEnChangeEditPosx)
	ON_EN_CHANGE(IDC_EDIT_PosY, &ObjectTool_Dialog::OnEnChangeEditPosy)
	ON_EN_CHANGE(IDC_EDIT_PosZ, &ObjectTool_Dialog::OnEnChangeEditPosz)
	ON_EN_CHANGE(IDC_EDIT_ScaleX, &ObjectTool_Dialog::OnEnChangeEditScalex)
	ON_EN_CHANGE(IDC_EDIT_ScaleY, &ObjectTool_Dialog::OnEnChangeEditScaley)
	ON_EN_CHANGE(IDC_EDIT_ScaleZ, &ObjectTool_Dialog::OnEnChangeEditScalez)
	ON_EN_CHANGE(IDC_EDIT_RotX, &ObjectTool_Dialog::OnEnChangeEditRotx)
	ON_EN_CHANGE(IDC_EDIT_RotY, &ObjectTool_Dialog::OnEnChangeEditRoty)
	ON_EN_CHANGE(IDC_EDIT_RotZ, &ObjectTool_Dialog::OnEnChangeEditRotz)
	ON_BN_CLICKED(IDC_BUTTON_CameraReset, &ObjectTool_Dialog::OnBnClickedButtonCamerareset)
	ON_BN_CLICKED(IDC_BUTTON_TransReset, &ObjectTool_Dialog::OnBnClickedButtonTransreset)
	ON_BN_CLICKED(IDC_BUTTON_LayoutSave, &ObjectTool_Dialog::OnBnClickedButtonLayoutsave)
	ON_BN_CLICKED(IDC_BUTTON_LayoutLoad, &ObjectTool_Dialog::OnBnClickedButtonLayoutload)
END_MESSAGE_MAP()


// ObjectTool_Dialog �޽��� ó�����Դϴ�.




void ObjectTool_Dialog::Update_Info()
{
	UpdateData(TRUE);

	if (m_pSelectObject != nullptr)
	{
		m_MeshList_Combo.GetLBText(m_iMeshList_Index, m_csSelMeshName);

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
	else
	{
		m_PosY_Edit = L"��ü�� ������ �ֽʽÿ�.";
		m_PosX_Edit = L"��ü�� ������ �ֽʽÿ�.";
		m_PosZ_Edit = L"��ü�� ������ �ֽʽÿ�.";

		m_ScaleX_Edit = L"��ü�� ������ �ֽʽÿ�.";
		m_ScaleY_Edit = L"��ü�� ������ �ֽʽÿ�.";
		m_ScaleZ_Edit = L"��ü�� ������ �ֽʽÿ�.";

		m_RotX_Edit = L"��ü�� ������ �ֽʽÿ�.";
		m_RotY_Edit = L"��ü�� ������ �ֽʽÿ�.";
		m_RotZ_Edit = L"��ü�� ������ �ֽʽÿ�.";

	}

	UpdateData(FALSE);
}

void ObjectTool_Dialog::OnCbnSelchangeComboMeshlist()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_iMeshList_Index = m_MeshList_Combo.GetCurSel();
	m_MeshList_Combo.GetLBText(m_iMeshList_Index, m_csSelMeshName);

	//m_pSelectObject = EngineFunction->Get_GameObjectbyName(m_csSelMeshName.operator LPCWSTR());
	m_pSelectObject = EngineFunction->Get_GameObject(1, m_csSelMeshName.operator LPCWSTR());
	assert(L"GameObject find Failed at ComboBox"&&m_pSelectObject);

	m_vPos = m_pSelectObject->Get_Position();
	m_vScale = m_pSelectObject->Get_Scale();
	m_vRot = m_pSelectObject->Get_Transform()->Get_Rotation_Euler();



	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnBnClickedButtonMeshload()
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
	//���ҽ� ���� ã�Ƽ� Modal �⺻ ������ ���ֱ�.
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
	wstring szMeshRelativePath;
	wstring szMeshName;
	//wstring szTexturePath;
	//wstring szTextureName;
	wstring szObjName;

	wstring temp = L"../../Resource/";
	int len = (int)temp.length();

	if (Dlg.DoModal() == IDOK)
	{
		szMeshPath = Dlg.GetPathName(); //�����η� �޾ƿ�.
		szMeshName = Dlg.GetFileName();

		szMeshRelativePath = szMeshPath;
		//int findpos = szMeshRelativePath.find(L"Resource\\");
		szMeshRelativePath.erase(0, szMeshRelativePath.find(L"Resource\\") + 9);
		//���� �ؽ��Ĵ� �Ž� ���ο��� XFile�� �ִ� �ɷ� �˾Ƽ� �ҷ��� ����.  
		//szTextureName = szMeshName;
		//szTextureName.replace(szMeshName.find(L".X"), 2, L".png");

		szObjName = szMeshName;
		szObjName.erase(szObjName.find(L".X"), szObjName.length());
		//PathRemoveExtensionW((LPWSTR)szObjName.c_str());
		//���� �̰� .�ڸ��� \0�� �ִ°��� �� �ڿ��� erase�������� �ʳ�... ��������

		//�ּҰ� '\\'�� '/'�� �ٲٱ�
		size_t iPos = -1;
		while (true)
		{
			iPos = szMeshRelativePath.find(L"\\");
			if (iPos == string::npos)
			{
				break;
			}

			szMeshRelativePath.replace(iPos, 1, L"/");
		}
		//�ε��Ҷ��� ���ҽ��ؿ� �ִ� ���������� �� �������.
		Engine_Mother::Get_Instance()->Load_Mesh(szMeshRelativePath, szObjName);
		GameObject* pTempObject = INSTANTIATE(OBJECT_TAG_TERRAIN, szObjName);

		Mesh_Renderer::Desc Mesh_desc;
		Mesh_desc.szMeshName = szObjName;
		pTempObject->Add_Component<Mesh_Renderer>(&Mesh_desc);

		SaveInfo::Desc Save_desc;
		Save_desc.szMeshPath = szMeshRelativePath;
		Save_desc.szObjName = szObjName;
		pTempObject->Add_Component<SaveInfo>(&Save_desc);


		m_MeshList_Combo.AddString(szObjName.c_str());

#pragma region stringsTest
		//const TCHAR* tcTemp = L"";
		//TCHAR arrTemp[255];
		//tcTemp = (wchar_t*)szMeshRelativePath.c_str();
		//_tcscpy_s(arrTemp, tcTemp);
		//wstring wstrTemp;
		//Function_String::TCHAR2wstring(arrTemp, wstrTemp);

		//TCHAR arrTemp2[255] = L"";
		//Function_String::wstring2TCHAR(wstrTemp, arrTemp2);
		////strcpy_s((char*)arrTemp, strlen((char*)),(char*)tcTemp);
		////Function_String::wstring2TCHAR(szMeshRelativePath, tcTemp);

		//Save_TerrainLayout* pTempSaveInfo = new Save_TerrainLayout;
		//ZeroMemory(pTempSaveInfo, sizeof(Save_TerrainLayout));
		//Function_String::wstring2TCHAR(szMeshRelativePath, pTempSaveInfo->szMeshPath);
#pragma endregion
	}
	else
	{

	}




	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnBnClickedButtonDeletelist()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	if (m_pSelectObject == nullptr)
	{
		AfxMessageBox(L"�����Ұ� �����ϻ�", MB_OK | MB_ICONQUESTION);
	}
	else
	{
		if (IDYES == AfxMessageBox(L"������ٰ� �ش� ������Ʈ ���� �㽯?", MB_YESNO | MB_ICONQUESTION))
		{
			m_MeshList_Combo.DeleteString(m_iMeshList_Index);
			m_iMeshList_Index = -1;
			m_csSelMeshName = L"";

			GameObject::Destory(m_pSelectObject);
			m_pSelectObject = nullptr;

			AfxMessageBox(L"���� ����. ����", MB_OK | MB_ICONQUESTION);
		}
	}



	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnEnChangeEditPosx()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vPos.x = (float)atof((CStringA)m_PosX_Edit);

		m_pSelectObject->Set_Position(m_vPos);
	}
	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnEnChangeEditPosy()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vPos.y = (float)atof((CStringA)m_PosY_Edit);

		m_pSelectObject->Set_Position(m_vPos);
	}
	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnEnChangeEditPosz()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vPos.z = (float)atof((CStringA)m_PosZ_Edit);

		m_pSelectObject->Set_Position(m_vPos);
	}
	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnEnChangeEditScalex()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	if (m_pSelectObject != nullptr)
	{
		m_vScale.x = (float)atof((CStringA)m_ScaleX_Edit);

		m_pSelectObject->Set_Scale(m_vScale);
	}
	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnEnChangeEditScaley()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vScale.y = (float)atof((CStringA)m_ScaleY_Edit);

		m_pSelectObject->Set_Scale(m_vScale);
	}
	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnEnChangeEditScalez()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vScale.z = (float)atof((CStringA)m_ScaleZ_Edit);

		m_pSelectObject->Set_Scale(m_vScale);
	}
	UpdateData(FALSE);

}


void ObjectTool_Dialog::OnEnChangeEditRotx()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		m_vRot.x = (float)atof((CStringA)m_RotX_Edit);

		m_pSelectObject->Set_RotationX(m_vRot.x);
	}

	UpdateData(FALSE);

}


void ObjectTool_Dialog::OnEnChangeEditRoty()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	if (m_pSelectObject != nullptr)
	{
		m_vRot.y = (float)atof((CStringA)m_RotY_Edit);

		m_pSelectObject->Set_RotationY(m_vRot.y);
	}
	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnEnChangeEditRotz()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	if (m_pSelectObject != nullptr)
	{
		m_vRot.z = (float)atof((CStringA)m_RotZ_Edit);

		m_pSelectObject->Set_RotationZ(m_vRot.z);
	}

	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnBnClickedButtonCamerareset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}


void ObjectTool_Dialog::OnBnClickedButtonTransreset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	if (m_pSelectObject != nullptr)
	{
		if (IDYES == AfxMessageBox(L"������ٰ� Ʈ������ �ʱ�ȭ �㽯..?", MB_YESNO | MB_ICONQUESTION))
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
	else { AfxMessageBox(L"�ʱ�ȭ �� �� ���µ� ���� ��", MB_OK); }
	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnBnClickedButtonLayoutsave()
{
	//���̾ƿ� ����
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(FALSE,
		L"dat",
		L"",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data File(*.bin)|*.bin||", this);

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
	csResourcePath += L"/Resource/Data";
	Dlg.m_ofn.lpstrInitialDir = csResourcePath;

	if (Dlg.DoModal())
	{
		CString csFilePath = Dlg.GetPathName();

		HANDLE	hFile = CreateFile(csFilePath, GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox(L"������ �ڵ� �������� ���� �����ϴ�. ����", MB_OK);
			return;
		}

		DWORD	dwByte = 0;

		list<GameObject*> TempList = EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_TERRAIN);

		for (auto& obj : TempList)
		{
			Save_TerrainLayout SaveData = obj->Get_Component<SaveInfo>()->Get_TerrainSave();
			WriteFile(hFile, &SaveData, sizeof(Save_TerrainLayout), &dwByte, nullptr);
		}
		AfxMessageBox(L"����Ϸ�", MB_ICONASTERISK);
		CloseHandle(hFile);


	}


	//if (Dlg.DoModal())
	//{
	//	CString csFilePath = Dlg.GetPathName();

	//	HANDLE hFile = CreateFile(csFilePath, GENERIC_WRITE, 0, 0,
	//		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	//	if (INVALID_HANDLE_VALUE == hFile)
	//	{
	//		AfxMessageBox(L"�ڵ� �������� ������ ���� �����ϴ�. ����", MB_OK);
	//	}

	//	DWORD dwByte = 0;

	//	int iSize = CMainApp::Get_Instance()->Get_SortSize();
	//	int iCap = CMainApp::Get_Instance()->Get_VecSprite().capacity();

	//	for (auto& element : CMainApp::Get_Instance()->Get_VecSprite())
	//	{
	//		//element->Sprite_Info.tFrameInfo.fFrameCurrent = 0.f;
	//		//�̰ŋ��� ������ ���� ���°� ����.

	//		SAVE_INFO temp = element->Sprite_Info;
	//		temp.tFrameInfo.fFrameCurrent = 0.f;
	//		WriteFile(hFile, &temp, sizeof(SAVE_INFO), &dwByte, nullptr);
	//	}
	//	AfxMessageBox(L"����Ϸ�", MB_ICONASTERISK);
	//	CloseHandle(hFile);
	//}




	UpdateData(FALSE);
}


void ObjectTool_Dialog::OnBnClickedButtonLayoutload()
{
	//���̾ƿ� �ε�
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(
		TRUE,
		nullptr,
		nullptr,
		OFN_OVERWRITEPROMPT,
		L".bin|*bin||",
		this);

	TCHAR	szDlg_First[256] = L"";
	GetCurrentDirectory(256, szDlg_First); //���� ���� ��ġ �޾ƿ���
	PathRemoveFileSpec(szDlg_First); //�� ������ ���� �̸� ���� -> ������Ʈ ���� �ִ� ��
	CString	 csDataFolderPath = szDlg_First;
	//�������� �ΰ� �����ֱ�
	for (int i = 0; i < 1; ++i)
	{
		int pos = csDataFolderPath.ReverseFind('\\');
		csDataFolderPath = csDataFolderPath.Left(pos);
	}
	csDataFolderPath += L"/Resource/Data";
	Dlg.m_ofn.lpstrInitialDir = csDataFolderPath;


	if (Dlg.DoModal())
	{
		CString csFilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(csFilePath, GENERIC_READ, 0, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox(L"�ε尡 �ڵ� �������� ���������ϴ�. ������", MB_OK);
		}

		DWORD dwByte = 0;

		while (true)
		{
			Save_TerrainLayout	LoadTemp;

			ReadFile(hFile,
				&LoadTemp,
				sizeof(Save_TerrainLayout),
				&dwByte,
				nullptr);

			if (dwByte == 0)
			{
				break;
			}

			wstring MeshPath;
			wstring ObjName;

			Function_String::TCHAR2wstring(LoadTemp.szMeshPath, MeshPath);
			Function_String::TCHAR2wstring(LoadTemp.szObjName, ObjName);

			Engine_Mother::Get_Instance()->Load_Mesh(MeshPath, ObjName);

			GameObject* pGameObject = INSTANTIATE(OBJECT_TAG_TERRAIN, ObjName);
			pGameObject->Set_Position(LoadTemp.vPosition);
			pGameObject->Set_Scale(LoadTemp.vScale);
			pGameObject->Set_Rotation(LoadTemp.vRotation);

			Mesh_Renderer::Desc Mesh_desc;
			Mesh_desc.szMeshName = ObjName;
			pGameObject->Add_Component<Mesh_Renderer>(&Mesh_desc);

			SaveInfo::Desc Save_desc;
			Save_desc.szMeshPath = MeshPath;
			Save_desc.szObjName = ObjName;
			pGameObject->Add_Component<SaveInfo>(&Save_desc);


			m_MeshList_Combo.AddString(ObjName.c_str());

			//sprite = new CSprite;
			//sprite->Load(temp);
			//wstring Path = sprite->Sprite_Info.szFilePath;
			//CTextureManager::Get_Instance()->Insert_Texture(
			//	sprite->type,
			//	Path,
			//	sprite->objKey,
			//	sprite->objStateKey,
			//	sprite->Sprite_Info.tFrameInfo.fFrameMax
			//);



			//CMainApp::Get_Instance()->Load(sprite);


			//CString temp1 = sprite->objKey.c_str();
			//CString temp2 = sprite->objStateKey.c_str();

			//if (temp.iType == 1)
			//{
			//	m_NameCombo.AddString(temp1 + L"_" + temp2);
			//}
			//else if (temp.iType == 0)
			//{
			//	m_NameCombo.AddString(temp1);
			//}

		}

		AfxMessageBox(L"���̾ƿ� �ε� �Ϸ�", MB_ICONASTERISK);
		CloseHandle(hFile);

	}



	UpdateData(FALSE);
}
