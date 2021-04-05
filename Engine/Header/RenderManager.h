#pragma once

#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include "Engine_Include.h"
#include "Renderer.h"
#include "Text.h"

class RenderManager
{	
	
	Declare_Singleton(RenderManager)

private:
	RenderManager();
	~RenderManager();

public:
	void Initialize();
	void Render();
	void Release();

private:
	void Render_Priority();
	void Render_NonAlpha();
	void Render_Alpha();
	void Render_UI();

public: /* Functions */
	HRESULT Update_ViewPort();

	
public: /* Get */


public: /* Set */
	void Insert_RenderingList(Renderer * _renderer, int = 0);

private:
	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;

	map<int, list<Renderer*>> m_RenderingList;
	//vector<Renderer*>			m_RenderingList;

	
	


#ifdef _DEBUG
public:
	void Render_DEBUG();
	void Set_FPSText(Text* _text)
	{
		m_pText = _text;
	};
	void Set_Script(const wstring& _script)
	{	
		m_pText->Set_Script(_script);
	};

private:
	LPDIRECT3DDEVICE9		m_pDX9_Device_DEBUG = nullptr;
	Text* m_pText = nullptr;
#endif//_DEBUG
};

#endif //_RENDER_MANAGER_H_