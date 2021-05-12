#pragma once

#ifndef _BULLET_MANAGER_H_
#define _BULLET_MANAGER_H_

#include "Include.h"

class BulletManager
{

	Declare_Singleton(BulletManager)

private:
	BulletManager();
	~BulletManager();

public:
	void Initialize();
	void Release();

public:

public:

public:

private:
};
#endif //_BULLET_MANAGER_H_
