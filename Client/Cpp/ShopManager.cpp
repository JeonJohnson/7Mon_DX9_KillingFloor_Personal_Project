#include "stdafx.h"
#include "..\Header\ShopManager.h"
#include "UI.h"
#include "Weapon_Status.h"
#include "Player_Attack.h"
#include "Player_Status.h"

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
	/*{
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
	}*/

	//{
	//	m_pAllAmmo = INSTANTIATE_UI(L"Shop_BuyAllAmmo");
	//	m_LeftTime->Set_Position(Vector3(640.f, 360.f, 0.f));
	//	m_LeftTime->Set_Active(false);

	//	Sprite::Desc Sprite;
	//	LefTimeSprite.TextureName = L"Shop_LeftTime";
	//	m_LeftTime->Add_UIComponent<Sprite>(&LefTimeSprite);

	//	Text::Desc	LeftTimeText;
	//	LeftTimeText.szScript = L"Left Time";
	//	LeftTimeText.iHeight = 30;
	//	LeftTimeText.iWeight = FW_HEAVY;
	//	LeftTimeText.ulOption = DT_VCENTER | DT_CENTER | DT_NOCLIP;
	//	LeftTimeText.tColor = D3DCOLOR_RGBA(255, 0, 0, 255);
	//	LeftTimeText.vOffSet = Vector2(0.f, -320.f);
	//	m_LeftTime->Add_UIComponent<Text>(&LeftTimeText);
	//}

}

void ShopManager::Update()
{
	if (m_bShopOn)
	{
		Update_ItemInfo();
		if (m_pBuyButton->MouseOn())
		{
			((Sprite*)(m_pBuyButton->Get_Sprite()))->Set_Texture(L"AllAmmo_MouseOn");
		}
		else { ((Sprite*)(m_pBuyButton->Get_Sprite()))->Set_Texture(L"AllAmmo"); }
		
		Maintenance();

	}

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
	for (auto& weapon : m_vecHaveWeapon_Name)
	{
		weapon->Set_Active(true);
	}
	m_pBuyButton->Set_Active(true);
	m_bShopOn = true;
}

void ShopManager::Exit_Shop()
{
	EngineFunction->MouseLock_OnOff(ON);
	m_ShopFrame->Set_Active(false);
	m_LeftTime->Set_Active(false);
	for (auto& weapon : m_vecHaveWeapon_Name)
	{
		weapon->Set_Active(false);
	}
	m_pBuyButton->Set_Active(false);
	m_bShopOn = false;
}


void ShopManager::Maintenance()
{
	if (m_pBuyButton->Clikced())
	{
		GameObject*	pPlayer = EngineFunction->Get_GameObjectbyTag(OBJECT_TAG_PLAYER);
		Player_Attack* playerAtt = pPlayer->Get_Component<Player_Attack>();
		Player_Status* playerState = pPlayer->Get_Component<Player_Status>();

		playerAtt->All_Ammo();
		playerState->Buy_Vest();

	}
}

bool ShopManager::Get_ShopOn()
{
	return m_bShopOn;
}



void ShopManager::Insert_HaveWeapon(Weapon_Status * _Weapon)
{
	m_vecHaveItems.emplace_back(_Weapon);
}

void ShopManager::Set_VestValue(int _iCurVest)
{
	m_iVest = _iCurVest;
}

//void ShopManager::Insert_HaveWeapon(Weapon_Status * _Weapon)
//{
//	size_t temp = m_vecHaveWeapon_Name.size();
//	wstring szName = _Weapon->m_tWeaponInfo.m_szName;
//	int		curMag = _Weapon->m_tWeaponInfo.m_iCurMagazine;
//	int		MaxMag = _Weapon->m_tWeaponInfo.m_iMaxMagazine;
//
//	UI* Name = INSTANTIATE_UI(szName);
//	Name->Set_Position(Vector3(640.f, 360.f, 1.f));
//
//	Sprite::Desc NameSprite;
//	NameSprite.TextureName = L"Shop_WeaponName";
//	Name->Add_UIComponent<Sprite>(&NameSprite);
//
//	Text::Desc NameText;
//	wstring script;
//	script = szName + L" (" + to_wstring(curMag) + L"/" + to_wstring(MaxMag) + L")";
//	NameText.szScript = script;
//	NameText.iHeight = 25;
//	NameText.iWeight = FW_HEAVY;
//	NameText.ulOption = DT_VCENTER | DT_CENTER | DT_NOCLIP;
//	NameText.tColor = D3DCOLOR_RGBA(255, 255, 255, 255);
//	NameText.vOffSet = Vector2(0.f, 0.f);
//	Name->Add_UIComponent<Text>(&NameText);
//
//}

void ShopManager::Create_ItemUI()
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
	for (int i = 0; i <= (int)m_vecHaveItems.size(); ++i)
	{
		//size_t temp = m_vecHaveWeapon_Name.size();
		wstring szName = L"ShopItem" + to_wstring(i);
		//int		curMag = _Weapon->m_tWeaponInfo.m_iCurMagazine;
		//int		MaxMag = _Weapon->m_tWeaponInfo.m_iMaxMagazine;

		UI* Name = INSTANTIATE_UI(szName);
		Vector3 vPos = Vector3(335.f, 185.f, 1.f);
		vPos.y += (50 * i);
		Name->Set_Position(vPos);
		Name->Set_Scale(Vector3(0.5f, 0.5f, 0.f));
		Name->Set_Active(false);

		Sprite::Desc NameSprite;
		NameSprite.TextureName = L"Shop_WeaponName";
		Name->Add_UIComponent<Sprite>(&NameSprite);

		Text::Desc NameText;
		wstring script = L"";
		//script = szName + L" (" + to_wstring(curMag) + L"/" + to_wstring(MaxMag) + L")";
		NameText.szScript = script;
		NameText.iHeight = 20;
		NameText.iWeight = FW_HEAVY;
		NameText.ulOption = DT_VCENTER | DT_CENTER | DT_NOCLIP;
		NameText.tColor = D3DCOLOR_RGBA(255, 255, 255, 255);
		NameText.vOffSet = Vector2(0.f, 0.f);
		Name->Add_UIComponent<Text>(&NameText);

		m_vecHaveWeapon_Name.emplace_back(Name);
	}

	{
		m_pBuyButton = INSTANTIATE_UI(L"Start");
		m_pBuyButton->Set_Position(Vector3(975.f, 635.f, 0.f));
		m_pBuyButton->Set_Scale(Vector3(1.f, 1.f, 0.f));
		m_pBuyButton->Set_Button(true);
		m_pBuyButton->Set_Active(false);

		Sprite::Desc Buy_sprite;
		Buy_sprite.TextureName = L"AllAmmo";
		//AllAmmo_MouseOn
		m_pBuyButton->Add_UIComponent<Sprite>(&Buy_sprite);


		Text::Desc Buy_text;
		Buy_text.szScript = L"Maintenance";
		Buy_text.iHeight = 25;
		Buy_text.iWeight = FW_HEAVY;
		Buy_text.tColor = D3DCOLOR_RGBA(0, 0, 0, 255);
		m_pBuyButton->Add_UIComponent<Text>(&Buy_text);
	}

}

void ShopManager::Update_ItemInfo()
{
	for (int i = 0; i <= m_vecHaveWeapon_Name.size(); ++i)
	{
		if (i == (int)m_vecHaveWeapon_Name.size()-1)
		{ //Vest
			wstring script;
			script = L"Vest (" + to_wstring(m_iVest) + L"/100)";
			((Text*)(m_vecHaveWeapon_Name[i]->Get_Text()))->Set_Script(script);

			return;
		}

		wstring script;
		wstring szName = m_vecHaveItems[i]->m_tWeaponInfo.m_szName;
		int curMag = m_vecHaveItems[i]->m_tWeaponInfo.m_iCurMagazine;
		int MaxMag = m_vecHaveItems[i]->m_tWeaponInfo.m_iMaxMagazine;
		script = szName + L" (" + to_wstring(curMag) + L"/" + to_wstring(MaxMag) + L")";
		((Text*)(m_vecHaveWeapon_Name[i]->Get_Text()))->Set_Script(script);
		
	}
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

void ShopManager::Buy_AllAmmo()
{
}
