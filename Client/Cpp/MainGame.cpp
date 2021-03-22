#include "stdafx.h"
#include "..\Header\MainGame.h"
#include "Base.h"


Implement_Singleton(MainGame)

MainGame::MainGame()
{

}


MainGame::~MainGame()
{

}

void MainGame::Initialize()
{
	Base::Desc base_desc;
	base_desc.wincx = WINCX;
	base_desc.wincy = WINCY;
	base_desc.window = false;
	base_desc.hWnd = g_hWnd;
	Base::Get_Instance()->Initialize(&base_desc);
}

void MainGame::Release()
{
}

void MainGame::Process()
{
	Base::Get_Instance()->Process();
}
