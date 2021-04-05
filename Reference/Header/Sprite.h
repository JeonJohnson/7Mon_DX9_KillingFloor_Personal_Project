#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Engine_Include.h"

#include "CResource.h"

class DLL_STATE Sprite :public CResource
{
public:
	struct Desc 
	{
	};
public:
	Sprite(Desc* _desc);
	virtual ~Sprite();

public:
	virtual void Initialize() override;
	virtual void Release() override;

public: /* function */
	void	Render_Sprite();

public:

public:

private:

};

#endif //_SPRITE_H_