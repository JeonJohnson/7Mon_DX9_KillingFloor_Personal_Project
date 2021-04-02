#include "stdafx.h"
#include "..\Header\TestScene.h"
//#include "../../Reference/Header/Camera.h"

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
	
}

void TestScene::Initialize()
{
	GameObject*	Test_Cam = INSTANTIATE(OBJECT_TAG_MAINCAM, L"Test_Cam");
	Camera::Desc Cam_desc;
	Test_Cam->Add_Component<Camera>(&Cam_desc);




	GameObject* Test_Triangle = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Test_Rect");
	
	VIBuffer_Renderer::Desc Test_Desc;
	Test_Desc.wBufferName = L"Rect_Color";
	Test_Desc.iLayer = RENDER_LAYER::RENDER_LAYER_Priority;
	Test_Triangle->Add_Component<VIBuffer_Renderer>(&Test_Desc);
}
