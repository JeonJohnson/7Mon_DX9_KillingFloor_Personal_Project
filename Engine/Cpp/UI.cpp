#include "../Header/UI.h"

#include "UIManager.h"
#include "Sprite.h"
#include "InputManager.h"
#include "SoundManager.h"

void UI::Initialize()
{
	
}

void UI::Update()
{
	//Update_UITransform();

	if (m_bActive)
	{
		if (m_pSprite)
		{
			m_pSprite->Update();
		}

		if (m_pText)
		{
			m_pText->Update();
		}
	}
}


void UI::LateUpdate()
{

}

void UI::ReadyRender()
{
}

void UI::Render()
{
	//여기서 위치 정해주기, 넘겨주기/
	if (m_bActive)
	{
		Update_UITransform();

		if (m_pSprite)
		{
			m_pSprite->Render();
		}

		if (m_pText)
		{
			m_pText->Render();
		}
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

UI* UI::Instantiate_UI(const wstring & _wNameUI, bool _bIsStatic)
{
	UI* UIObj = new UI;
	assert(L"UIObj create failed" && UIObj);

	UIObj->Initialize();
	UIObj->m_wName = _wNameUI;

	if (_bIsStatic)
	{
		if (FAILED(UIManager::Get_Instance()->Insert_StaticUI(UIObj, _wNameUI)))
		{
			assert(0 && L"Ui name is aready exist");
		}
	}
	else
	{
		if (FAILED(UIManager::Get_Instance()->Insert_UI(UIObj, _wNameUI)))
		{
			assert(0 && L"Ui name is aready exist");
		}
	}

	return UIObj;
}

void UI::Destory_UI(UI * _pUi)
{
}

void UI::Delete_UiComponents()
{
}

void UI::Update_UITransform()
{

	if (m_pSprite == nullptr)
	{
		//m_fWidth = 0.f;
		//m_fHeight = 0.f;
	
			
		
	}
	else 
	{
		m_fWidth = (float)(static_cast<Sprite*>(m_pSprite)->Get_TextureInfo(0)->Width);
		m_fHeight = (float)(static_cast<Sprite*>(m_pSprite)->Get_TextureInfo(0)->Height);

		m_vCenter = { m_fWidth / 2.f , m_fHeight / 2.f , 0.f };
		
		m_tRect.left = (LONG)(m_vPosition.x - (m_vCenter.x * m_vScale.x));
		m_tRect.top = (LONG)(m_vPosition.y - (m_vCenter.y * m_vScale.y));
		m_tRect.right = (LONG)(m_vPosition.x + (m_vCenter.x	* m_vScale.x));
		m_tRect.bottom = (LONG)(m_vPosition.y + (m_vCenter.y * m_vScale.x));
	}



}

bool UI::Clikced()
{
	if (m_bButton)
	{
		if (InputManager::Get_Instance()->GetMouseDown(KEY_STATE_LMouse))
		{
			POINT MousePos = InputManager::Get_Instance()->Get_MousePos();

			if (MousePos.x >= m_tRect.left && MousePos.x <= m_tRect.right
				&& MousePos.y >= m_tRect.top && MousePos.y <= m_tRect.bottom)
			{
				SoundManager::Get_Instance()->Overlap_Play(L"UI_MouseClick.wav", 7);
				return true;

			} 
			return false;
		}
		return false;
	}
	return false;
}

bool UI::Pressed()
{
	if (m_bButton)
	{
		if (InputManager::Get_Instance()->GetMousePress(KEY_STATE_LMouse))
		{
			POINT MousePos = InputManager::Get_Instance()->Get_MousePos();

			if (MousePos.x >= m_tRect.left && MousePos.x <= m_tRect.right
				&& MousePos.y >= m_tRect.top && MousePos.y <= m_tRect.bottom)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool UI::ClickedUp()
{
	if (m_bButton)
	{
		if (InputManager::Get_Instance()->GetMouseUp(KEY_STATE_LMouse))
		{
			POINT MousePos = InputManager::Get_Instance()->Get_MousePos();

			if (MousePos.x >= m_tRect.left && MousePos.x <= m_tRect.right
				&& MousePos.y >= m_tRect.top && MousePos.y <= m_tRect.bottom)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}


bool UI::MouseOn()
{
	POINT MousePos = InputManager::Get_Instance()->Get_MousePos();

	if (MousePos.x >= m_tRect.left && MousePos.x <= m_tRect.right
		&& MousePos.y >= m_tRect.top && MousePos.y <= m_tRect.bottom)
	{
		if (!m_bMouseOver)
		{
			SoundManager::Get_Instance()->Overlap_Play(L"UI_MouseOver.wav", 7);
		}
		m_bMouseOver = true;
		return true;
	}
	else { 
		m_bMouseOver = false;
		return false; 
	
	}

	
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

const RECT& UI::Get_Rect() const
{
	return m_tRect;
}

const Vector3 & UI::Get_Position() const
{
	return m_vPosition;
}

const Vector3 & UI::Get_Scale() const
{
	return m_vScale;
}

const Vector3 & UI::Get_Rotation() const
{
	return m_vRotation;
}

const Vector3 & UI::Get_Center() const
{
	return m_vCenter;
}

void UI::Set_Active(bool _onoff)
{
	m_bActive = _onoff;
}

void UI::Set_Alive(bool _FalseIsDead)
{
	m_bAlive = _FalseIsDead;
}

void UI::Set_Button(bool _bButton)
{
	m_bButton = _bButton;
}

void UI::Set_Position(const Vector3 & _vPos)
{
	m_vPosition = _vPos;
}

void UI::Add_Position(const Vector3 & _vPos)
{
	m_vPosition += _vPos;
}

void UI::Set_Scale(const Vector3 & _vScale)
{
	m_vScale = _vScale;
}

void UI::Add_Scale(const Vector3 & _vScale)
{
	m_vScale += _vScale;
}

void UI::Set_Rotate(const Vector3 & _vRot)
{
	m_vRotation = _vRot;
}

void UI::Rotate(const Vector3 & _vRot)
{
	m_vRotation += _vRot;
}

void UI::Set_Rect(const RECT & _tRect)
{
	m_tRect = _tRect;
}

void UI::Set_Width(float _fWidth)
{
	m_fWidth = _fWidth;
}

void UI::Set_Height(float _fHeight)
{
	m_fHeight = _fHeight;
}


