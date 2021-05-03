#include "..\Header\Line.h"


Line::Line()
{
}

Line::Line(Desc * _desc)
{
	m_tColor = _desc->tColor;

	m_fWidth = _desc->fWidth;

	m_vArrPoint[POINT_START] = _desc->vStart;
	m_vArrPoint[POINT_DEST] = _desc->vDest;
}

Line::~Line()
{
}

void Line::Initialize()
{
}

void Line::Release()
{
}

float Line::Get_Width() const
{
	return m_fWidth;
}

const D3DXCOLOR & Line::Get_Color() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tColor;
}

const Vector3 & Line::Get_StartPos() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_vArrPoint[POINT_START];
}

const Vector3 & Line::Get_DestPos() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_vArrPoint[POINT_DEST];
}

void Line::Set_StartPos(const Vector3 & _vStartPos)
{
	m_vArrPoint[POINT_START] = _vStartPos;
}

void Line::Set_DestPos(const Vector3 & _DestPos)
{
	m_vArrPoint[POINT_DEST] = _DestPos;
}
