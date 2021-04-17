#pragma once

#ifndef _ENGINE_STRUCT_H_
#define _ENGINE_STRUCT_H_


#pragma region VIBuffer Structs
/* vertex Buffer */
	/* Vertex Property */
		//=> a �׸� ������ �Ӽ�
typedef struct tagVertexColor
{
	//������ ������ ���� ��12��
	Vector3 vPos;
	unsigned int uiColor;

}VERTEX_COLOR;

typedef struct tagVertexUV
{
	//UV, �� �ؽ��ĸ� �԰� ���� ��12��
	Vector3 vPos;
	Vector2 vUV;

}VERTEX_TEXTURE;

typedef struct tagVertexUV_DDS
{
	Vector3 vPos;
	Vector3 vUV;

}VERTEX_DDS;

	
	/* FVF */
		//=> Flexible Vertex Format
		//=> a ���ؽ��� �Ӽ�
const unsigned int FVF_COLOR = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;
const unsigned int FVF_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;
const unsigned int FVF_DDS	= D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef struct tagVertexBufferInfo
{
	//�� ����
	unsigned int	m_iVertexCount = 0;

	//������ ���� �޸� ũ�� => �� �쿡 ���� �Ӽ� ���� �ٸ��ϱ�
	unsigned int	m_iVertexMemSize = 0;

	//������(�� 3���� ��������� �ּ� �ﰢ��)�� ����
	unsigned int	m_iPolyCount = 0;

	//�ٷ� �쿡 �ִ� ���ؽ��Ӽ� ���� �� ģ��.
	unsigned int	m_iFVF = 0;

}VBUFFER_INFO;

/* index Buffer */
//https://mooneegee.blogspot.com/2015/03/directx9-index-buffer.html
//�ε��� : �������� �׸��� �ﰢ�� ������ �׸��� �Ǵµ�,
//���� ���� �� ������ ���� �����̳� ������Ʈ�� �׸���, ������ ������ �ִ� ��������
//�� ���� �׷��� �ϴ� ��찡 ����.
	//=> Rect�� ������ �ʿ��� ������ 4������, �ﰢ�� ������ �׷��� �ϱ� ������
	//=> Vertex���� 6�� �̿� �ؼ� �׸��� ��. (�׸��� �ߺ��Ǵ� ������ ����)
				//=> �ߺ��ȴ� = ��ǥ���� ������ �׸��� ���� ���� ������ �����ؾ��ϴ� ������ �����ϰ� ��.
//���� ��ȿ�����̴ϱ� �����鿡 ���� �ѹ��� �ο��ؼ� �ߺ��Ǵ� ��쿡 �� ���� ������ �����ϰ� �����ϴ°� �ƴ϶�
//���� �ѹ��� �ҷ����ڴ� ����

//--------------------------------------
//Index 16�� 32����
//WORD = unsigned sort = 16��Ʈ
//DWORD = unsigned long = 32��Ʈ
//������� �׸��Ŀ� ���� �ѹ��� �׸� �� �ִ� �������� ������ �޶���.
//16 => 2^16�� ���� ǥ������
//32 => 2^32�� ���� ǥ������
//���� �׷���ī�忡���� 32��Ʈ ǥ�� �ȵȴٴµ� �������� ���ϼ� �׷���ī�� ��帲

//�� ����ü���� �迭�� ���ΰ� �������� ��������.
typedef struct tagIndex16
{
	WORD	_1, _2, _3;
	//�׸��� �ּ� ������ �ﰢ�������� 3����.
	//�̻��� �Ⱦ���. ��������
}INDEX_16;

typedef struct tagIndex32
{
	DWORD	_1, _2, _3;
	//�׸��� �ּ� ������ �ﰢ�������� 3����.
}INDEX_32;

typedef struct tagIndex32_Line
{
	DWORD	_1, _2;
}INDEX_32_LINE;

typedef struct tagIndexBufferInfo
{
	D3DFORMAT		m_tIndexFMT;
	unsigned int	m_iIndexMemSize = 0;

}IBUFFER_INFO;
#pragma endregion

#pragma region MeshRender Strcuts
typedef struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	/* Default Variables */
	//LPSTR                   Name;					//���̸�, �߾Ⱦ�.
	//D3DXMATRIX              TransformationMatrix; //
	//LPD3DXMESHCONTAINER     pMeshContainer;		//
	//struct _D3DXFRAME       *pFrameSibling;		//���� bone
	//struct _D3DXFRAME       *pFrameFirstChild;	//�ڽ� bone

	Matrix		CombinedTransformMatrix; //�θ� �� ��Ʈ���� * �� ��
}D3DXFrame_Derived;

/* Mesh Render Derived Struct */
typedef struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	/* Default Variables */
	//LPSTR                   Name;
	//D3DXMESHDATA            MeshData;
	//LPD3DXMATERIAL          pMaterials;
	//LPD3DXEFFECTINSTANCE    pEffects;
	//DWORD                   NumMaterials;
	//DWORD                  *pAdjacency;
	//LPD3DXSKININFO          pSkinInfo;
	//struct _D3DXMESHCONTAINER *pNextMeshContainer;

	/* Derived Variables */
	LPDIRECT3DTEXTURE9*	ppTexture;
	LPD3DXMESH			pOriginMesh;
	int					iBoneCount;

	Matrix*				pFrameOffsetMatrix; //�ڽ��� ���� ���.
	Matrix**			ppCombinedTrasnformMatrix; //�ڽ� ��Ŀ� �θ���� ���ؼ� ���� ���� ���.
						//=> �� �����̽��� ����.
	Matrix*				pRenderingMatrix; //���������� ��� ��ȯ�� ������ �������� �� ���.
						//=> pFrameOffsetMatrix * CombinedTransformMatrix
}MeshContainer_Derived;
 


#pragma endregion
#endif //_ENGINE_STRUCT_H_