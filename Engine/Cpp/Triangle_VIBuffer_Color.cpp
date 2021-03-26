#include "..\Header\Triangle_VIBuffer_Color.h"



Triangle_VIBuffer_Color::Triangle_VIBuffer_Color()
{
	Initialize();
}


Triangle_VIBuffer_Color::~Triangle_VIBuffer_Color()
{
}

void Triangle_VIBuffer_Color::Initialize()
{
	VBUFFER_INFO Temp;
	ZeroMemory(&Temp, sizeof(VBUFFER_INFO));

	Temp.m_iVertexCount = 3;
	Temp.m_iPolyCount = 1;
	Temp.m_iVertexMemSize = sizeof(VERTEX_COLOR);
	Temp.m_iFVF = FVF_COLOR;

	Set_VBufferInfo(Temp);
}

void Triangle_VIBuffer_Color::Create_VBuffer()
{
	m_pDX9Device->CreateVertexBuffer(


	);
}

void Triangle_VIBuffer_Color::Create_IBuffer()
{
}


