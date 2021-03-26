#include "..\Header\VIBuffer.h"
#include "DeviceManager.h"



VIBuffer::VIBuffer()
{
	m_pDX9Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	assert(L"DX9Device is null at VIBuffer" && m_pDX9Device);
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
