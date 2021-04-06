#pragma once

#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include "Engine_Include.h"

#include "UI.h"
#include "Sprite.h"
#include "Text.h"

class DLL_STATE UIManager
{
	Declare_Singleton(UIManager)

private:
	UIManager();
	~UIManager();

public:
	void Initailize();
	void Update();
	void LateUpdate();
	void ReadyRender();
	void Render();
	void Release();

public: /* function */
	void Release_Scene();

public: /* Get */

public: /* Set */
	HRESULT Insert_UI(UI* _pUi, const wstring& _name);

	//bool nameFind(const wstring& _vecName, const wstring& _insertName)
	//{
	//	if (_vecName == _insertName)
	//	{
	//		return true;
	//	}
	//}
	
private:
	//LPDIRECT3DDEVICE9			m_pDX9_Device = nullptr;
	//LPD3DXSPRITE				m_pDX9_Sprite = nullptr;

	vector<pair<wstring, UI*>> m_vecUIList;

	//vector<tuple<wstring, Sprite*, Text*>> m_vecUIList;

};

#endif //_UI_MANAGER_H_