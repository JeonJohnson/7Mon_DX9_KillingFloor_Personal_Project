#pragma once

#ifndef _STAGE_SCENE_H_
#define _STAGE_SCENE_H_

#include "Scene.h"
class StageScene :	public Scene
{
public:
	StageScene();
	virtual ~StageScene();

public:
	virtual void Initialize() override;
};

#endif //_STAGE_SCENE_H_