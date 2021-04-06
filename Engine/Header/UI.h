#pragma once

#ifndef _UI_H_
#define _UI_H_

#include "Engine_Include.h"

#include "Cycle.h" 

//#include "Sprite.h"
//#include "Text.h"

#include "UI_Component.h"
#include "Transform.h"

/* define */
#define INSTANTIATE_UI	UI::Instantiate_UI
#define DESTROY_UI		UI::Destory_UI

class DLL_STATE UI : public Cycle
{
	//GameObject�� ����� ����.
		//=> Text�� Sprite�� ��
	//Text�� Sprite => Component�� ����
	friend class UIManager;

private:
	explicit UI() = default;
	virtual ~UI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Render()override;
	virtual void Release() override;
	
public: /* */
	static UI* Instantiate_UI(const wstring& _wNameUI);
	static void Destory_UI(UI* _pUi);

#pragma region Template
public:
	template<class T>
	UI* Add_UIComponent(class T::Desc* _desc)
	{
		UI_Component* ui = nullptr;
		ui = UI_Component::Instantiate<T>(_desc);
		assert(L"Ui Component create failed" && ui);

		UI_KIND temp = ui->Get_UIkind();

		switch (temp)
		{
			case UI_KIND::UI_SPRITE:
			{
				m_pSprite = ui;
			}
			break;

			case UI_KIND::UI_TEXT:
			{
				m_pText = ui;
			}
			break;
			
			default:
				break;
		}

		return this;
	}


#pragma endregion

public: /* function */
	void Delete_UiComponents();

public: /* Get */
	const wstring&	Get_Name() const;
	UI_Component*	Get_Sprite();
	UI_Component*	Get_Text();


public: /* Set */

	

private:
	//tuple<wstring, Sprite*, Text*>	m_tupUIComponents;
	Transform* m_pTransform = nullptr;

	bool				m_bActive;
	bool				m_bAlive;
	
	wstring				m_wName;
	UI_Component*		m_pSprite = nullptr;
	UI_Component*		m_pText = nullptr;

};

#endif //_UI_H_