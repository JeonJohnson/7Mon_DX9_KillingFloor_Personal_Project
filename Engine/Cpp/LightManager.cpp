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
