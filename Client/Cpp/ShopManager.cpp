#include "stdafx.h"
#include "..\Header\ShopManager.h"
#include "UI.h"
#include "Weapon_Status.h"

ShopManager* ShopManager::m_pInstance = nullptr;

ShopManager::ShopManager(Desc * _desc)
{
}

ShopManager::~ShopManager()
{
}

ShopManager * ShopManager::Get_Instance()
{
	if (m_pInstance == nullptr)
	{
		GameObject*	mgrObj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"StageManager");
		mgrObj->Add_Component<ShopManager>();
		//mgrObj->Add_Component<StateController>();

		m_pInstance = mgrObj->Get_NewComponent<ShopManager>();

		//m_pInstance->SetDontDestory(true);
	}

	return m_pInstance;
}

void ShopManager::Destory_Instance()
{
	if (m_pInstance)
	{
		GameObject::Destory(m_pInstance->Get_GameObject());
		m_pInstance = nullptr;
	}
}

void ShopManager::Initialize()
{
	{
		m_ShopFrame = INSTANTIATE_UI(L"Shop_Frame");
		m_ShopFrame->Set_Position(Vector3(640.f, 360.f, 0.f));
		m_ShopFrame->Set_Scale(Vector3(1.f, 1.f, 1.f));
		m_ShopFrame->Set_Active(false);

		Sprite::Desc FrameDesc;
		FrameDesc.TextureName = L"Shop_Frame";
		m_ShopFrame->Add_UIComponent<Sprite>(&FrameDesc);
	}

	{
		m_LeftTime = INSTANTIATE_UI(L"Shop_LeftTime");
		m_LeftTime->Set_Position(Vector3(640.f, 360.f, 0.f));
		m_LeftTime->Set_Active(false);

		Sprite::Desc LefTimeSprite;
		LefTimeSprite.TextureName = L"Shop_LeftTime";
		m_LeftTime->Add_UIComponent<Sprite>(&LefTimeSprite);

		Text::Desc	LeftTimeText;
		LeftTimeText.szScript = L"Left Time";
		LeftTimeText.iHeight = 30;
		LeftTimeText.iWeight = FW_HEAVY;
		LeftTimeText.ulOption = DT_VCENTER | DT_CENTER | DT_NOCLIP;
		LeftTimeText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
		LeftTimeText.vOffSet = Vector2(0.f, -320.f);
		m_LeftTime->Add_UIComponent<Text>(&LeftTimeText);
	}

}

void ShopManager::Update()
{
}

void ShopManager::LateUpdate()
{
}

void ShopManager::ReadyRender()
{
}

void ShopManager::Release()
{
}

void ShopManager::Open_Shop()
{
	EngineFunction->MouseLock_OnOff(OFF);
	m_ShopFrame->Set_Active(true);
	m_LeftTime->Set_Active(true);
	m_bShopOn = true;
}

void ShopManager::Exit_Shop()
{
	EngineFunction->MouseLock_OnOff(ON);
	m_ShopFrame->Set_Active(false);
	m_LeftTime->Set_Active(false);
	m_bShopOn = false;
}

void ShopManager::Buy_OneMag()
{
}

void ShopManager::Buy_AllMag()
{
}

void ShopManager::Buy_Weapon()
{
}

bool ShopManager::Get_ShopOn()
{
	return m_bShopOn;
}

void ShopManager::Insert_HaveWeapon(Weapon_Status * _Weapon)
{
	size_t temp = m_vecHaveWeapon_Name.size();
	wstring szName = _Weapon->m_tWeaponInfo.m_szName;
	int		curMag = _Weapon->m_tWeaponInfo.m_iCurMagazine;
	int		MaxMag = _Weapon->m_tWeaponInfo.m_iMaxMagazine;

	UI* Name = INSTANTIATE_UI(szName);
	Name->Set_Position(Vector3(640.f, 360.f, 1.f));

	Sprite::Desc NameSprite;
	NameSprite.TextureName = L"Shop_WeaponName";
	Name->Add_UIComponent<Sprite>(&NameSprite);

	Text::Desc NameText;
	wstring script;
	script = szName + L" (" + to_wstring(curMag) + L"/" + to_wstring(MaxMag) + L")";
	NameText.szScript = script;
	NameText.iHeight = 25;
	NameText.iWeight = FW_HEAVY;
	NameText.ulOption = DT_VCENTER | DT_CENTER | DT_NOCLIP;
	NameText.tColor = D3DCOLOR_RGBA(255, 255, 255, 255);
	NameText.vOffSet = Vector2(0.f, 0.f);
	Name->Add_UIComponent<Text>(&NameText);



}

void ShopManager::Set_LeftTime(float _fLeftTime)
{
	int Min = (int)_fLeftTime / 60;
	int Sec = (int)_fLeftTime % 60;

	if (Sec < 10)
	{
		((Text*)m_LeftTime->Get_Text())->Set_Script(
			L"Left Shopping Time\n" +
			to_wstring(Min) + L":0" + to_wstring(Sec));
	}
	else {
		((Text*)m_LeftTime->Get_Text())->Set_Script(
			L"Left Shopping Time\n" +
			to_wstring(Min) + L":" + to_wstring(Sec));
	}
	
}

void ShopManager::Set_ShopOnOff(bool _OnOff)
{
	m_bShopOn = _OnOff;
}
