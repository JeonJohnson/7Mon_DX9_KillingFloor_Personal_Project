#pragma once

#ifndef _INTRO_SCENE_H_
#define _INTRO_SCENE_H_

#include "Scene.h"

class IntroScene :
	public Scene
{
public:
	IntroScene();
	virtual ~IntroScene();

public:
	virtual void Initialize() override;

};

#endif //_INTRO_SCENE_H_