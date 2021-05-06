#pragma once

#ifndef _MAINMENU_SCENE_H_
#define _MAINMENU_SCENE_H_

#include "Scene.h"
class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	virtual ~MainMenuScene();

public:
	virtual void Initialize() override;
};

#endif //_MAINMENU_SCENE_H_