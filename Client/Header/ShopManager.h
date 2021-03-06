#pragma once

#ifndef _SHOP_MANAGER_H_
#define _SHOP_MANAGER_H_

#include "Component.h"


class Weapon_Status;
class UI;

class ShopManager :	public Component
{
public:
	struct Desc
	{
		
	};

public:
	ShopManager(Desc* _desc);
	virtual ~ShopManager();

private:
	static ShopManager* m_pInstance;
public:
	static ShopManager*	Get_Instance();
	static void			Destory_Instance();


public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void		Open_Shop();
	void		Exit_Shop();
	//void		Buy_OneMag();
	//void		Buy_AllMag();
	//void		Buy_Weapon();

	
	void	Maintenance();
public:
	bool		Get_ShopOn();
	//bool		Get_ShopOff();


public:
	void		Insert_HaveWeapon(Weapon_Status* _Weapon);
	void		Set_VestValue(int _iCurVest);
	//void		Insert_ShopWeapon(GameObject* _Weapon);
	//void		Insert_Vest(int _iVest);
	//void		Insert_Granade(Weapon_Status* _Granade);
	
	void		Create_ItemUI();

	void		Update_ItemInfo();
	

	void		Set_LeftTime(float _fLeftTime);
	void		Set_ShopOnOff(bool _OnOff);

	void		Buy_AllAmmo();
private:
	
	
	vector<Weapon_Status*> m_vecHaveItems;
	int		m_iVest;

	vector<UI*> m_vecHaveWeapon_Name;

	//UI*		m_Vest;

	//vector<UI*> m_vecHaveWeapon_OneMag;
	//vector<UI*> m_vecHaveWeapon_OneMag_MouseOn;
	//vector<UI*> m_vecHaveWeapon_AllMag;
	//vector<UI*> m_vecHaveWeapon_AllMag_MouseOn;

	UI*		m_pBuyButton = nullptr;
	//vector<UI*> m_vecShopWeapon_Name;
	//vector<UI*> m_vecShopWeapon_Buy;
	//vector<UI*> m_vecShopWeapon_Buy_MouseOn;

	UI*			m_ShopFrame = nullptr;
	UI*			m_LeftTime = nullptr;

	bool		m_bShopOn = false;


};

#endif //_SHOP_MANAGER_H_