#pragma once

#ifndef _STRUCT_H_
#define _STRUCT_H_

//typedef struct tSaveInfo_TerrainLayout
//{
//	TCHAR		szMeshPath[255];
//	TCHAR		szMeshName[255];
//
//	TCHAR		szObjName[255];
//	int			iObjTag;
//	int			iRenderLayer;
//
//	Vector3		vPosition;
//	Vector3		vScale;
//	Vector3		vRotation;
//}TerrainInfo;

typedef struct tWeaponStatus
{
	wstring		m_szName = L"";

	WEAPON_PRIORITY		m_ePriority; //주/보조/근접 무기
	WEAPON_TYPE			m_eType;	//라이플,샷건,스나,권총,근접

	int			m_iDmg = 0;			//뎀쥐(콩쥐 팥쥐 아님ㅎ;)
	int			m_iBuck = 0;		//샷건에서 벜 개수

	bool		m_bAuto = false;		//(단발, 연발 Mouse press down)

	int			m_iMaxBullet = 0;
	int			m_iCurBullet = 0;

	int			m_iMaxMagazine = 0;
	int			m_iCurMagazine = 0;



	float		m_fMaxRapid = 0.f;	//연사력 : 발사 허가할 시간.
	float		m_fCurRapid = 0.f;	//연사력 : 현재 굴러갈 시간

	float		m_fAccuracy = 0.f;	//정확도 : 탄퍼짐 할 때.

	float		m_fRecoilForce = 0.f;	//반동 : 카메라 쉐이크 줄 때

	int			m_iWeight = 0;
	int			m_iPrice = 0;
	int			m_iMagazinePrice = 0;

}WEAPON_INFO;

typedef struct tPlayerStatus
{
	int			m_iCurHp = 73;
	int			m_iMaxHp = 100;

	int			m_iCurArmor = 20;
	int			m_iMaxArmor = 100;

	int			m_iCurWeight = 1;
	int			m_iMaxWeight = 15;

	int			m_iGold = 123250;


}PLAYER_INFO;


typedef struct tZedStatus
{
	int			m_iCurHp;
	int			m_iMaxHp;

	int			m_iCurArmor;
	int			m_iMaxArmor;


}ZED_INFO;

#endif //_STRUCT_H_