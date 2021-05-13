#pragma once

#ifndef _PLAYER_STATUS_H_
#define _PLAYER_STATUS_H_

#include "Component.h"

class Player_Status : public Component
{
public:
	struct Desc
	{


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

public: /* Set */

public: /* Get */

private:
	int			m_iCurHp;
	int			m_iMaxHp;

	int			m_iCurArmor;
	int			m_iMaxArmor;

	int			m_iCurWeight;
	int			m_iMaxWeight;

	int			m_iGold;

};
#endif //_PLAYER_STATUS_H_
