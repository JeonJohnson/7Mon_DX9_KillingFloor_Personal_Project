#include "..\Header\Engine_Mother.h"
#include "SaveInfo_NaviMesh.h"
#include "NaviPoint.h"
#include "NaviMesh.h"
#include "NaviCell.h"

Engine_Mother*	Engine_Mother::m_Instance = nullptr;

Engine_Mother * Engine_Mother::Get_Instance()
{
	if (!m_Instance)
	{
		m_Instance = new Engine_Mother;
	}
	return m_Instance;
}

void Engine_Mother::Destroy_Instance()
{
	if (m_Instance)
	{
		delete	m_Instance;
		m_Instance = nullptr;
	}
}

Engine_Mother::Engine_Mother()
{
	m_pDeviceManager		= DeviceManager::Get_Instance();
	m_pTimeManager			= TimeManager::Get_Instance();
	m_pInputManager			= InputManager::Get_Instance();
	m_pResourceManager		= ResourceManager::Get_Instance();

	m_pGameObjectManager	= GameObjectManager::Get_Instance();
	m_pUiManager			= UIManager::Get_Instance();
	m_pLineManager			= LineManager::Get_Instance();
	m_pLightManager			= LightManager::Get_Instance();
	m_pRenderManager		= RenderManager::Get_Instance();
	m_pSceneManager			= SceneManager::Get_Instance();

#ifdef _DEBUG		
	m_pDebugManager			= DebugManager::Get_Instance();

#endif //_DEBUG
}

Engine_Mother::~Engine_Mother()
{
	
}


void Engine_Mother::Initialize(Desc * _desc)
{
	m_pDeviceManager->Initialize(_desc->hWnd, _desc->wincx, _desc->wincy, _desc->window);
#ifdef _DEBUG
	m_pDeviceManager->Ready_DX9_Device_DEBUG(_desc->hWnd_DEBUG,
		_desc->wincx_DEBUG, _desc->wincy_DEBUG);
	m_pDebugManager->Initialize();
#endif //_DEBUG
	m_pTimeManager->Time_Init();
	m_pInputManager->Initialize(_desc->hInst, _desc->hWnd, false);
	m_pResourceManager->Initialize();

	m_pGameObjectManager->Initailize(_desc->Object_Tag_MaxCount);
	
	m_pUiManager->Initailize();
	m_pLineManager->Initialize();
	m_pLightManager->Initialize();
	m_pRenderManager->Initialize();
	m_pSceneManager->Initialize();
	
}

void Engine_Mother::Initialize(Desc_Tool * _desc)
{
	m_pDeviceManager->Initialize(_desc->hWnd_forDevice, _desc->wincx, _desc->wincy, true);
	m_pTimeManager->Time_Init();
	m_pInputManager->Initialize(_desc->hInst, _desc->hWnd_forDInput, true);
	m_pResourceManager->Initialize();

	m_pGameObjectManager->Initailize(_desc->Object_Tag_MaxCount);
	m_pUiManager->Initailize();
	m_pLineManager->Initialize();
	m_pLightManager->Initialize();
	m_pRenderManager->Initialize();
	m_pSceneManager->Initialize();
}

void Engine_Mother::Process()
{
	m_pTimeManager->Time_Update();
	m_pInputManager->Update();

	m_pSceneManager->Update();
	m_pSceneManager->LateUpdate();
	m_pSceneManager->ReadyRender();
	//m_pRenderManager->Render_DEBUG();
	//Collision
	m_pSceneManager->Render();
}

void Engine_Mother::Release()
{
	m_pSceneManager->Destroy_Instance();
	m_pRenderManager->Destroy_Instance();
	m_pLightManager->Destroy_Instance();
	m_pLineManager->Destroy_Instance();
	m_pUiManager->Destroy_Instance();
	m_pGameObjectManager->Destroy_Instance();
	m_pInputManager->Destroy_Instance();
	m_pTimeManager->Destroy_Instance();

	m_pResourceManager->Destroy_Instance();

#ifdef _DEBUG
	m_pDebugManager->Destroy_Instance();
#endif //_DEBUG

	m_pDeviceManager->Destroy_Instance();
}

LPDIRECT3DDEVICE9 Engine_Mother::Get_Dx9_Device() const
{
	return m_pDeviceManager->Get_DX9_Device();
}

LPD3DXSPRITE Engine_Mother::Get_DX9_Sprite() const
{
	return m_pDeviceManager->Get_DX9_Sprite();
}

Vector2 Engine_Mother::Get_WindowSize() const
{
	return m_pDeviceManager->Get_WindowSize();
}

#ifdef _DEBUG
LPDIRECT3DDEVICE9 Engine_Mother::Get_Dx9_Device_DEBUG() const
{
	return m_pDeviceManager->Get_DX9_Device_DEBUG();
}
Vector2 Engine_Mother::Get_WindowSize_DEBUG()
{
	return m_pDeviceManager->Get_WindowSize_DEBUG();
}
#endif //_DEBUG


float Engine_Mother::Get_fDeltaTime() const
{
	return m_pTimeManager->Get_fTime();
}

double Engine_Mother::Get_dDeltaTime() const
{
	return m_pTimeManager->Get_dTime();
}

int Engine_Mother::Get_FPS() const
{
	return m_pTimeManager->Get_FPS();
}

bool Engine_Mother::GetKeyUp(const BYTE & _keyValue)
{
	return m_pInputManager->Get_Instance()->GetKeyUp(_keyValue);
}

bool Engine_Mother::GetKeyDown(const BYTE & _keyValue)
{
	return m_pInputManager->Get_Instance()->GetKeyDown(_keyValue);
}

bool Engine_Mother::GetKeyPress(const BYTE & _keyValue)
{
	return m_pInputManager->Get_Instance()->GetKeyPress(_keyValue);
}

bool Engine_Mother::GetMouseUp(int _MouseVal)
{
	return m_pInputManager->Get_Instance()->GetMouseUp(_MouseVal);
}

bool Engine_Mother::GetMouseDown(int _MouseVal)
{
	return m_pInputManager->Get_Instance()->GetMouseDown(_MouseVal);
}

bool Engine_Mother::GetMousePress(int _MouseVal)
{
	return m_pInputManager->Get_Instance()->GetMousePress(_MouseVal);
}

int Engine_Mother::GetMouseMove(int _MouseMove)
{
	return m_pInputManager->Get_Instance()->GetMouseMove(_MouseMove);
}

LONG Engine_Mother::GetMouseMoveX()
{
	return m_pInputManager->Get_Instance()->GetMouseMoveX();
}

LONG Engine_Mother::GetMouseMoveY()
{
	return m_pInputManager->Get_Instance()->GetMouseMoveY();
}

POINT Engine_Mother::Get_MousePos()
{
	return m_pInputManager->Get_MousePos();
}

POINT Engine_Mother::Get_MousePos(HWND _hWnd)
{
	return m_pInputManager->Get_MousePos(_hWnd);
}

void Engine_Mother::Add_Scene(const wstring & _wName, Scene * _pScene)
{
	m_pSceneManager->Insert_Scene(_wName, _pScene);
}

void Engine_Mother::Load_Scene(const wstring & _wName)
{
	m_pSceneManager->Load_Scene(_wName);
}

void Engine_Mother::Init_Scene(const wstring & _wName)
{
	m_pSceneManager->Set_FirstScene(_wName);
}

GameObject * Engine_Mother::Get_GameObject(int _tag, const wstring & _name)
{
	return m_pGameObjectManager->Get_GameObject(_tag, _name);
}

GameObject * Engine_Mother::Get_GameObjectbyName(const wstring & _name)
{
	return m_pGameObjectManager->Get_GameObjectbyName(_name);
}

GameObject * Engine_Mother::Get_GameObjectbyTag(int _tag)
{
	return m_pGameObjectManager->Get_GameObjectbyTag(_tag);
}

list<GameObject*> Engine_Mother::Get_GameObjectListbyTag(int _tag)
{
	return m_pGameObjectManager->Get_GameObjectListbyTag(_tag);
}

Camera * Engine_Mother::Get_MainCamera()
{
	if (m_pGameObjectManager->Get_GameObjectbyTag(2) == nullptr)
	{
		return nullptr;
	}
	else 
	{ 
		return m_pGameObjectManager->Get_GameObjectbyTag(2)->Get_Component<Camera>(); 
	}

}

Line* Engine_Mother::Create_Line(const Vector3 & _vStart, const Vector3 & _vDest, D3DXCOLOR _tColor, float _fWidth)
{
	return m_pLineManager->Create_Line(
		_vStart, _vDest,
		_tColor, _fWidth);
}

void Engine_Mother::Insert_Line(Line * _pLine)
{
	m_pLineManager->Insert_Line(_pLine);
}

#ifdef _DEBUG
void Engine_Mother::DebugLog(const wstring & _log)
{
	m_pDebugManager->DebugLog(_log);
}
#endif //_debug

void Engine_Mother::Insert_Light(D3DLIGHT9 * _pLight, const wstring & _Name)
{
	m_pLightManager->Insert_Light(_pLight, _Name);
}

void Engine_Mother::Load_Texture(const wstring & _wPath, const wstring & _wName)
{
	m_pResourceManager->Load_Texture(_wPath, _wName);
}

//void Engine_Mother::Load_StaticMesh(const wstring & _szMeshPath, const wstring & _szTexPath, const wstring & _szMeshName)
//{
//	m_pResourceManager->Load_StaticMesh(_szMeshPath, _szTexPath, _szMeshName);
//}
//
//void Engine_Mother::Load_AnimMesh(const wstring & _szMeshPath, const wstring & _szMeshName)
//{
//	m_pResourceManager->Load_AnimMesh(_szMeshPath, _szMeshName);
//}

void Engine_Mother::Load_Mesh(const wstring & _szMeshPath, const wstring & _szMeshName)
{
	m_pResourceManager->Load_Mesh(_szMeshPath, _szMeshName);
}

void Engine_Mother::Load_TerrainLayout(const wstring & _szDataPath)
{
	wstring szDataFullpath = ResourceManager::Get_Instance()->Get_ResourceFolderPath() + _szDataPath;

	//m_pResourceManager->Load_TerrainLayout(_szDataPath);
	HANDLE	hFile = CreateFile(szDataFullpath.c_str(),
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,nullptr);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		assert(0 && L"handle has error at TerrainLayout Load");
	}

	DWORD	dwByte = 0;

	while (true)
	{
		Save_TerrainLayout LoadTemp;

		ReadFile(hFile, &LoadTemp, sizeof(Save_TerrainLayout), &dwByte, nullptr);

		if (dwByte == 0)
		{
#ifdef _DEBUG
			MsgBox(L"Don't Worried! :)", L"Terrain Layout Load is Succeed!");

#endif //_DEBUG
			break;
		}

		wstring MeshPath;
		wstring ObjName;

		Function_String::TCHAR2wstring(LoadTemp.szMeshPath, MeshPath);
		Function_String::TCHAR2wstring(LoadTemp.szObjName, ObjName);

		Engine_Mother::Get_Instance()->Load_Mesh(MeshPath, ObjName);

		GameObject* pGameObject = INSTANTIATE(1, ObjName);
		pGameObject->Set_Position(LoadTemp.vPosition);
		pGameObject->Set_Scale(LoadTemp.vScale);
		pGameObject->Set_Rotation(LoadTemp.vRotation);

		Mesh_Renderer::Desc Mesh_desc;
		Mesh_desc.szMeshName = ObjName;
		pGameObject->Add_Component<Mesh_Renderer>(&Mesh_desc);

	}


	CloseHandle(hFile);

}

void Engine_Mother::Load_NaviMeshData(const wstring & _szDataPath)
{
	wstring szDataFullPath = m_pResourceManager->Get_ResourceFolderPath() + _szDataPath;

	HANDLE	hFile = CreateFile(szDataFullPath.c_str(),
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		assert(0 && L"Handle Create failed to NaviMeshData");
	}

	DWORD	dwByte = 0;
	SaveInfo_NaviMesh LoadNaviMeshData;

	while(true)
	{
		int iPointCount;
		ReadFile(hFile,
			&iPointCount,
			sizeof(int),
			&dwByte,
			nullptr);

		if (dwByte == 0)
		{
			break;
		}

		Vector3*		arrPointPosition = new Vector3[iPointCount];
		for (int i = 0; i < iPointCount; ++i)
		{
			ReadFile(hFile,
				&arrPointPosition[i],
				sizeof(Vector3),
				&dwByte,
				nullptr);
		}

		//Cell
		int iCellCount;
		ReadFile(hFile,
			&iCellCount,
			sizeof(int),
			&dwByte,
			nullptr);

		Vector3*		arrCellPointIndex = new Vector3[iCellCount];
		for (int i = 0; i < iCellCount; ++i)
		{
			ReadFile(hFile,
				&arrCellPointIndex[i],
				sizeof(Vector3),
				&dwByte,
				nullptr);
		}

		//setting
		LoadNaviMeshData.Setting(iPointCount, iCellCount);
		LoadNaviMeshData.arrPointPosition = arrPointPosition;
		LoadNaviMeshData.arrCellPointIndex = arrCellPointIndex;

	}
	CloseHandle(hFile);

	Load_Mesh(L"Test/StaticMesh/DebugSphere.X", L"DebugSphere");

	//Create Points
	vector<NaviPoint*> vecPoint;
	for (int i = 0; i < LoadNaviMeshData.iPointCount; ++i)
	{	
		Vector3 _WorldPos = LoadNaviMeshData.arrPointPosition[i];

		GameObject* pPointObj = INSTANTIATE(5, L"NaviPoint_" + to_wstring(i));
		pPointObj->Set_Position(_WorldPos);

		Mesh_Renderer::Desc Render_Desc;
		Render_Desc.szMeshName = L"DebugSphere";
		pPointObj->Add_Component<Mesh_Renderer>(&Render_Desc);

		NaviPoint::Desc NaviPoint_Desc;
		NaviPoint_Desc.Pos = _WorldPos;
		NaviPoint_Desc.Index = i;
		pPointObj->Add_Component<NaviPoint>(&NaviPoint_Desc);
		
		NaviPoint* tempPoint = pPointObj->Get_NewComponent<NaviPoint>();

		vecPoint.emplace_back(tempPoint);
	}

	NaviMesh* tempNaviMesh = new NaviMesh;
	//CreateCell & Setting
	for (int i = 0; i < LoadNaviMeshData.iCellCount; ++i)
	{
		NaviCell* Cell = new NaviCell;
		Cell->Set_CellIndex(i);
		Vector3		PointIndex = LoadNaviMeshData.arrCellPointIndex[i];

		for (int j = 0; j < 3; ++j)
		{
			switch (j)
			{
			case 0:
			{
				Cell->Insert_NaviPoint(vecPoint[(int)PointIndex.x], j);
			}
			break;

			case 1:
			{
				Cell->Insert_NaviPoint(vecPoint[(int)PointIndex.y], j);
			}
			break;

			case 2:
			{
				Cell->Insert_NaviPoint(vecPoint[(int)PointIndex.z], j);
			}
			break;
			default:
				break;
			}
		}

		Cell->Setup_Lines();

		tempNaviMesh->Insert_NaviCell(Cell);
		tempNaviMesh->Link_Cells();
	}

	m_pResourceManager->Set_NaviMesh(tempNaviMesh);

#ifdef _DEBUG	
	MsgBox(L"Notice", L"NaviMesh Load Compelate");
#endif


}
