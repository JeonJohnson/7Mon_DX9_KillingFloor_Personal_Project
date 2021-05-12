#pragma once

#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Include.h"

class Weapon
{

	friend class WeaponManager;

public:
	Weapon();
	virtual ~Weapon();



public:
	wstring		m_szName = L"";
	
	WEAPON_PRIORITY		m_ePriority; //주/보조/근접 무기
	WEAPON_TYPE			m_eType;	//라이플,샷건,스나,권총,근접

	int			m_iDmg = 0;			//뎀쥐(콩쥐 팥쥐 아님ㅎ;)
	
	int			m_iCurBullet = 0;
	int			m_iMaxBullet = 0;

	int			m_iCurMagazine = 0;
	int			m_iMaxMagazine = 0;

	int			m_iBuck = 0;		//샷건에서 벜 개수

	bool		m_bAuto = false;		//(단발, 연발 Mouse press down)

	float		m_fCurRapid = 0.f;	//연사력 : 현재 굴러갈 시간
	float		m_fMaxRapid = 0.f;	//연사력 : 발사 허가할 시간.
	
	float		m_fAccuracy = 0.f;	//정확도 : 탄퍼짐 할 때.
	
	float		m_fRecoilForce = 0.f;	//반동 : 카메라 쉐이크 줄 때

	int			m_iWeight = 0;
	int			m_iPrice = 0;
};

#endif //_WEAPON_H_