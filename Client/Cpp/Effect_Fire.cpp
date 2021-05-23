#include "stdafx.h"
#include "..\Header\Effect_Fire.h"

#include "VIBuffer_Renderer.h"


Effect_Fire::Effect_Fire(Desc * _desc)
{
	m_pRenderer = _desc->pVibufferRenderer;

}

Effect_Fire::~Effect_Fire()
{
}

void Effect_Fire::Initialize()
{
}

void Effect_Fire::Update()
{
	m_fIndex += fTime * 15.f;

	if (m_fIndex >= 15.f)
	{
		m_fIndex = 0.f;
	}

	
	m_pRenderer->Set_TextureIndex(m_fIndex);


	//m_Transform->Set_Rotation()

}

void Effect_Fire::LateUpdate()
{
}

void Effect_Fire::ReadyRender()
{
}

void Effect_Fire::Release()
{
}
