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

void Line::Setup_Normal()
{
	Vector2 point_Dest, point_Start;
	point_Dest.x = m_vArrPoint[POINT_DEST].x;
	point_Dest.y = m_vArrPoint[POINT_DEST].z;

	point_Start.x = m_vArrPoint[POINT_START].x;
	point_Start.y = m_vArrPoint[POINT_START].z;

	m_vDirection = point_Dest - point_Start;
	m_vNormal = Vector2(m_vDirection.y * -1.f, m_vDirection.x);
	D3DXVec2Normalize(&m_vNormal, &m_vNormal);


	//m_vDirection = m_vArrPoint[POINT_DEST] - m_vArrPoint[POINT_START];

	//D3DXVec3Cross(&m_vNormal, &m_vArrPoint[POINT_START], &m_vArrPoint[POINT_DEST]);

	//D3DXVec3Normalize(&m_vNormal, &m_vNormal);
}

Line_Dir Line::Compare(const Vector3 & _vEndPos)
{
	//이동 해야할 위치가 해당 선에서 오른쪽에 있는지 왼쪽에 있는지?

	Vector2 EndPos = { _vEndPos.x, _vEndPos.z };
	Vector2 ArrPoint = { m_vArrPoint[POINT_START].x, m_vArrPoint[POINT_START].z };

	Vector2 vDest = EndPos - ArrPoint;

	float fDot = D3DXVec2Dot(&m_vNormal, D3DXVec2Normalize(&vDest, &vDest));

	if (fDot >= 0.f)
	{
		return Line_Dir::LINE_LEFT;
	}
	else 
	{
		return Line_Dir::LINE_RIGHT;
	}
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
