#pragma once

#ifndef _ZED_STATUS_H_
#define _ZED_STATUS_H_

#include "Include.h"

#include "Component.h"

class Zed_Status :	public Component
{
public:
	struct Desc
	{
		ZED_INFO	tZedInfo; 
	};

public:
	Zed_Status(Desc* _desc);
	virtual ~Zed_Status();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: /* Func */

public: /* Get */
	ZED_INFO	Get_Status();

public: /* Set */
	void		Damaged(int _iDmg);

public:

private:
	ZED_INFO		m_tZedStatus;
	//int			m_iCurHp;
	//int			m_iMaxHp;

	//float		m_fWalkSpd;
	//float		m_fRunSpd;


	//int			m_iDmg;
	//int			m_iDmg2;

};

#endif //_ZED_STATUS_H_