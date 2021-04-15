#pragma once

#ifndef _ANIMATION_MESH_H_
#define _ANIMATION_MESH_H_

#include "Engine_Include.h"

#include "CResource.h"

class AnimMesh :public CResource
{
public:
	AnimMesh();
	virtual ~AnimMesh();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

public:

public:

public:

private:
	D3DXFRAME*		m_pRootFrame; 
	//Frame => DirectX���� ���ϴ� Bone
	//�ִϸ��̼ǿ��� ��� �� ������ ����, �ڽ� ����� ������ ��������
	//�� ���踦 �� ���鼭 ��� ������ ��ȸ �Ҳ���
	//�������� �𸣴� �� ������ ������ ���� ģ��.
	//typedef struct _D3DXFRAME 
	//{
	//	LPSTR                   Name; //���� ���� �̸�
	//	D3DXMATRIX              TransformationMatrix; //���� Ʈ������

	//	LPD3DXMESHCONTAINER     pMeshContainer; //�Ž��� ����ü? �Ž���� ���� ��.

	//	struct _D3DXFRAME       *pFrameSibling; //���� ��. ���� �θ� ������ ����.
	//	struct _D3DXFRAME       *pFrameFirstChild; //���� ���� �θ� �� �ڽ� ��.
	//} D3DXFRAME, *LPD3DXFRAME;

								


};


#endif //_ANIMATION_MESH_H_