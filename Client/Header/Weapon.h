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
	
	int			m_iDmg;			//����(���� ���� �ƴԤ�;)
	
	int			m_iBuck;		//���ǿ��� �� ����

	bool		m_bAuto;		//(�ܹ�, ���� Mouse press down)

	float		m_fCurRapid;	//����� : ���� ������ �ð�
	float		m_fMaxRapid;	//����� : �߻� �㰡�� �ð�.
	
	float		m_fAccuracy;	//��Ȯ�� : ź���� �� ��.
	
	float		m_fRecoilForce;	//�ݵ� : ī�޶� ����ũ �� ��

};

#endif //_WEAPON_H_