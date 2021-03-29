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
	void ReadyRender();
	void Render();
	void Release();

public:
	void CurrentSceneCheck();

public:
	void Insert_Scene(const wstring& _wName, Scene* _pScene);
	void Set_FirstScene(const wstring& _wName);
	void Load_Scene(const wstring& _wName);
	void SceneChangeCheck();


private:
	Scene*	m_pCurrentScene = nullptr;
	Scene*	m_pNextScene = nullptr;
	map<wstring, Scene*> m_mapSceneList;

private:
	bool	m_bNext = false;


};

#endif