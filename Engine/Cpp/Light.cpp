#include "..\Header\Light.h"
#include "DeviceManager.h"

Light::Light()
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	assert(L"Dx9Device is null at Light" && m_pDX9_Device);

	ZeroMemory(&m_tDx9_Light, sizeof(D3DLIGHT9));

}


Light::~Light()
{
}

void Light::Initialize()
{
}

void Light::Release()
{
}

HRESULT Light::Light_On()
{
	HRESULT iTemp = m_pDX9_Device->LightEnable(0, TRUE);
	if (iTemp == S_OK)
	{
		m_bOnOff = true;
		
	}
	else { m_bOnOff = false; }

	return iTemp;
	
}

HRESULT Light::Light_Off()
{
	HRESULT iTemp = m_pDX9_Device->LightEnable(0, FALSE);

	if (iTemp == S_OK)
	{
		m_bOnOff = false;

	}
	else { m_bOnOff = true; }

	return iTemp;
}

bool Light::Get_IsOn()
{
	return m_bOnOff;
}

D3DLIGHT9 Light::Get_Light()
{
	return m_tDx9_Light;
}

void Light::Set_Light(D3DLIGHT9* _pLight)
{
	memcpy(&m_tDx9_Light, _pLight, sizeof(D3DLIGHT9));

	
	//m_tDx9_Light.Type = D3DLIGHT_DIRECTIONAL;
	//m_tDx9_Light.Diffuse = { 255.f, 255.f, 255.f, 255.f };
	////Temp->Ambient = colorTemp * 0.4f;
	////Temp->Specular = colorTemp * 0.6f;
	//Vector3 vTemp = { 1.f, -1.f, 1.f };
	////D3DXVec3Normalize(&vTemp, &vTemp);
	//m_tDx9_Light.Direction = vTemp;

	m_pDX9_Device->SetLight(0, &m_tDx9_Light);
	m_pDX9_Device->LightEnable(0, TRUE);
	
}
