#pragma once

#ifndef _STAGE_SHOP_H_
#define _STAGE_SHOP_H_

#include "CState.h"
class Stage_Shop : public CState
{
public:
	Stage_Shop();
	virtual ~Stage_Shop();

public:
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:
	void	Create_Arrow();

	void	Skip_Shop();
	void	Open_Shop();
	void	Exit_Shop();
public:

public:

private:
	GameObject*		m_pPlayer = nullptr;
	GameObject*		m_pShopArrow = nullptr;


	float	m_fLeftTime = 120.f;

};

#endif //_STAGE_SHOP_H_