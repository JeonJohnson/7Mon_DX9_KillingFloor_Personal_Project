#pragma once

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Engine_Include.h"

#include "CResource.h"
class Texture : public CResource
{
public:
	Texture();
	virtual ~Texture();
	
public:
	virtual void Initialize() override;
	virtual void Release() override;

public:

public:

public:

private:
};

#endif //_TEXTURE_H_