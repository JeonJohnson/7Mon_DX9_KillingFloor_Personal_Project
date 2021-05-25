#pragma once

#ifndef _BULLET_MANAGER_H_
#define _BULLET_MANAGER_H_

#include "Include.h"

#include "Component.h"

class BulletManager : public Component
{
public:
	struct Desc
	{


	};

private:
	static BulletManager* m_pInstance;

public:
public:
	static BulletManager*		Get_Instance();
	static void					Destroy_Instance();

public:
	BulletManager(Desc* _desc);
	virtual ~BulletManager();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void	Create_Bullet(GameObject* _pPlayer, const WEAPON_INFO& _tInfo, int _iCount = 1);
	void	Create_Muzzle(GameObject* _pPlayer, Mesh* _pMesh, const WEAPON_INFO& _tInfo);
	//void	Create_Tracer(GameObject* _pPlayer, Mesh* _pMesh, const WEAPON_INFO& _tInfo);

	void	Create_PipeBomb(GameObject* _pPlayer, const WEAPON_INFO& _tInfo);
	void	Create_Explosion(const Vector3 _vPos, int _iDmg, float _fRadius);

	void	Create_Blood(const Vector3 _vPos);
	void	Create_BombBlood(const Vector3 _vPos);
public:
	
public:

private:
	


};
#endif //_BULLET_MANAGER_H_
