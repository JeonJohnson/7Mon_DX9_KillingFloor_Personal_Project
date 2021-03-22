#pragma once

#ifndef _BASE_H_
#define _BASE_H_

#include "Engine_Include.h"

#include "DeviceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "RenderManager.h"

class _declspec(dllexport) Base
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
	LPDIRECT3DDEVICE9 Get_Dx9Device() const;

public: /* Time Manager */
	float Get_DeltaTime() const;

public: /* Input Manager */

public: /*  */

public:
		
private:
	DeviceManager*			m_pDeviceManager = nullptr;
	TimeManager*			m_pTimeManager = nullptr;
	InputManager*			m_pInputManager = nullptr;

	RenderManager*			m_pRenderManager = nullptr;
	SceneManager*			m_pSceneManager = nullptr;
	
	
};
#endif