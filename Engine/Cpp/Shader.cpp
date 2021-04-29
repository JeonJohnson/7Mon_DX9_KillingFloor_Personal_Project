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

	// 에러 메세지에 따른 경우의 수

	// m_pEffect의 값이 있고 m_pErrMsg값이 없는 경우 : 정상적인 컴파일 수행 완료
	// m_pEffect의 값이 없고 m_pErrMsg값이 있는 경우 : 쉐이더 코드 상 컴파일 에러가 있는 경우
	// m_pEffect의 값이 있고 m_pErrMsg값도 있는 경우 : 쉐이더 코드 상 경고가 있는 경우

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



