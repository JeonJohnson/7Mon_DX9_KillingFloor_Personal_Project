#include "../Header/UI.h"

#include "UIManager.h"
#include "Sprite.h"

void UI::Initialize()
{
	
}

void UI::Update()
{
	//Update_UITransform();

	if (m_pSprite)
	{
		m_pSprite->Update();
	}

	if (m_pText)
	{
		m_pText->Update();
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

void UI::Update_UITransform()
{

	if (m_pSprite == nullptr)
	{
		m_fWidth = 100.f;
		m_fHeight = 100.f;
	}
	else 
	{
		m_fWidth = (float)(static_cast<Sprite*>(m_pSprite)->Get_TextureInfo(0)->Width);
		m_fHeight = (float)(static_cast<Sprite*>(m_pSprite)->Get_TextureInfo(0)->Height);
	}

	m_vCenter = { m_fWidth / 2.f , m_fHeight / 2.f , 0.f };

	Vector3 Pos = m_vPosition;

	m_tRect.left = (LONG)(m_vPosition.x - m_vCenter.x);
	m_tRect.top = (LONG)(m_vPosition.y - m_vCenter.y);
	m_tRect.right = (LONG)(m_vPosition.x + m_vCenter.x);
	m_tRect.bottom= (LONG)(m_vPosition.y + m_vCenter.y);


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


