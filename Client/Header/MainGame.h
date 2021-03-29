#pragma once

#ifndef _MAIN_GAME_H_
#define _MAIN_GAME_H_

class MainGame
{
	Declare_Singleton(MainGame)

private:
	MainGame();
	~MainGame();

public:
	void Initialize();
	void Process();
	void Release();

public:
	void Engine_Load();
	void Scene_Setting();
public:

public:
	Base*	m_pEngine;

};

#endif