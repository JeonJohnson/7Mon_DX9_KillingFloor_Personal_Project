#pragma once

#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Include.h"

class Weapon
{
public:
	Weapon();
	virtual ~Weapon();



private:
	wstring		m_szName;
	
	int			m_iDmg;			//뎀쥐(콩쥐 팥쥐 아님ㅎ;)
	
	int			m_iBuck;		//샷건에서 벜 개수

	bool		m_bAuto;		//(단발, 연발 Mouse press down)

	float		m_fCurRapid;	//연사력 : 현재 굴러갈 시간
	float		m_fMaxRapid;	//연사력 : 발사 허가할 시간.
	
	float		m_fAccuracy;	//정확도 : 탄퍼짐 할 때.
	
	float		m_fRecoilForce;	//반동 : 카메라 쉐이크 줄 때

};

#endif //_WEAPON_H_