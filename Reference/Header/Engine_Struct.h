#pragma once

#ifndef _ENGINE_STRUCT_H_
#define _ENGINE_STRUCT_H_

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

}VERTEX_UV;
	
	/* FVF */
		//=> Flexible Vertex Format
		//=> a ���ؽ��� �Ӽ�
const unsigned int FVF_COLOR = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;
const unsigned int FVF_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;

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

typedef struct tagIndexBufferInfo
{


}IBUFFER_INFO;


#endif //_ENGINE_STRUCT_H_