#include "..\Header\VIBuffer.h"
#include "DeviceManager.h"



VIBuffer::VIBuffer()
{

}

VIBuffer::~VIBuffer()
{
	Release();
}

void VIBuffer::Release()
{
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}

const wstring & VIBuffer::Get_Name() const
{
	return m_wName;
}

LPDIRECT3DVERTEXBUFFER9 VIBuffer::Get_VBuffer_Com() const
{
	return m_pVB;
}

const VBUFFER_INFO & VIBuffer::Get_VBuffer_Info() const
{
	return m_tVBInfo;
}

LPDIRECT3DINDEXBUFFER9 VIBuffer::Get_IBuffer_Com() const
{
	return m_pIB;
}

const IBUFFER_INFO & VIBuffer::Get_IBuffer_Info() const
{
	return m_tIBInfo;
}

D3DPRIMITIVETYPE VIBuffer::Get_DrawType() const
{
	return m_eDrawType;
}

int VIBuffer::Get_RenderLayer() const
{
	return m_iRenderLayer;
}

VIBUFFER_KIND VIBuffer::Get_Kind() const
{
	return m_eKind;
}

void VIBuffer::Set_Name(const wstring & _name)
{
	m_wName = _name;
}

void VIBuffer::Set_VBufferInfo(const VBUFFER_INFO & _tVBuffer)
{
	m_tVBInfo = _tVBuffer;
}

void VIBuffer::Set_IBufferInfo(const IBUFFER_INFO & _tIBuffer)
{
	m_tIBInfo = _tIBuffer;
}

void VIBuffer::Set_DrawType(D3DPRIMITIVETYPE _type)
{
	m_eDrawType = _type;
}

void VIBuffer::Set_RenderLayer(int _iRenderLayer)
{
	m_iRenderLayer = _iRenderLayer;
}

void VIBuffer::Set_Texture(Texture * _pTexture)
{
	return;
}

HRESULT VIBuffer::Render_Texture(int _iNum)
{
	return S_OK;
}

HRESULT VIBuffer::Render_Texture(LPD3DXEFFECT _pEffect, const char* _ShaderTexName, int _iTexNum)
{
	return S_OK;
}


