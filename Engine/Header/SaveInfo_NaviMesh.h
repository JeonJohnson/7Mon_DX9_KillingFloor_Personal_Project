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
	void Setting(int _iPointCount, int _iCellCount);


public:

public:

public:
	//�����Ҷ��� STL����!

	//����, ������ �ε� �� ������� naviPoint ����
		//=>���� �� �� �ڿ������� ���� �ؾ���.
	int							iPointCount = 0;
	Vector3*					arrPointPosition = nullptr;
	//vector<Vector3> 			vecPointPosition;

	//���� ��ŭ �� ����. 
	//�� ���� vecCellPoint�� ���� �Ǿ��ִ� �ε�����ȣ��
	//������� �˸°� Cell�� Point����.
	//���� �� ������ ���μ���.
	int							iCellCount = 0;

	Vector3*					arrCellPointIndex = nullptr;
	//vector<tuple<int, int, int>>	vecCellPoint;

	//�׸��� �Ž� �ϳ� ���� �� �ְ� 
	//LinkCell������


};

#endif //_SAVE_INFO_NAVIMESH_H_