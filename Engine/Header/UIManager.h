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

public: /* function */

public: /* Get */

public: /* Set */
	void Insert_UI(UI* _pUi, const wstring& _name);
	
private:
	vector<pair<wstring, UI*>> m_vecUIList;

	//vector<tuple<wstring, Sprite*, Text*>> m_vecUIList;

};

#endif //_UI_MANAGER_H_