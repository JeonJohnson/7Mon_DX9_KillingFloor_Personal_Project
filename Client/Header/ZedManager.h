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
	void Setting_Ending(const Vector3& _vPos);

	void Nogada_Datas();
	
	void	Generate_Clot(const Vector3& _vPos, 
		const Quaternion& _qRot = Quaternion(), ZED_INFO _tStatus = ZED_INFO());
	void	Generate_GoreFast(const Vector3& _vPos,
		const Quaternion& _qRot= Quaternion(), ZED_INFO _tStatus = ZED_INFO());
	void	Generate_Scrake(const Vector3& _vPos,
		const Quaternion& _qRot = Quaternion(), ZED_INFO _tStatus = ZED_INFO());
	void	Generate_Patriarch(const Vector3& _vPos,
		const Quaternion& _qRot = Quaternion(), ZED_INFO _tStatus = ZED_INFO());

	void	KillThemAll();

public: /* Get */
	int		Get_ZedCount();

	Vector3		Get_ZedGenLocate(eZedGenLocate _eZedGenLocate);
	Vector3		Get_ZedGenLocate(int _iZedGenLocate);

	int		 Get_CurZedCount();
public: /* Set */
	void	Set_ZedCount(int _Count);
	void	Add_ZedCount(int _Count);

	void	Set_CurZedCount(int _curZed);
	void	Add_CurZedCount(int _curZed);
private:
	int		m_iZedCount = 0;
	int		m_iCurZed = 0;

	ZED_INFO	arrZedInfo[ZED_TYPE_END];

	Vector3		arrZedGenLocate[ZED_GEN_END];
	
	//typedef struct tZedStatus
	//{
	//	ZED_TYPE    m_szName;
	//	int			m_iCurHp = 100;
	//	int			m_iMaxHp = 100;
	//	float		m_fWalkSpd = 20.f;
	//	float		m_fRunSpd = 40.f;
	//	int			m_iDmg = 10;
	//	int			m_iDmg2 = 20;
	//}ZED_INFO;

};

#endif //_ZED_MANAGER_H_