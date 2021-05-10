#pragma once

#ifndef _SAVE_INFO_NAVIMESH_H_
#define _SAVE_INFO_NAVIMESH_H_

#include "Engine_Include.h"

class DLL_STATE SaveInfo_NaviMesh
{
public:
	SaveInfo_NaviMesh();
	~SaveInfo_NaviMesh();

public:

public:

public:

public:
	//개수, 포지션 로드 후 순서대로 naviPoint 생성
		//=>저장 할 때 뒤에서부터 저장 해야함.
	int							iPointCount = 0;
	vector<Vector3> 			vecPointPosition;

	//개수 만큼 셀 생성. 
	//한 셀당 vecCellPoint에 저장 되어있는 인덱스번호에
	//순서대로 알맞게 Cell에 Point삽입.
	//세개 다 넣으면 라인세팅.
	int							iCellCount = 0;
	vector<tuple<int, int, int>>	vecCellPoint;

	//그리고 매쉬 하나 만들어서 다 넣고 
	//LinkCell조지기


};

#endif //_SAVE_INFO_NAVIMESH_H_