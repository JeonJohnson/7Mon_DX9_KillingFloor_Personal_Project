#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include "Engine_Include.h"

#include "CResource.h"

class DLL_STATE  Mesh : public CResource
{
//���߿� �Ѵ� ����
	//����ƽ�Ž���, �ִϸ��̼� �Ž� ��ĥ Ŭ����.

public:
	Mesh();
	virtual ~Mesh();

public:
	virtual void Initialize() override;
	virtual void Update();
	virtual void Release() override;

public:
	
public:

public:

public:

private:

};

#endif //_MESH_H_