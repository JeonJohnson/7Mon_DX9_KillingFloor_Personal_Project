#include "..\Header\LightManager.h"

Implement_Singleton(LightManager)

LightManager::LightManager()
{
}


LightManager::~LightManager()
{
	Release();
}


void LightManager::Initialize()
{
	D3DXCOLOR	colorTemp = D3DCOLOR_RGBA(253, 251, 211, 255);

	D3DLIGHT9*	Temp = new D3DLIGHT9;
	ZeroMemory(Temp, sizeof(D3DLIGHT9));
	Temp->Type = D3DLIGHT_DIRECTIONAL;
	Temp->Diffuse = colorTemp;
	Temp->Ambient = colorTemp * 0.5f;
	Temp->Specular = colorTemp * 0.8f;
	//Vector3 vTemp = { -0.2f, -1.f, 1.f };
	//Vector3 vTemp = { -1.f, -1.f, .f };
	Vector3 vTemp = { 1.f, -1.f, -1.f };
	Temp->Direction = vTemp;
	Insert_Light(Temp, L"SunShine");
	//EngineFunction->Insert_Light(Temp, L"HatBit");
	delete Temp;

}

void LightManager::Release()
{
	for (auto& light : m_umLightList)
	{
		light.second->Release();
		delete light.second;
	}
	m_umLightList.clear();
}

Light * LightManager::Get_LightByName(const wstring & _Name)
{
	auto iter_find = m_umLightList.find(_Name);

	if (iter_find != m_umLightList.end())
	{
		return iter_find->second;
	}
	else { return nullptr; }
}

void LightManager::Insert_Light(D3DLIGHT9 * _pLight, const wstring & _Name)
{
	if (m_umLightList.size() != 0)
	{
		auto iter_find = m_umLightList.find(_Name);

		if (iter_find != m_umLightList.end())
		{
			Light* temp = new Light;

			temp->Set_Light(_pLight);

			m_umLightList.insert(pair<wstring, Light*>(_Name, temp));


		}
		else
		{
			assert(0 && L"already Light is exist same name");
		}
	}
	else
	{
		//0x0000022091525970
		Light* temp = new Light;
		temp->Set_Light(_pLight);
		m_umLightList.insert(pair<wstring, Light*>(_Name, temp));
	}

	
}
