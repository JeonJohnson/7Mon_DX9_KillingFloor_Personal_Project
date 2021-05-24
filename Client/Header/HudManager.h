#pragma once

#ifndef _HUD_MANAGER_H_
#define _HUD_MANAGER_H_

#include "Component.h"

class UI;
class Text;

class HudManager : public Component
{
public:
	struct Desc
	{
	
	};

public:
	HudManager(Desc* _desc);
	virtual ~HudManager();

private:
	static HudManager*	m_pInstance;
public:
	static HudManager*		Get_Instance();
	static void				Destroy_Instance();

public: 
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: /* Func */
	void		Hit_EffectOn();
	void		Hit_EffectOff();
	
	void		Setting_FadeIn();
	void		Setting_FadeOut();
	bool		Fade_In();
	bool		Fade_Out();

	void		All_HudOnOff(bool _OnOff);


public: /* Get */
	UI*			Get_Hud(const wstring& _szName);
	Text*		Get_HudText(const wstring& _szName);

public: /* Set */
	void		Insert_Hud(const wstring& _szName, UI* _pUI);

	void		Set_TextHp(int _iHp);
	void		Set_TextHeal(int _iHeal);
	void		Set_TextArmor(int _iArmor);
	void		Set_TextWeight(int _iWeight);
	void		Set_TextBullet(int _iBullet);
	void		Set_TextMagazine(int _iMagazine);
	
	void		Set_TextGranade(int _iGranade);

	void		Set_TextMoney(int _iMoney);
	void		Set_TextWeaponName(const wstring& _szWeaponName);
	
	void		Set_TextClock(float _fClock);
	void		Set_TextZedCount(int _iZedCount);
	void		Set_TextZedCount(const wstring& _szScript);

	void		Set_Fade(UI* _pFade);
	
	//void		Insert_ShopHud(const wstring& _szName, UI* _pUI);
	

private:

	unordered_map<wstring, UI*>	m_umStageHuds;
	bool		m_bHitEffect = false;
	 
	UI*			m_pFade = nullptr;
	Sprite*		m_pFadeSprite = nullptr;
	bool		m_bFadeIn = false;
	bool		m_bFadeOut = false;
	//unordered_map<wstring, UI*> m_umShopHud;
	//vector<UI*>					m_vecHaveWeapon;
	//vector<UI*>					m_vecBuyWeapon;


	//Hp
	//Armor
	//Weight
	//Bullet
	//Magazine
	//Grande
	//Money
	//WeaponName
	//Clock
	//EnemyCount

	//UI*		m_pHp			= nullptr;
	//UI*		m_pArmor		= nullptr;
	//UI*		m_pWeight		= nullptr;
	//UI*		m_pBullet		= nullptr;
	//UI*		m_pMagazine		= nullptr;
	//UI*		m_pGranade		= nullptr;
	//UI*		m_pMoney		= nullptr;
	//UI*		m_pWeaponName	= nullptr;
	//UI*		m_pClock		= nullptr;
	//UI*		m_pEnemyCount	= nullptr;


};

#endif //_HUD_MANAGER_H_