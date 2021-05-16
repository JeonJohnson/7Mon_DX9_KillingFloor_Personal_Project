#pragma once

#ifndef _SPHERE_COLLIDER_H_
#define _SPHERE_COLLIDER_H_

#include "Engine_Include.h"

#include "Collider.h"

class DLL_STATE	SphereCollider :public Collider
{
public:
	struct Desc
	{
		float				fRadius = 1.f;
		Vector3				vOffset = { 0.f,0.f,0.f };
		_collision_Layer	iCollisionLayer = -1;
		wstring				szColName = L"";
	};

public:
	SphereCollider(Desc* _desc);
	~SphereCollider();
	
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	bool	Sphere2Sphere(SphereCollider * _pStart, SphereCollider * _pDest);
	bool	Collision_Check(GameObject* _pGameObejct, const wstring& _szColName = L"");
	bool	Collision_Check(_object_Tag _iTag, const wstring& _szObjName, const wstring& _szColName = L"");
	//bool	Collision(SphereCollider* )

public: 
	


public: /* Get */
	Vector3			Get_Center();
	float			Get_Radius();
	bool			Get_Check();
	
public : /* Set */
	void			Set_Check(bool _bCheack);
private:
	float				m_fRadius = 0.f;
	Vector3				m_vOffset = { 0.f,0.f,0.f };
	Vector3				m_vCenter = { 0,0,0 };

	_collision_Layer	m_iCollisionLayer = -1;
	wstring				m_szColName;

	bool				m_bCheck = true;



	GameObject*			m_pDebuging = nullptr;

};

#endif //_SPHERE_COLLIDER_H_