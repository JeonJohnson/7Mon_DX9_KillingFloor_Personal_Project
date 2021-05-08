#include "..\Header\NaviPoint.h"


#include "Transform.h"


NaviPoint::NaviPoint(Desc * _desc)
{
	m_vPosition = _desc->Pos;
	m_iIndex = _desc->Index;
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

int NaviPoint::Get_Index() const
{
	return m_iIndex;
}

void NaviPoint::Set_Position(const Vector3 & _vPos)
{
	//m_vPosition = _vPos;
}

void NaviPoint::Update()
{
	m_vPosition = m_Transform->Get_Position();
}

void NaviPoint::LateUpdate()
{
}

void NaviPoint::ReadyRender()
{
}
