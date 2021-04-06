#include "..\Header\UIManager.h"

Implement_Singleton(UIManager)

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

void UIManager::Initailize()
{

}

void UIManager::Update()
{

}

void UIManager::LateUpdate()
{

}

void UIManager::ReadyRender()
{

}

void UIManager::Render()
{
	for (auto& uiObj : m_vecUIList)
	{
		uiObj.second->Render();
	}
}

void UIManager::Release()
{

}

void UIManager::Release_Scene()
{
	for(auto& UIs : m_vecUIList)
	{
		UIs.second->Release();
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
