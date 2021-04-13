#pragma once

#ifndef _ANIMATION_MESH_H_
#define _ANIMATION_MESH_H_

#include "Engine_Include.h"

#include "CResource.h"

class AnimMesh :public CResource
{
public:
	AnimMesh();
	virtual ~AnimMesh();

public:
	virtual void Initialize() override;
	virtual void Release() override;

};


#endif //_ANIMATION_MESH_H_