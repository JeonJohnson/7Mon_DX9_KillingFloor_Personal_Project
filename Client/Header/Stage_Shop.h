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

public:

public:

private:
	float	m_fLefTime = 0.f;

};

#endif //_STAGE_SHOP_H_