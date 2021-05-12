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
	
	WEAPON_PRIORITY		m_ePriority; //��/����/���� ����
	WEAPON_TYPE			m_eType;	//������,����,����,����,����

	int			m_iDmg = 0;			//����(���� ���� �ƴԤ�;)
	
	int			m_iCurBullet = 0;
	int			m_iMaxBullet = 0;

	int			m_iCurMagazine = 0;
	int			m_iMaxMagazine = 0;

	int			m_iBuck = 0;		//���ǿ��� �� ����

	bool		m_bAuto = false;		//(�ܹ�, ���� Mouse press down)

	float		m_fCurRapid = 0.f;	//����� : ���� ������ �ð�
	float		m_fMaxRapid = 0.f;	//����� : �߻� �㰡�� �ð�.
	
	float		m_fAccuracy = 0.f;	//��Ȯ�� : ź���� �� ��.
	
	float		m_fRecoilForce = 0.f;	//�ݵ� : ī�޶� ����ũ �� ��

	int			m_iWeight = 0;
	int			m_iPrice = 0;
};

#endif //_WEAPON_H_