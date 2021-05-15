#include "stdafx.h"
#include "..\Header\SkyBox.h"




SkyBox::SkyBox(Desc * _desc)
{
}

SkyBox::~SkyBox()
{
}

void SkyBox::Initialize()
{
}

void SkyBox::Update()
{
	if (pMainCam == nullptr)
	{
		pMainCam = EngineFunction->Get_GameObjectbyName(L"Player")->Get_Component<Camera>();
	}

	Vector3 Pos = pMainCam->Get_Transform()->Get_Position();
	m_Transform->Set_Position(Vector3(Pos.x, 0.f, Pos.z));
}

void SkyBox::LateUpdate()
{
}

void SkyBox::ReadyRender()
{
}

void SkyBox::Release()
{
}
