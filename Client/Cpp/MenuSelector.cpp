#include "stdafx.h"
#include "..\Header\MenuSelector.h"
#include "UI.h"
#include "Sprite.h"


MenuSelector::MenuSelector(Desc * _desc)
{
	m_vecButtons[0] = _desc->StartButton;
	m_vecButtons[1] = _desc->ExitButton;
	m_pLoading = _desc->Loading;
}

MenuSelector::~MenuSelector()
{
}

void MenuSelector::Initialize()
{

}

void MenuSelector::Update()
{
	DEBUG_LOG(L"Cur Scene : MainMenu");

	for (int i = 0; i < 2; ++i)
	{
		if (m_vecButtons[i]->MouseOn())
		{
			((Sprite*)m_vecButtons[i]->Get_Sprite())->Set_Texture(L"HighLight");

			if (m_vecButtons[i]->Pressed())
			{
				((Sprite*)m_vecButtons[i]->Get_Sprite())->Set_Texture(L"Pressed");
			}
		}
		else 
		{
			((Sprite*)m_vecButtons[i]->Get_Sprite())->Set_Texture(L"Idle");
		}

		if (m_vecButtons[i]->ClickedUp())
		{
			switch (i)
			{
			case 0:
			{
				for (int i = 0; i < 2; ++i)
				{
					m_vecButtons[i]->Set_Active(false);
				}
				m_pLoading->Set_Active(true);
				EngineFunction->Load_Scene(L"Test_Scene"); 
			}
			break;

			case 1:
			{
				PostQuitMessage(0);
			}
			break;
			
			default:
				break;
			}
			
		}
	}

}

void MenuSelector::LateUpdate()
{
}

void MenuSelector::ReadyRender()
{
}

void MenuSelector::Release()
{
}
