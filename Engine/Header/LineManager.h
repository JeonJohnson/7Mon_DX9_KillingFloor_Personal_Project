#pragma once

#ifndef _LINE_MANAGER_H_
#define _LINE_MANAGER_H_

#include "Engine_Include.h"

#include "Line.h"

class LineManager
{
public:
	Declare_Singleton(LineManager)

private:
	LineManager();
	~LineManager();

public:
	void Initialize();

	void Render();

	void Release();

public: /* funciton */
	void Delete_Lines();

	Line*		Create_Line(const Vector3& _vStart, 
		const Vector3& _vDest,
		D3DXCOLOR _tColor = D3DCOLOR_RGBA(0, 255, 0, 255),
		float _fWidth = 3.5f);

public: /* Get */
	 

public: /* Set */
		
	void Insert_Line(Line* _pLine);

private:
	LPDIRECT3DDEVICE9	m_pDX9_Device = nullptr;
	LPD3DXLINE			m_pDX9_LineCom = nullptr;
	list<Line*>			m_listLines;

};

#endif //_LINE_MANAGER_H_