#pragma once

#ifndef _LINE_H_
#define _LINE_H_

#include "Engine_Include.h"

class Line
{
public:
	enum ePOINT {POINT_START, POINT_DEST, POINT_END };

public:
	struct Desc
	{
		D3DXCOLOR	tColor = D3DCOLOR_RGBA(0, 255, 0, 255);
		float		fWidth = 3.5f;

		Vector3		vStart = { 0.f,0.f,0.f };
		Vector3		vDest = { 0.f, 0.f, 0.f };
	};
public:
	Line();
	Line(Desc* _desc);
	~Line();

public:
	void Initialize();

	void Release();

public:

public:
	void Setup_Normal();
	Line_Dir Compare(const Vector3& _vEndPos);

public: /* Get */
	float				Get_Width() const;
	const D3DXCOLOR&	Get_Color() const;
	const Vector3&		Get_StartPos() const;
	const Vector3&		Get_DestPos() const;

public: /* Set */
	void				Set_StartPos(const Vector3& _vStartPos);
	void				Set_DestPos(const Vector3& _DestPos);
	

private:
	//LPD3DXLINE			m_pDX9_Line_Com = nullptr;
	D3DXCOLOR			m_tColor;
	float				m_fWidth;
	Vector3				m_vArrPoint[POINT_END];


	Vector2				m_vDirection;
	Vector2				m_vNormal;

};

#endif //_LINE_H_
