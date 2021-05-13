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

		//WEAPON_PRIORITY		ePriority; //��/����/���� ����
		//WEAPON_TYPE			eType;	//������,����,����,����,����

		//int					iDmg = 0;			//����(���� ���� �ƴԤ�;)
		//int					iBuck = 0;		//���ǿ��� �� ����

		//bool				bAuto = false;		//(�ܹ�, ���� Mouse press down)

		//int					iMaxBullet = 0;
		//int					iCurBullet = 0;

		//int					iMaxMagazine = 0;
		//int					iCurMagazine = 0;

		//float				fMaxRapid = 0.f;	//����� : �߻� �㰡�� �ð�.
		//float				fCurRapid = 0.f;	//����� : ���� ������ �ð�


		//float				fAccuracy = 0.f;	//��Ȯ�� : ź���� �� ��.

		//float				fRecoilForce = 0.f;	//�ݵ� : ī�޶� ����ũ �� ��

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