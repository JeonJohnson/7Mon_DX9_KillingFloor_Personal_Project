#pragma once

#ifndef _ENGINE_STRUCT_H_
#define _ENGINE_STRUCT_H_

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

}VERTEX_UV;
	
	/* FVF */
		//=> Flexible Vertex Format
		//=> a 버텍스의 속성
const unsigned int FVF_COLOR = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;
const unsigned int FVF_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;

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

typedef struct tagIndexBufferInfo
{


}IBUFFER_INFO;


#endif //_ENGINE_STRUCT_H_