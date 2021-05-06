#include "..\Header\UIManager.h"

Implement_Singleton(UIManager)

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
	Release();
}

void UIManager::Initailize()
{

}

void UIManager::Update()
{
	for (auto& uiObj : m_vecUIList)
	{
		uiObj.second->Update();
	}

	for (auto& staticUi : m_vecStaticUiList)
	{
		staticUi.second->Update();
	}
}

void UIManager::LateUpdate()
{
	for (auto& uiObj : m_vecUIList)
	{
		uiObj.second->LateUpdate();
	}

	for (auto& staticUi : m_vecStaticUiList)
	{
		staticUi.second->LateUpdate();
	}
}

void UIManager::ReadyRender()
{
	for (auto& uiObj : m_vecUIList)
	{
		uiObj.second->ReadyRender();
	}

	for (auto& staticUi : m_vecStaticUiList)
	{
		staticUi.second->ReadyRender();
	}
}

void UIManager::Render()
{
	for (auto& uiObj : m_vecUIList)
	{
		uiObj.second->Render();
	}

	for (auto& staticUi : m_vecStaticUiList)
	{
		staticUi.second->Render();
	}
}

void UIManager::Release()
{
	//스태틱이고 뭐고 다 지우기

	for (auto UIiter = m_vecUIList.begin(); UIiter != m_vecUIList.end();)
	{
		(*UIiter).second->Release();

		delete (*UIiter).second;
		UIiter = m_vecUIList.erase(UIiter);
	}
	if (m_vecUIList.size() > 0)
	{
		assert(0 && L"Ui List Dont earse all");
	}

	for (auto UIiter = m_vecStaticUiList.begin(); UIiter != m_vecStaticUiList.end();)
	{
		(*UIiter).second->Release();

		delete (*UIiter).second;
		UIiter = m_vecStaticUiList.erase(UIiter);
	}
	if (m_vecStaticUiList.size() > 0)
	{
		assert(0 && L"Static Ui List Dont earse all");
	}

}

void UIManager::Release_Scene()
{
	for (auto UIiter = m_vecUIList.begin(); UIiter != m_vecUIList.end();)
	{
		(*UIiter).second->Release();

		delete (*UIiter).second;
		UIiter = m_vecUIList.erase(UIiter);
	}
}


HRESULT UIManager::Insert_UI(UI * _pUi, const wstring& _name)
{
	assert(L"UIInsert Failed at UiManager" && _pUi);

	//wstring name = _pUi->Get_Name();
	//wstring 중복값 처리 해주삼
	
	for (auto& uicomponent : m_vecUIList)
	{
		if (uicomponent.first == _name)
		{
			return E_FAIL;
		}
	}

	m_vecUIList.emplace_back(pair<wstring, UI*>(_name, _pUi));

	m_vecUIList.shrink_to_fit();

	return S_OK;
}

HRESULT UIManager::Insert_StaticUI(UI * _pUi, const wstring & _name)
{
	assert(L"UIInsert Failed at UiManager" && _pUi);

	//wstring name = _pUi->Get_Name();
	//wstring 중복값 처리 해주삼

	for (auto& uicomponent : m_vecStaticUiList)
	{
		if (uicomponent.first == _name)
		{
			return E_FAIL;
		}
	}

	m_vecStaticUiList.emplace_back(pair<wstring, UI*>(_name, _pUi));

	m_vecStaticUiList.shrink_to_fit();

	return S_OK;
}
