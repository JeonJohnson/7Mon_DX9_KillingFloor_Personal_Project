#pragma once

#ifndef _NAVI_CELL_H_
#define _NAVI_CELL_H_

#include "Engine_Include.h"

class NaviPoint;

class DLL_STATE NaviCell
{
	friend class NaviMesh; 
public:

public:
	NaviCell();
	~NaviCell();

public:
	void Initialize();
	//void Render();
	void Release();

public: 

public: /* Func */
	void Setup_Lines();

public: /* Get */
	NaviPoint*			Get_NaviPoint(int _iIndex);
	int					Get_PointArraySize();

public: /* Set */
	HRESULT	Insert_NaviPoint(NaviPoint* _pPoint, int _iIndex);

private:
	//LPDIRECT3DDEVICE9	m_pDX9_Device = nullptr;
	//LPD3DXLINE			m_pDX9_Line = nullptr;
	NaviPoint*			m_arrNaviPoints[3] = { nullptr };
};

#endif //_NAVI_CELL_H_