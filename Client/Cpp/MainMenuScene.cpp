#include "stdafx.h"
#include "..\Header\MainMenuScene.h"
#include "UI.h"
#include "MenuSelector.h"
#include "ZedChanger.h"


MainMenuScene::MainMenuScene()
{
}


MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Initialize()
{
	EngineFunction->MouseLock_OnOff(OFF);

	EngineFunction->StopAll_Sound();
	EngineFunction->PlayBGM(L"BGM_Menu.wav");

	{//BackGround Sprites
		EngineFunction->Load_Texture(L"Texture/Logo.png", L"GameTitle");
		
		for (int i = 0; i < 8; ++i)
		{
			EngineFunction->Load_Texture(L"Texture/Zeds/MainMenu_Zed_0" + to_wstring(i) + L".png",
				L"MainMenu_Zeds_0" + to_wstring(i));
		}

		EngineFunction->Load_Texture(L"Texture/Fade.png", L"Fade");		

		EngineFunction->Load_Texture(L"Texture/MainMenu/Idle.png", L"Idle");
		EngineFunction->Load_Texture(L"Texture/MainMenu/HighLight.png", L"HighLight");
		EngineFunction->Load_Texture(L"Texture/MainMenu/Pressed.png", L"Pressed");

		EngineFunction->Load_Texture(L"Texture/ScreenEffect/LightFilterTex.png", L"Film_Grain");

		EngineFunction->Load_Texture(L"Texture/Loading.png", L"Loading");



	}

	{//UISetting
		
		{
			UI* BackGround = INSTANTIATE_UI(L"BackGround");
			BackGround->Set_Position(Vector3(640.f, 360.f, 0.f));
			BackGround->Set_Scale(Vector3(1.f, 1.f, 0.f));

			Sprite::Desc BackGroundDesc;
			BackGroundDesc.TextureName = L"Fade";
			//BackGroundDesc.tColor = D3DCOLOR_RGBA(255, 255, 255, 255);
			BackGround->Add_UIComponent<Sprite>(&BackGroundDesc);
		}

		{
			UI* ZedSprites = INSTANTIATE_UI(L"ZedSprites");
			ZedSprites->Set_Position(Vector3(830.f, 620.f, 0.f));
			ZedSprites->Set_Scale(Vector3(1.f, 1.f, 0.f));

			int irand = rand() %8;
			Sprite::Desc desc;
			desc.TextureName = L"MainMenu_Zeds_0" + to_wstring(irand);
			ZedSprites->Add_UIComponent<Sprite>(&desc);

			GameObject*	ZedSprite_Obj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Zed_Sprite");
			
			ZedChanger::Desc ZedSpriteDesc;
			ZedSpriteDesc.ZedSprite = ZedSprites;
			ZedSprite_Obj->Add_Component<ZedChanger>(&ZedSpriteDesc);

		}
		
		{
			UI* TitleLogo = INSTANTIATE_UI(L"TitleLogo");
			TitleLogo->Set_Position(Vector3(300.f, 100.f, 0.f));
			TitleLogo->Set_Scale(Vector3(0.5f, 0.5f, 0.f));

			Sprite::Desc desc;
			desc.TextureName = L"GameTitle";
			TitleLogo->Add_UIComponent<Sprite>(&desc);		
		}

		
		{
			UI* StartButton = INSTANTIATE_UI(L"Start");
			StartButton->Set_Position(Vector3(180.f, 500.f, 0.f));
			StartButton->Set_Scale(Vector3(1.f, 1.2f, 0.f));
			StartButton->Set_Button(true);

			Sprite::Desc Start_sprite;
			Start_sprite.TextureName = L"Idle";
			StartButton->Add_UIComponent<Sprite>(&Start_sprite);


			Text::Desc Start_text;
			Start_text.szScript = L"Start Game";
			Start_text.iHeight = 25;
			Start_text.iWeight = FW_HEAVY;
			Start_text.tColor = D3DCOLOR_RGBA(255, 255, 255, 255);
			StartButton->Add_UIComponent<Text>(&Start_text);
	
			UI* ExitButton = INSTANTIATE_UI(L"Exit");
			ExitButton->Set_Position(Vector3(180.f, 550.f, 0.f));
			ExitButton->Set_Scale(Vector3(1.f, 1.2f, 0.f));
			ExitButton->Set_Button(true);

			Sprite::Desc Exit_Sprite;
			Exit_Sprite.TextureName = L"Idle";
			ExitButton->Add_UIComponent<Sprite>(&Exit_Sprite);


			Text::Desc Exit_Text;
			Exit_Text.szScript = L"Exit Game";
			Exit_Text.iHeight = 25;
			Exit_Text.iWeight = FW_HEAVY;
			Exit_Text.tColor = D3DCOLOR_RGBA(255, 255, 255, 255);
			ExitButton->Add_UIComponent<Text>(&Exit_Text);

			UI* Loading = INSTANTIATE_UI(L"Loading");
			Loading->Set_Position(Vector3(640.f, 360.f, 0.f));
			Loading->Set_Scale(Vector3(1.f, 1.f, 0.f));
			Loading->Set_Active(false);

			Sprite::Desc LoadingDesc;
			LoadingDesc.TextureName = L"Loading";
			//BackGroundDesc.tColor = D3DCOLOR_RGBA(255, 255, 255, 255);
			Loading->Add_UIComponent<Sprite>(&LoadingDesc);


			UI* Fade = INSTANTIATE_UI(L"Fade");
			Fade->Set_Position(Vector3(640.f, 360.f, 0.f));
			Fade->Set_Active(false);

			Sprite::Desc FadeSprite;
			FadeSprite.TextureName = L"Fade";
			Fade->Add_UIComponent<Sprite>(&FadeSprite);


			GameObject* Selector_Obj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"MenuButtonSelector");
			
			MenuSelector::Desc	SelectorDesc;
			SelectorDesc.StartButton = StartButton;
			SelectorDesc.ExitButton = ExitButton;
			SelectorDesc.Loading = Loading;
			SelectorDesc.Fade = Fade;
			Selector_Obj->Add_Component<MenuSelector>(&SelectorDesc);
		}

		
		{
			UI* FilmGrain = INSTANTIATE_UI(L"FilmGrain");
			FilmGrain->Set_Position(Vector3(640.f, 360.f, 0.f));
			FilmGrain->Set_Scale(Vector3(1.f, 1.f, 0.f));


			Sprite::Desc FilmGrain_Sprite;
			FilmGrain_Sprite.TextureName = L"Film_Grain";
			FilmGrain->Add_UIComponent<Sprite>(&FilmGrain_Sprite);


		}




	}
}

