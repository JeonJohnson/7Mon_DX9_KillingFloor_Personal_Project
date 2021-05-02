#pragma once

#ifndef _NAVI_CELL_H_
#define _NAVI_CELL_H_

#include "Engine_Include.h"

class NaviPoint;

class DLL_STATE NaviCell
{
	friend class NaviMesh;
public:
	NaviCell();
	~NaviCell();
};

#endif //_NAVI_CELL_H_