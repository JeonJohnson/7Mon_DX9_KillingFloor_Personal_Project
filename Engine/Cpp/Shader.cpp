#include "..\Header\Shader.h"
#include "DeviceManager.h"


Shader::Shader(Desc * _desc)
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	assert(L"Dx9 Device is null" && m_pDX9_Device);

	Ready_Shader(_desc->pFilePath);


}

Shader::~Shader()
{
}

void Shader::Initialize()
{
}

void Shader::Update()
{
}

void Shader::LateUpdate()
{
}

void Shader::ReadyRender()
{
}

void Shader::Release()
{
	Safe_Release(m_pEffect);
}

HRESULT Shader::Ready_Shader(const wstring & _szShaderFilePath)
{
	if (FAILED(D3DXCreateEffectFromFile(m_pDX9_Device,
		_szShaderFilePath.c_str(),
		NULL,
		NULL,
		D3DXSHADER_DEBUG, NULL,
		&m_pEffect,
		&m_pErrMsg)))
	{
		MessageBoxA(NULL, (char*)m_pErrMsg->GetBufferPointer(), "Shader_Error", MB_OK);
		return E_FAIL;
	}

	else if (nullptr != m_pErrMsg)
	{
		MessageBoxA(NULL, (char*)m_pErrMsg->GetBufferPointer(), "Shader_Warning", MB_OK);
	}

	return S_OK;
}

LPD3DXEFFECT Shader::Get_ComEffect() const
{
	return m_pEffect;
}

