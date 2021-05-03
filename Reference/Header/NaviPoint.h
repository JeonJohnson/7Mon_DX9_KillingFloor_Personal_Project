#pragma once

#ifndef _NAVI_POINT_H_
#define _NAVI_POINT_H_

#include "Engine_Include.h"

class DLL_STATE NaviPoint
{
	friend class NaviCell;

public:
	NaviPoint();
	NaviPoint(const Vector3& _vPos);
	~NaviPoint();
	
public:
	void Initialize();
	void Render();
	void Release();

public: /* func */


public: /* Get */
	const Vector3&	Get_Position() const ;

public: /* Set */
	void			Set_Position(const Vector3& _vPos);

private:
	Vector3		m_vPosition;

};

#endif //_NAVI_POINT_H_