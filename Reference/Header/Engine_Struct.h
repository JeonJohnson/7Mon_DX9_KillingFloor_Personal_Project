#pragma once

#ifndef _ENGINE_STRUCT_H_
#define _ENGINE_STRUCT_H_


#pragma region VIBuffer Structs
/* vertex Buffer */
	/* Vertex Property */
		//=> a 그릴 도형의 속성
typedef struct tagVertexColor
{
	//색상을 가지고 있을 새12끼
	Vector3 vPos;
	unsigned int uiColor;

}VERTEX_COLOR;

typedef struct tagVertexUV
{
	//UV, 즉 텍스쳐를 입고 있을 새12끼
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
		//=> a 버텍스의 속성
const unsigned int FVF_COLOR = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;
const unsigned int FVF_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;
const unsigned int FVF_DDS	= D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef struct tagVertexBufferInfo
{
	//점 개수
	unsigned int	m_iVertexCount = 0;

	//정점의 개당 메모리 크기 => 저 우에 도형 속성 따라서 다르니까
	unsigned int	m_iVertexMemSize = 0;

	//폴리곤(점 3개로 만들어지는 최소 삼각형)의 개수
	unsigned int	m_iPolyCount = 0;

	//바로 우에 있는 버텍스속성 적어 줄 친구.
	unsigned int	m_iFVF = 0;

}VBUFFER_INFO;

/* index Buffer */
//https://mooneegee.blogspot.com/2015/03/directx9-index-buffer.html
//인덱스 : 정점으로 그릴때 삼각형 단위로 그리게 되는데,
//만약 조금 더 정점이 많은 도형이나 오브젝트를 그리때, 실제로 가지고 있는 정점보다
//더 많이 그려야 하는 경우가 생김.
	//=> Rect만 보더라도 필요한 정점은 4개지만, 삼각형 단위로 그려야 하기 때문에
	//=> Vertex들을 6번 이용 해서 그리게 됨. (그릴때 중복되는 정점이 생김)
				//=> 중복된다 = 좌표값은 같지만 그릴때 따로 정점 정보를 저장해야하는 정점이 존재하게 됨.
//존나 비효율적이니까 정점들에 고유 넘버를 부여해서 중복되는 경우에 또 따로 정점을 저장하고 연산하는게 아니라
//고유 넘버를 불러오자는 거지

//--------------------------------------
//Index 16과 32차이
//WORD = unsigned sort = 16비트
//DWORD = unsigned long = 32비트
//어떤것으로 그리냐에 따라 한번에 그릴 수 있는 폴리곤의 개수가 달라짐.
//16 => 2^16개 까지 표현가능
//32 => 2^32개 까지 표현가능
//구형 그래픽카드에서는 32비트 표현 안된다는데 그정도면 말하셈 그래픽카드 사드림

//이 구조체들을 배열로 놔두고 정점들을 대입해줌.
typedef struct tagIndex16
{
	WORD	_1, _2, _3;
	//그릴때 최소 단위가 삼각형임으로 3개씩.
	//이새끼 안쓸꺼. ㅋㅋㅅㄱ
}INDEX_16;

typedef struct tagIndex32
{
	DWORD	_1, _2, _3;
	//그릴때 최소 단위가 삼각형임으로 3개씩.
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
	//LPSTR                   Name;					//뼈이름, 잘안씀.
	//D3DXMATRIX              TransformationMatrix; //
	//LPD3DXMESHCONTAINER     pMeshContainer;		//
	//struct _D3DXFRAME       *pFrameSibling;		//형제 bone
	//struct _D3DXFRAME       *pFrameFirstChild;	//자식 bone

	Matrix		CombinedTransformMatrix; //부모 뼈 매트릭스 * 내 뼈
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

	Matrix*				pFrameOffsetMatrix; //자신의 본래 행렬.
	Matrix**			ppCombinedTrasnformMatrix; //자신 행렬에 부모행렬 곱해서 나올 최종 행렬.
						//=> 본 스페이스에 있음.
	Matrix*				pRenderingMatrix; //최종적으로 모든 변환이 끝나고 렌더링에 쓸 행렬.
						//=> pFrameOffsetMatrix * CombinedTransformMatrix
}MeshContainer_Derived;
 


#pragma endregion
#endif //_ENGINE_STRUCT_H_