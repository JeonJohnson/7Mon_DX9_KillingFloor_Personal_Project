#include "stdafx.h"
#include "..\Header\BombEffect.h"
#include "VIBuffer_Renderer.h"

BombEffect::BombEffect(Desc * _desc)
{
	//m_pExplosionObj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Explosion");
	//m_pExplosionObj->Set_Position(m_GameObject->Get_Position());

	//VIBuffer_Renderer::Desc ExplosionSprite;
	//ExplosionSprite.wBufferName = RECT_TEXTURE;
	//ExplosionSprite.szShaderName = EFFECT_SHADER;
	//ExplosionSprite.wTextureName = L"Explosion_Effect";
	//ExplosionSprite.bEffect = true;
	//ExplosionSprite.iLayer = RENDER_LAYER_Alpha;
	//m_pExplosionObj->Add_Component<VIBuffer_Renderer>(&ExplosionSprite);

	//m_pExplosionBuffer = m_pExplosionObj->Get_Component<VIBuffer_Renderer>();

	m_fSmokeScale = _desc->fSmokeInitScale;

}

BombEffect::~BombEffect()
{

}

void BombEffect::Initialize()
{
	m_pBigSmokeObj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Explosion");
	m_pBigSmokeObj->Set_Scale(Vector3(m_fSmokeScale, m_fSmokeScale, 1.f));
	Vector3 Pos = m_GameObject->Get_Position();
	Pos.y = m_fSmokeScale / 2.f;
	m_pBigSmokeObj->Set_Position(Pos);

	VIBuffer_Renderer::Desc SmokeSprite;
	SmokeSprite.wBufferName = RECT_TEXTURE;
	SmokeSprite.szShaderName = EFFECT_SHADER;
	SmokeSprite.wTextureName = L"Smoke_Effect";
	//SmokeSprite.bEffect = true;
	SmokeSprite.bFade = true;
	SmokeSprite.fFadeSpd = 0.5f;
	SmokeSprite.iLayer = RENDER_LAYER_Alpha;
	m_pBigSmokeObj->Add_Component<VIBuffer_Renderer>(&SmokeSprite);

	m_pSmokeBuffer = m_pBigSmokeObj->Get_Component<VIBuffer_Renderer>();

	if (m_pPlayer == nullptr)
	{
		m_pPlayer = EngineFunction->Get_GameObjectbyTag(OBJECT_TAG_PLAYER);
	}
}

void BombEffect::Update()
{
	//m_pExplosionObj->Set_Rotation(m_pPlayer->Get_Rotation());
	
	m_fSmokeTime += fTime;
	if (m_fSmokeTime >= 2.f)
	{
		m_pBigSmokeObj->Set_Alive(false);
		m_GameObject->Set_Alive(false);
	}

	
	m_fSmokeScale += fTime * m_fSmokeSpd;
	m_pBigSmokeObj->Get_Transform()->Set_PosY(m_fSmokeScale / 2.f);
	m_pBigSmokeObj->Set_Rotation(m_pPlayer->Get_Rotation());
	m_pBigSmokeObj->Add_Scale(Vector3(fTime * m_fSmokeSpd, fTime * m_fSmokeSpd, 0.f));

}

void BombEffect::LateUpdate()
{
}

void BombEffect::ReadyRender()
{
}

void BombEffect::Release()
{
}
