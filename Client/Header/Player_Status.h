#pragma once

#ifndef _PLAYER_STATUS_H_
#define _PLAYER_STATUS_H_

#include "Include.h"

#include "Component.h"

class Player_Status : public Component
{
public:
	struct Desc
	{
		PLAYER_INFO tPlayerStatus;

	};

public:
	Player_Status(Desc* _desc);
	virtual ~Player_Status();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:/* Func */
	void	Damaged(int _iDmg);
	void	Heal();
	void	Buy_Vest();

public: /* Set */
	void	Set_Heal(bool _OnOff);

public: /* Get */
	PLAYER_INFO		Get_PlayerStatus();

private:
	PLAYER_INFO		m_tPlayerStatus;
	
	bool			m_bHeal = false;
	int				m_iHealAmount = 50;
	float			m_fHealTime = 0.f;
	
	//bool			m_bHeal = false;

	//int			m_iCurHp;
	//int			m_iMaxHp;

	//int			m_iCurArmor;
	//int			m_iMaxArmor;

	//int			m_iCurWeight;
	//int			m_iMaxWeight;

	//int			m_iGold;

};
#endif //_PLAYER_STATUS_H_
