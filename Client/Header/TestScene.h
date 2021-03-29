#pragma once

#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include "Scene.h"


class TestScene :
	public Scene
{
public:
	TestScene();
	virtual ~TestScene();

public:
	virtual void Initialize() override;
};

#endif //_TEST_SCENE_H_