#include "..\Header\Sprite.h"
#include "DeviceManager.h"

Sprite::Sprite(Desc * _desc)
{
	m_pDX9_Sprite = DeviceManager::Get_Instance()->Get_DX9_Sprite();
	assert(L"Sprite Com Load Failed to Sprite" && m_pDX9_Sprite);


}

Sprite::~Sprite()
{
}

void Sprite::Initialize()
{
	//렉트지정
}

void Sprite::Update()
{
}

void Sprite::LateUpdate()
{
}

void Sprite::ReadyRender()
{
}

void Sprite::Render()
{
	if (m_pDX9_Sprite)
	{
		//m_pDX9_Sprite->Draw
		//(

		//);
	}
}

void Sprite::Release()
{
}

UI_KIND Sprite::Get_UIkind() const
{
	return m_eUiKind;
}


