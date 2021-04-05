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
	void FPS_Update();
public:

public:
	Engine_Mother*	m_pEngine;
	//Text*			m_pFPS;
};

#endif //_MAIN_GAME_H_