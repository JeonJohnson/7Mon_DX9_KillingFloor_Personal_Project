#pragma once

#ifndef _ENGINE_STRUCT_H_
#define _ENGINE_STRUCT_H_

/* vertex Buffer */
	/* Vertex Structure */
		//=> Vertex has what property 

	/* FVF */
		// 

typedef struct tagVertexBufferInfo
{

	unsigned int	m_iVertexCount = 0;
	unsigned int	m_iVertexMemSize = 0;
	unsigned int	m_iPolyCount = 0;
	unsigned int	m_iFVF = 0;

}VBUFFER_INFO;

/* index Buffer */

typedef struct tagIndexBufferInfo
{


}IBUFFER_INFO;


#endif