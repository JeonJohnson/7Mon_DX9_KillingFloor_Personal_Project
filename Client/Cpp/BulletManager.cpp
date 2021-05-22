#include "stdafx.h"
#include "..\Header\BulletManager.h"
#include "SphereCollider.h"
#include "Bullet_Move.h"
#include "..\..\Engine\Header\VIBuffer_Renderer.h"
#include "MuzzleEffect.h"
#include "Mesh_Renderer.h"
#include "..\..\Engine\Header\Mesh.h"

BulletManager* BulletManager::m_pInstance = nullptr;

BulletManager * BulletManager::Get_Instance()
{
	if (m_pInstance == nullptr)
	{
		GameObject* mgrObj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"BulletManager");
		mgrObj->Add_Component<BulletManager>();
		m_pInstance = mgrObj->Get_Component<BulletManager>();
	}
		
	return m_pInstance;
}

void BulletManager::Destroy_Instance()
{
	if (m_pInstance)
	{
		GameObject::Destory(m_pInstance->Get_GameObject());
	}
}

BulletManager::BulletManager(Desc * _desc)
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::Initialize()
{
}

void BulletManager::Release()
{
}


void BulletManager::Update()
{
}

void BulletManager::LateUpdate()
{
}

void BulletManager::ReadyRender()
{
}

void BulletManager::Create_Bullet(GameObject* _pPlayer, const WEAPON_INFO& _tInfo, int _iCount)
{
	for (int i = 0; i < _iCount; ++i)
	{
	
		//Rot.z += (float)((rand() % 21) - 10) / 10.f;

		GameObject* Bullet = INSTANTIATE(OBJECT_TAG_BULLET, L"Bullet");
		//Vector3 vDir = _pPlayer->Get_Position();
		Bullet->Set_Position(_pPlayer->Get_Position());
		Bullet->Set_Rotation(_pPlayer->Get_Rotation());
		//Bullet->Set_Rotation(Rot);
		//Vector3  vDir = m_Transform->Get_Position() /*+ m_Transform->Get_Forward()*50.f*/;
		//Bullet->Set_Position(vDir);
		//Bullet->Set_Rotation(m_Transform->Get_Rotation());

		SphereCollider::Desc ColDesc;
		ColDesc.fRadius = 0.5f;
		ColDesc.szColName = L"bullet";
		Bullet->Add_Component<SphereCollider>(&ColDesc);


		float Acc = _tInfo.m_fAccuracy;
		Acc *= 100.f;
		Acc -= 100.f;
		Acc = abs(Acc);

		Vector3 vSpread = {0.f,0.f,0.f};
		vSpread.x += (float)((rand() % (int)(Acc * 2 + 1)) - Acc) / 1000.f;
		vSpread.y += (float)((rand() % (int)(Acc * 2 + 1)) - Acc) / 1000.f;
		//Rot.z += (float)((rand() % (int)(Acc * 2 + 1)) - Acc) / 10.f;

		Bullet_Move::Desc bulletmove;
		bulletmove.Spd = 2000.f;
		bulletmove.Dmg = _tInfo.m_iDmg;
		bulletmove.vAcc = vSpread;
		Bullet->Add_Component<Bullet_Move>(&bulletmove);
	}
}

void BulletManager::Create_Muzzle(GameObject* _pPlayer, Mesh* _pMesh, const WEAPON_INFO& _tInfo)
{
	GameObject* Muzzle = INSTANTIATE(OBJECT_TAG_DEFAULT, L"");
	
	int iRand = rand() % 4;
	VIBuffer_Renderer::Desc sprite;
	sprite.wBufferName = RECT_TEXTURE;
	sprite.szShaderName = EFFECT_SHADER;
	sprite.wTextureName = L"Muzzle_0" + to_wstring(iRand);
	sprite.bEffect = true;
	sprite.iLayer = RENDER_LAYER_Alpha;
	Muzzle->Add_Component<VIBuffer_Renderer>(&sprite);


	MuzzleEffect::Desc effect;
	effect.pPlayer = _pPlayer;
	effect.pMesh = _pMesh;
	if (_tInfo.m_eType == WEAPON_TYPE::Weapon_Shotgun)
	{
		effect.fmaxsize = (_tInfo.m_iDmg*_tInfo.m_iBuck) / 11.f;
	}
	else 
	{
		effect.fmaxsize = (_tInfo.m_iDmg*_tInfo.m_iBuck) / 7.f;
	}
	
	
	Muzzle->Add_Component<MuzzleEffect>(&effect);
}
