#pragma once

#ifndef _ENGINE_MOTHER_H_
#define _ENGINE_MOTHER_H_

#include "Engine_Include.h"

#pragma region Managers
#include "DeviceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"

#include "DebugManager.h"
#pragma endregion

#pragma region Components
#include "GameObject.h"
#include "Component.h"

#include "Camera.h"

#include "VIBuffer_Renderer.h"

#include "UI.h"
#include "UI_Component.h"
#pragma endregion

class DLL_STATE Engine_Mother
{
	
private:
	static Engine_Mother*	m_Instance;

public:
	static Engine_Mother*	Get_Instance();
	static void				Destroy_Instance();
	
public:
	struct Desc
	{
		HINSTANCE	hInst = nullptr;
		HWND		hWnd = nullptr;
		UINT		wincx = 1280;
		UINT		wincy = 720;
		bool		window = false;

		_object_Tag			Object_Tag_MaxCount = 1;
		_render_Layer		Render_Layer_MaxCount = 1;
		_collision_Layer	Collision_Layer_MaxCount = 1;

#ifdef _DEBUG
		HWND	hWnd_DEBUG = nullptr;
		UINT	wincx_DEBUG = 425;
		UINT	wincy_DEBUG = 720;
#endif //_DEBUG
	};

public:
	struct Desc_Tool
	{
		HINSTANCE	hInst = nullptr;
		HWND		hWnd_forDevice = nullptr;
		HWND		hWnd_forDInput = nullptr;
		//MFC에서 다이렉트 인풋을 사용할려면 최상위 계층의 핸들이 필요함.
		//MainVeiw의 hwnd가 아니라 AfxGetMainWnd()->m_hWnd 를 넣어 줘야함.
		UINT		wincx = 1280;
		UINT		wincy = 720;

		_object_Tag			Object_Tag_MaxCount = 1;
		_render_Layer		Render_Layer_MaxCount = 1;
		_collision_Layer	Collision_Layer_MaxCount = 1;
	};

private:
	Engine_Mother();
	~Engine_Mother();

public:
	void Initialize(Desc* _desc);
	void Initialize(Desc_Tool* _desc);
	void Process();
	void Release();

public: /* Device Manager */
	LPDIRECT3DDEVICE9	Get_Dx9_Device() const;
	LPD3DXSPRITE		Get_DX9_Sprite() const;
#ifdef _DEBUG
	LPDIRECT3DDEVICE9	Get_Dx9_Device_DEBUG() const;
#endif //_DEBUG

public: /* Time Manager */
	float	Get_DeltaTime() const;
	int		Get_FPS() const;

public: /* Input Manager */
	bool	GetKeyUp(const BYTE& _keyValue);
	bool	GetKeyDown(const BYTE& _keyValue);
	bool	GetKeyPress(const BYTE& _keyValue);
	
	bool	GetMouseUp(int _MouseVal);
	bool	GetMouseDown(int _MouseVal);
	bool	GetMousePress(int _MouseVal);
	int		GetMouseMove(int _MouseMove);

	

public: /* Scene Manager */
	void Add_Scene(const wstring& _wName, Scene* _pScene);
	void Load_Scene(const wstring& _wName);
	void Init_Scene(const wstring& _wName);

public: /* Gameobject Manager */
	GameObject*			Get_GameObject(int _tag, const wstring& _name);
	GameObject*			Get_GameObjectbyName(const wstring& _name); //Return First Object
	GameObject*			Get_GameObjectbyTag(int _tag); //Return First Object
	list<GameObject*>	Get_GameObjectListbyTag(int _tag);

public: /* UI Manager */

public: /* Render Manager */

public: /* Resource Manager */
	void Load_Texture(const wstring & _wPath, const wstring& _wName);
	//void Load_StaticMesh(const wstring& _szMeshPath, const wstring& _szTexPath, const wstring& _szMeshName= L"");
	//void Load_AnimMesh(const wstring& _szMeshPath, const wstring& _szMeshName);
	void Load_Mesh(const wstring& _szMeshPath, const wstring& _szMeshName);

public:
		
private:
	DeviceManager*			m_pDeviceManager = nullptr;
	TimeManager*			m_pTimeManager = nullptr;
	InputManager*			m_pInputManager = nullptr;
	ResourceManager*		m_pResourceManager = nullptr;
	
	GameObjectManager*		m_pGameObjectManager = nullptr;
	UIManager*				m_pUiManager = nullptr;
	RenderManager*			m_pRenderManager = nullptr;
	SceneManager*			m_pSceneManager = nullptr;
	
	
};
#endif //_ENGINE_MOTHER_H_