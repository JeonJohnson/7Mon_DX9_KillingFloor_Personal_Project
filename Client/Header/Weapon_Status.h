#pragma once

#ifndef _WEAPON_STATUS_H_
#define _WEAPON_STATUS_H_

#include "Include.h"

#include "Component.h"

class Weapon_Status : public Component
{
public:
	struct Desc
	{
		WEAPON_INFO			tWeaponStatus;

		//wstring				szName = L"";

		//WEAPON_PRIORITY		ePriority; //주/보조/근접 무기
		//WEAPON_TYPE			eType;	//라이플,샷건,스나,권총,근접

		//int					iDmg = 0;			//뎀쥐(콩쥐 팥쥐 아님ㅎ;)
		//int					iBuck = 0;		//샷건에서 벜 개수

		//bool				bAuto = false;		//(단발, 연발 Mouse press down)

		//int					iMaxBullet = 0;
		//int					iCurBullet = 0;

		//int					iMaxMagazine = 0;
		//int					iCurMagazine = 0;

		//float				fMaxRapid = 0.f;	//연사력 : 발사 허가할 시간.
		//float				fCurRapid = 0.f;	//연사력 : 현재 굴러갈 시간


		//float				fAccuracy = 0.f;	//정확도 : 탄퍼짐 할 때.

		//float				fRecoilForce = 0.f;	//반동 : 카메라 쉐이크 줄 때

		//int					iWeight = 0;
		//int					iPrice = 0;
		//int					iMagazinePrice = 0;
	};
public:
	Weapon_Status(Desc* _desc);
	virtual ~Weapon_Status();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

public:
	WEAPON_INFO		m_tWeaponInfo;

};

#endif //_WEAPON_STATUS_H_