#pragma once

#ifndef _NAVI_POINT_H_
#define _NAVI_POINT_H_

#include "Engine_Include.h"

#include "Component.h"

class DLL_STATE NaviPoint : public Component
{
	friend class NaviCell;
public:
	struct Desc
	{
		Vector3 Pos;
		int		Index;
	};

public:
	NaviPoint(Desc* _desc);
	NaviPoint(const Vector3& _vPos);
	~NaviPoint();
	
public:
	void Initialize();
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	void Render();
	void Release();

public: /* func */


public: /* Get */
	const Vector3&	Get_Position() const ;
	int				Get_Index() const;

public: /* Set */
	void			Set_Position(const Vector3& _vPos);

private:
	Vector3		m_vPosition;
	int			m_iIndex;
};

#endif //_NAVI_POINT_H_