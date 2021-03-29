#include "stdafx.h"
#include "..\Header\TestScene.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	GameObject* Test_Triangle = INSTANTIATE(ObjectLayer_Default, L"Test_Triangle");
	VIBuffer_Renderer::Desc Test_Desc;
	Test_Triangle->Add_Component<VIBuffer_Renderer>(&Test_Desc);
}
