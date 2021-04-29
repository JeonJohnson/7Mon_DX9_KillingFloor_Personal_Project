#include "..\Header\Shader.h"
#include "DeviceManager.h"


//Shader::Shader(Desc * _desc)
//{
//	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
//	assert(L"Dx9 Device is null" && m_pDX9_Device);
//
//	Ready_Shader(_desc->pFilePath);
//}

Shader::Shader()
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	assert(L"Shader's Device is nullptr" && m_pDX9_Device);
}

Shader::~Shader()
{
	Safe_Release(m_pEffect);
}

//void Shader::Initialize()
//{
//}
//
//void Shader::Update()
//{
//}
//
//void Shader::LateUpdate()
//{
//}
//
//void Shader::ReadyRender()
//{
//}
//
//void Shader::Release()
//{
//	
//}

HRESULT Shader::Ready_Shader(const wstring & _szShaderFilePath)
{

	// ���� �޼����� ���� ����� ��

	// m_pEffect�� ���� �ְ� m_pErrMsg���� ���� ��� : �������� ������ ���� �Ϸ�
	// m_pEffect�� ���� ���� m_pErrMsg���� �ִ� ��� : ���̴� �ڵ� �� ������ ������ �ִ� ���
	// m_pEffect�� ���� �ְ� m_pErrMsg���� �ִ� ��� : ���̴� �ڵ� �� ��� �ִ� ���

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

LPD3DXEFFECT Shader::Get_EffectCom() const
{
	return m_pEffect;
}



