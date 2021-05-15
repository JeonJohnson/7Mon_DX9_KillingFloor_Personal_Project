#pragma once

#ifndef _ZED_MANAGER_H_
#define _ZED_MANAGER_H_

#include "Component.h"


class ZedManager : public Component
{
public:
	struct Desc
	{


	};

public:
	ZedManager(Desc* _desc);
	virtual ~ZedManager();

private:
	static ZedManager* m_pInstance;

public:
	static ZedManager*		Get_Instance();
	static void				Destroy_Instance();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

};

#endif //_ZED_MANAGER_H_