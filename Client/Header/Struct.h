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

	WEAPON_PRIORITY		m_ePriority; //��/����/���� ����
	WEAPON_TYPE			m_eType;	//������,����,����,����,����

	int			m_iDmg = 0;			//����(���� ���� �ƴԤ�;)
	int			m_iBuck = 0;		//���ǿ��� �� ����

	bool		m_bAuto = false;		//(�ܹ�, ���� Mouse press down)

	int			m_iMaxBullet = 0;
	int			m_iCurBullet = 0;

	int			m_iMaxMagazine = 0;
	int			m_iCurMagazine = 0;



	float		m_fMaxRapid = 0.f;	//����� : �߻� �㰡�� �ð�.
	float		m_fCurRapid = 0.f;	//����� : ���� ������ �ð�

	float		m_fAccuracy = 0.f;	//��Ȯ�� : ź���� �� ��.

	float		m_fRecoilForce = 0.f;	//�ݵ� : ī�޶� ����ũ �� ��

	int			m_iWeight = 0;
	int			m_iPrice = 0;
	int			m_iMagazinePrice = 0;

}WEAPON_INFO;

typedef struct tPlayerStatus
{
	int			m_iCurHp = 30;
	int			m_iMaxHp = 100;

	int			m_iCurArmor = 20;
	int			m_iMaxArmor = 100;

	int			m_iCurWeight = 1;
	int			m_iMaxWeight = 15;

	int			m_iGold = 250;


}PLAYER_INFO;


typedef struct tZedStatus
{
	ZED_TYPE    m_eName;

	int			m_iMaxHp = 100;
	int			m_iCurHp = 100;

	float		m_fRunSpd = 40.f;
	float		m_fWalkSpd = 20.f;


	int			m_iDmg = 10;
	int			m_iStrongDmg = 20;
	int			m_iMg42Dmg = 0;
	int			m_iMissileDmg = 0;

}ZED_INFO;

//typedef struct tBossStatus
//{
//	int			m_iCurHp;
//	int			m_iMaxHp;
//
//	float		m_fWalkSpd;
//	float		m_fRunSpd;
//
//	int			m_iDmg_Melee;
//	int			m_iDmg_StrongMelee;
//	int			m_iDmg_Mg42;
//	int			m_iDmg_Missile;
//
//}BOSS_INFO;

#endif //_STRUCT_H_