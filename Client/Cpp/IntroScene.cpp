#include "stdafx.h"
#include "..\Header\IntroScene.h"
#include "GameObject.h"
#include "Camera.h"
#include "UI.h"
#include "..\..\Engine\Header\Sprite.h"


IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

void IntroScene::Initialize()
{
	{ //Resource Load
		EngineFunction->Load_Texture(L"Texture/Intro.png", L"Intro_Logo");
		EngineFunction->Load_Texture(L"Texture/Fade.png", L"Fade");

	
	}

	{ //CamSetting
		GameObject*	Cam = INSTANTIATE(OBJECT_TAG_MAINCAM, L"IntroCam");
		Cam->Set_Position(0.f, 0.f, 0.f);

		Camera::Desc	Cam_desc;
		Cam->Add_Component<Camera>(&Cam_desc);
	}

	{//Uis Test
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
	}

	{//LogoSprite
		UI*		JusinLogo = INSTANTIATE_UI(L"Jusin_Logo");
		JusinLogo->Set_Position(Vector3(640.f, 360.f, 0.f));
		JusinLogo->Set_Scale(Vector3(1.f, 1.f, 1.f));

		Sprite::Desc LogoSprite;
		LogoSprite.tColor = D3DCOLOR_RGBA(255, 255, 255, 255);
		LogoSprite.TextureName = L"Intro_Logo";

		JusinLogo->Add_UIComponent<Sprite>(&LogoSprite);
	}

	{//Fade
		UI*		Fade = INSTANTIATE_UI(L"Fade");
		Fade->Set_Position(Vector3(640.f, 360.f, 0.f));
		Fade->Set_Scale(Vector3(1.f, 1.f, 1.f));

		Sprite::Desc FadeSprite;
		FadeSprite.tColor = D3DCOLOR_RGBA(255, 255, 255, 0);
		FadeSprite.TextureName = L"Fade";

		Fade->Add_UIComponent<Sprite>(&FadeSprite);
	}
}
