#pragma once

#ifndef _BILLBOARD_BULLET_H_
#define _BILLBOARD_BULLET_H_

#include "Component.h"

class Billboard_Bullet : public Component
{
public:
	struct Desc
	{
	
	};

public:
	Billboard_Bullet(Desc* _desc);
	virtual ~Billboard_Bullet();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

private:

};

#endif //_BILLBOARD_BULLET_H_