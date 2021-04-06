#pragma once

#ifndef _UI_H_
#define _UI_H_

#include "Engine_Include.h"

#include "Cycle.h"


class DLL_STATE UI : public Cycle
{
	//text와 sprite가 상속받을꺼
	//GameObject랑 비슷한 역할.

public:
	explicit UI();
	virtual ~UI();


public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

#pragma region Template
public:
	


#pragma endregion
public:

public:

public:


private:


};

#endif //_UI_H_