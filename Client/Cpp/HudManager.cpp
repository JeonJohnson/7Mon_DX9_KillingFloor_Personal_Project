#include "stdafx.h"
#include "..\Header\HudManager.h"
#include "Sprite.h"

HudManager* HudManager::m_pInstance = nullptr;

HudManager::HudManager(Desc * _desc)
{
}

HudManager::~HudManager()
{
} 

HudManager * HudManager::Get_Instance()
{
	if (m_pInstance == nullptr)
	{
		GameObject*	mgrObj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"HudManager");
		mgrObj->Add_Component<HudManager>();
		m_pInstance = mgrObj->Get_NewComponent<HudManager>();

		//m_pInstance->SetDontDestory(true);
	}

	return m_pInstance;
}

void HudManager::Destroy_Instance()
{
	if (m_pInstance)
	{
		GameObject::Destory(m_pInstance->Get_GameObject());
	}
}

void HudManager::Initialize()
{
}

void HudManager::Update()
{
	//m_umStageHuds[L"Hp"]->Set_Button(true);
	//if (m_umStageHuds[L"Hp"]->MouseOn())
	//{
	//	DEBUG_LOG(L"MouseOn");
	//}
	Hit_EffectOff();
}

void HudManager::LateUpdate()
{

}

void HudManager::ReadyRender()
{
}

void HudManager::Release()
{
}

void HudManager::Hit_EffectOn()
{

	UI* uiTemp = Get_Hud(L"HitEffect");
	uiTemp->Set_Active(true);
	Sprite* hitEffect = (Sprite*)uiTemp->Get_Sprite();

	//hitEffect->Set_Color(D3DCOLOR_RGBA(125, 255, 255, 255));
	hitEffect->Set_Alpha(1.f);
	m_bHitEffect = true;
}

void HudManager::Hit_EffectOff()
{
	if (m_bHitEffect)
	{
		UI* uiTemp = Get_Hud(L"HitEffect");
		//uiTemp->Set_Active(true);
		Sprite* hitEffect = (Sprite*)uiTemp->Get_Sprite();

		hitEffect->Add_Alpha(fTime * -0.5f);

		if (hitEffect->Get_Alpha() <= 0.f)
		{
			uiTemp->Set_Active(false);
		}
	}
}

void HudManager::All_HudOnOff(bool _OnOff)
{
	for (auto& hud : m_umStageHuds)
	{
		hud.second->Set_Active(_OnOff);
	}

	Get_Hud(L"HitEffect")->Set_Active(false);
}

UI * HudManager::Get_Hud(const wstring & _szName)
{
	auto iter_find = m_umStageHuds.find(_szName);

	if (iter_find == m_umStageHuds.end())
	{
		return nullptr;
	}

	return (*iter_find).second;

}

Text * HudManager::Get_HudText(const wstring & _szName)
{
	auto iter_find = m_umStageHuds.find(_szName);

	if (iter_find == m_umStageHuds.end())
	{
		return nullptr;
	}

	return (Text*)((*iter_find).second->Get_Text());
}

void HudManager::Insert_Hud(const wstring & _szName, UI * _pUI)
{
	m_umStageHuds.emplace(_szName, _pUI);
}

void HudManager::Set_TextHp(int _iHp)
{
	Get_HudText(L"Hp")->Set_Script(to_wstring(_iHp));
}

void HudManager::Set_TextHeal(int _iHeal)
{
	Get_HudText(L"Heal")->Set_Script(to_wstring(_iHeal));
}

void HudManager::Set_TextArmor(int _iArmor)
{
	Get_HudText(L"Armor")->Set_Script(to_wstring(_iArmor));
}

void HudManager::Set_TextWeight(int _iWeight)
{
	wstring WeightText = to_wstring(_iWeight) + L"/15";

	Get_HudText(L"Weight")->Set_Script(WeightText);
}

void HudManager::Set_TextBullet(int _iBullet)
{
	Get_HudText(L"Bullet")->Set_Script(to_wstring(_iBullet));
}

void HudManager::Set_TextMagazine(int _iMagazine)
{
	Get_HudText(L"Magazine")->Set_Script(to_wstring(_iMagazine));
}

void HudManager::Set_TextGranade(int _iGranade)
{
	Get_HudText(L"Granade")->Set_Script(to_wstring(_iGranade));
}

void HudManager::Set_TextMoney(int _iMoney)
{
	Get_HudText(L"Money")->Set_Script(to_wstring(_iMoney));
}

void HudManager::Set_TextWeaponName(const wstring & _szWeaponName)
{
	Get_HudText(L"WeaponName")->Set_Script(_szWeaponName);
}

void HudManager::Set_TextClock(float _fClock)
{
	int Min = (int)_fClock / 60;
	int Sec = (int)_fClock % 60;

	if (Sec >= 10)
	{
		Get_HudText(L"Clock")->Set_Script(to_wstring(Min) + L":" + to_wstring(Sec));
	}
	else {
		Get_HudText(L"Clock")->Set_Script(to_wstring(Min) + L":0" + to_wstring(Sec));
	}
}

void HudManager::Set_TextZedCount(int _iZedCount)
{
	Get_HudText(L"EnemyCount")->Set_Script(L"Count\n" + to_wstring(_iZedCount));
}
