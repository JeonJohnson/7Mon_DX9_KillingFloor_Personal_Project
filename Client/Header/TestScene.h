#pragma once

#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include "Scene.h"


class TestScene :	public Scene
{
public:
	TestScene();
	virtual ~TestScene();
	
public:
	virtual void Initialize() override;
};


//{
	//Uis Test
 //UI* Test_Text = INSTANTIATE_UI(L"Test_Text");
 //Test_Text->Set_Position(Vector3(640.f, 360.f, 0.f));
 //Test_Text->Set_Scale(Vector3(1.f, 1.f, 1.f));

 //Text::Desc textInfo;
 //textInfo.iHeight = 56;
 //textInfo.iWeight = FW_HEAVY;
 //textInfo.szScript = L"Test Test Test Test";


 //Sprite::Desc spriteInfo;
 //spriteInfo.TextureName = L"PangDongE_UI";


 //Test_Text->Add_UIComponent<Sprite>(&spriteInfo);
 //Test_Text->Add_UIComponent<Text>(&textInfo);
//}

#endif //_TEST_SCENE_H_