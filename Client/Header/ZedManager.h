#pragma once

#ifndef _ZED_MANAGER_H_
#define _ZED_MANAGER_H_

#include "Component.h"


class ZedManager : public Component
{
public:
	struct Desc
	{


	};

public:
	ZedManager(Desc* _desc);
	virtual ~ZedManager();

private:
	static ZedManager* m_pInstance;

public:
	static ZedManager*		Get_Instance();
	static void				Destroy_Instance();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void	Generate_Clot(const Vector3& _vPos, 
		const Quaternion& _qRot = Quaternion(), ZED_INFO _tStatus = ZED_INFO());
	void	Generate_GoreFast(const Vector3& _vPos,
		const Quaternion& _qRot= Quaternion(), ZED_INFO _tStatus = ZED_INFO());
	void	Generate_Scrake(const Vector3& _vPos,
		const Quaternion& _qRot = Quaternion(), ZED_INFO _tStatus = ZED_INFO());
	void	Generate_Patriarch(const Vector3& _vPos,
		const Quaternion& _qRot = Quaternion(), ZED_INFO _tStatus = ZED_INFO());

public:

public:
	int		m_iZedCount = 0;
};

#endif //_ZED_MANAGER_H_