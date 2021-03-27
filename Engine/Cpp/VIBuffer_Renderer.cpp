#include "..\Header\VIBuffer_Renderer.h"
#include "Triangle_VIBuffer_Color.h"



VIBuffer_Renderer::VIBuffer_Renderer(Desc * _desc)
{
	
	m_pVIBuffer = new Triangle_VIBuffer_Color;

	m_pVIBuffer->Set_RenderLayer(_desc->iLayer);
}

VIBuffer_Renderer::~VIBuffer_Renderer()
{
}

void VIBuffer_Renderer::Initialize()
{
}

void VIBuffer_Renderer::Update()
{
}

void VIBuffer_Renderer::LateUpdate()
{
}

void VIBuffer_Renderer::Render()
{
	Binding_Stream_VIBuffer();

	m_pDX9Device->DrawPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		1);
}

void VIBuffer_Renderer::ReadyRender()
{

}

void VIBuffer_Renderer::Release()
{
}

void VIBuffer_Renderer::Binding_Stream_VIBuffer()
{
	m_pDX9Device->SetStreamSource(
		0,
		m_pVIBuffer->Get_VBuffer_Com(),
		0,
		sizeof(m_pVIBuffer->Get_VBuffer_Info().m_iVertexMemSize));

	m_pDX9Device->SetFVF(m_pVIBuffer->Get_VBuffer_Info().m_iFVF);

}

VIBuffer * VIBuffer_Renderer::Get_VIBuffer() const
{
	return m_pVIBuffer;
}

void VIBuffer_Renderer::Set_VIBuffer(const wstring & _wBufferName)
{

}


