#pragma once

#ifndef _STAGE_MANAGER_H_
#define _STAGE_MANAGER_H_

#include "Component.h"

class StageManager : public Component
{
public:
	struct Desc
	{
		
	};
public:
	StageManager(Desc* _desc);
	virtual ~StageManager();

private:
	static StageManager* m_pInstance;
public:
	static StageManager* Get_Instance();
	static void			 Destory_Instance();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

public:

private:
};

#endif //_STAGE_MANAGER_H_