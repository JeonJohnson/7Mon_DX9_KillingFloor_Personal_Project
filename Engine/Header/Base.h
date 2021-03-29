#pragma once

#ifndef _BASE_H_
#define _BASE_H_

#include "Engine_Include.h"

#pragma region Managers
#include "DeviceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "RenderManager.h"

#include "DebugManager.h"
#pragma endregion

#pragma region Components
#include "GameObject.h"
#include "Component.h"


#include "VIBuffer_Renderer.h"
#pragma endregion

class DLL_STATE Base
{
	
private:
	static Base*	m_Instance;

public:
	static Base*	Get_Instance();
	static void		Destroy_Instance();
	
public:
	struct Desc
	{
		HWND	hWnd = nullptr;
		UINT	wincx = 1280;
		UINT	wincy = 720;
		bool	window = false;
	};

private:
	Base();
	~Base();

public:
	void Initialize(Desc* _desc);
	void Process();
	void Release();

public: /* Device Manager */
	LPDIRECT3DDEVICE9 Get_Dx9_Device() const;

public: /* Time Manager */
	float Get_DeltaTime() const;

public: /* Input Manager */

public: /* Gameobject Manager  */

public: /* Render Manager */

public: /* Scene Manager */
	void Add_Scene(const wstring& _wName, Scene* _pScene);
	void Load_Scene(const wstring& _wName);
	void Init_Scene(const wstring& _wName);

public:
		
private:
	DeviceManager*			m_pDeviceManager = nullptr;
	TimeManager*			m_pTimeManager = nullptr;
	InputManager*			m_pInputManager = nullptr;

	GameObjectManager*		m_pGameObjectManager = nullptr;
	RenderManager*			m_pRenderManager = nullptr;
	SceneManager*			m_pSceneManager = nullptr;
	
	
};
#endif