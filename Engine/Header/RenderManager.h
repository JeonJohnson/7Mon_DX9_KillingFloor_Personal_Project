#pragma once

#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include "Engine_Include.h"
#include "Renderer.h"

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

public:
	void Insert_RenderingList(Renderer * _renderer, int = 0);

private:
	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;

	map<int, list<Renderer*>> m_RenderingList;
	//vector<Renderer*>			m_RenderingList;

#ifdef _DEBUG
public:

	void Render_DEBUG();

private:
	LPDIRECT3DDEVICE9		m_pDX9_Device_DEBUG = nullptr;
#endif//_DEBUG
};

#endif //_RENDER_MANAGER_H_