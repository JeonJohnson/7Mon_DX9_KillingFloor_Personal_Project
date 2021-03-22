#pragma once

#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Engine_Include.h"
#include "Scene.h"

class SceneManager
{
	
	Declare_Singleton(SceneManager)

private:
	SceneManager();
	~SceneManager();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:

public:

private:
	Scene*	m_pCurrentScene = nullptr;
	
};

#endif