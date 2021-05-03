#include "..\Header\NaviPoint.h"



NaviPoint::NaviPoint()
{
}


NaviPoint::NaviPoint(const Vector3 & _vPos)
{
	m_vPosition = _vPos;
}

NaviPoint::~NaviPoint()
{
}

void NaviPoint::Initialize()
{
}

void NaviPoint::Render()
{
}

void NaviPoint::Release()
{
}

const Vector3 & NaviPoint::Get_Position() const
{
	return m_vPosition;
}

void NaviPoint::Set_Position(const Vector3 & _vPos)
{
	m_vPosition = _vPos;
}
