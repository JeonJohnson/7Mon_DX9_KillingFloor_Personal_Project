#pragma once

#ifndef _UI_H_
#define _UI_H_

#include "Engine_Include.h"

#include "Cycle.h" 

#include "Sprite.h"
#include "Text.h"
#include "UI_Component.h"
#include "Transform.h"


class DLL_STATE UI : public Cycle
{
	//GameObject랑 비슷한 역할.
		//=> Text와 Sprite의 통
	//Text와 Sprite => Component의 역할

private:
	explicit UI() = default;
	virtual ~UI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;
	
public: /* */
	static UI* Instantiate_UI(const wstring& _wNameUI);
	static void Destory_UI(UI* _pUi);

#pragma region Template
public:
	template<class T>
	UI* Add_UIComponent(T::Desc* _desc)
	{
		UI_Component* ui = new T(_desc);
		assert(L"Ui Component create failed" && ui);

		

		return this; 
	}


#pragma endregion

public: /* function */


public: /* Get */
	const wstring&	Get_Name() const;
	UI_Component*	Get_Sprite() const;
	UI_Component*	Get_Text() const;

public: /* Set */


private:
	//tuple<wstring, Sprite*, Text*>	m_tupUIComponents;
	Transform* m_pTransform = nullptr;

	wstring				m_wName;
	UI_Component*		m_pSprite = nullptr;
	UI_Component*		m_pText = nullptr;

};

#endif //_UI_H_