#include "../Header/UI.h"

#include "UIManager.h"

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

void UI::Render()
{
	if (m_pSprite)
	{
		m_pSprite->Render();
	}
	
	if (m_pText)
	{
		m_pText->Render();
	}
}

void UI::Release()
{
	if (m_pSprite)
	{
		m_pSprite->Release();

		delete m_pSprite;
		m_pSprite = nullptr;
	}

	if (m_pText)
	{
		m_pText->Release();

		delete m_pText;
		m_pText = nullptr;
	}
}

UI* UI::Instantiate_UI(const wstring & _wNameUI)
{
	UI* UIObj = new UI;
	assert(L"UIObj create failed" && UIObj);

	UIObj->Initialize();
	UIObj->m_wName = _wNameUI;

	if (FAILED(UIManager::Get_Instance()->Insert_UI(UIObj, _wNameUI)))
	{
		assert(0 && L"Ui name is aready exist");
	}

	return UIObj;
}

void UI::Destory_UI(UI * _pUi)
{
}

void UI::Delete_UiComponents()
{
}

const wstring & UI::Get_Name()const
{
	return m_wName;	
}

UI_Component * UI::Get_Sprite()
{
	return m_pSprite;
}

UI_Component * UI::Get_Text()
{
	return m_pText;
}

