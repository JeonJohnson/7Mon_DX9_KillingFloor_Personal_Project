#include "stdafx.h"
#include "..\Header\BloodEffect.h"
#include "VIBuffer_Renderer.h"


BloodEffect::BloodEffect(Desc * _desc)
{
	m_fBloodScale = _desc->fBloodInitScale;
}

BloodEffect::~BloodEffect()
{
}

void BloodEffect::Initialize()
{
	m_pBloodObj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"Explosion");
	m_pBloodObj->Set_Scale(Vector3(m_fBloodScale, m_fBloodScale, 1.f));
	Vector3 Pos = m_GameObject->Get_Position();
	float iRandX = (rand() % 5) - 2.5f;
	float iRandY= (rand() % 5) - 2.5f;
	float iRandZ = (rand() % 5) - 2.5f;
	Pos.x += iRandX;
	Pos.y += iRandY;
	Pos.z += iRandZ;
	m_pBloodObj->Set_Position(Pos);
	
	VIBuffer_Renderer::Desc SmokeSprite;
	SmokeSprite.wBufferName = RECT_TEXTURE;
	SmokeSprite.szShaderName = EFFECT_SHADER;

	int iRand = rand() % 9;
	wstring texture = L"Blood" + to_wstring(iRand);
	SmokeSprite.wTextureName = texture;
	SmokeSprite.bEffect_Min = true;
	SmokeSprite.bFade = true;
	SmokeSprite.fFadeSpd = 0.5f;
	SmokeSprite.iLayer = RENDER_LAYER_Alpha;
	m_pBloodObj->Add_Component<VIBuffer_Renderer>(&SmokeSprite);

	m_pBloodBuffer = m_pBloodObj->Get_Component<VIBuffer_Renderer>();

	if (m_pPlayer == nullptr)
	{
		m_pPlayer = EngineFunction->Get_GameObjectbyTag(OBJECT_TAG_PLAYER);
	}
}

void BloodEffect::Update()
{

	m_fBloodTime += fTime;
	if (m_fBloodTime >= 0.75f)
	{
		m_pBloodObj->Set_Alive(false);
		m_GameObject->Set_Alive(false);
	}

	m_fBloodScale -= fTime * m_fBloodSpd;
	if (m_fBloodScale <= 0.f) 
	{
		m_fBloodScale = 0.f;
	}
	m_pBloodObj->Get_Transform()->Set_PosY(20.f);
	m_pBloodObj->Set_Rotation(m_pPlayer->Get_Rotation());
	m_pBloodObj->Set_Scale(Vector3(m_fBloodScale, m_fBloodScale, 0.f));

}

void BloodEffect::LateUpdate()
{
}

void BloodEffect::ReadyRender()
{
}

void BloodEffect::Release()
{
}
