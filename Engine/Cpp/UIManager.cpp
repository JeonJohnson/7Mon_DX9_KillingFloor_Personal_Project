#include "..\Header\UIManager.h"

Implement_Singleton(UIManager)

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

void UIManager::Insert_UI(UI * _pUi, const wstring& _name)
{
	assert(L"UIInsert Failed at UiManager" && _pUi);

	//wstring name = _pUi->Get_Name();
	//wstring 중복값 처리 해주삼

	m_vecUIList.emplace_back(pair<wstring, UI*>(_name, _pUi));

	m_vecUIList.shrink_to_fit();
}
