#include "..\Header\UI.h"
#include "UIManager.h"



UI::UI()
{
}


UI::~UI()
{
}

void UI::Initialize()
{
}

void UI::Update()
{
}

void UI::LateUpdate()
{
}

void UI::ReadyRender()
{
}

void UI::Release()
{
}

UI* UI::Instantiate_UI(const wstring & _wNameUI)
{
	UI* UIObj = new UI;
	assert(L"UIObj create failed" && UIObj);

	UIObj->Initialize();
	UIObj->m_wName = _wNameUI;

	UIManager::Get_Instance()->Insert_UI(UIObj, _wNameUI);

	return UIObj;
}

void UI::Destory_UI(UI * _pUi)
{
}

const wstring & UI::Get_Name()const
{
	return m_wName;
}

UI_Component * UI::Get_Sprite()const
{
	return m_pSprite;
}

UI_Component * UI::Get_Text()const
{
	return m_pText;
}
