#pragma once

#ifndef _UI_H_
#define _UI_H_

#include "Engine_Include.h"

#include "Cycle.h" 

//#include "Sprite.h"
//#include "Text.h"

#include "UI_Component.h"
#include "Transform.h"

/* Define */
#define INSTANTIATE_UI	UI::Instantiate_UI
#define DESTROY_UI		UI::Destory_UI

class DLL_STATE UI : public Cycle
{
	//GameObject랑 비슷한 역할.
		//=> Text와 Sprite의 통
	//Text와 Sprite => Component의 역할
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
	static UI* Instantiate_UI(const wstring& _wNameUI, bool _bIsStatic = false);
	static void Destory_UI(UI* _pUi);

#pragma region Template
public:
	template<class T>
	UI* Add_UIComponent(class T::Desc* _desc)
	{
		UI_Component* ui = nullptr;
		ui = UI_Component::Instantiate<T>(_desc);
		assert(L"Ui Component create failed" && ui);

		ui->Set_UiObject(this);

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

	template<class T>
	T* Get_UIComponent()
	{
		//시발 어쩃건 찾을라면 string값 필요하네
		string strName = typeid(T).name(); //클래스 이름을 string형으로 바까줌
		
		if (strName == "class Text")
		{
			return (T*)m_pText;
		}
		
		if (strName == "class Sprite")
		{
			return (T*)m_pSprite;
		}

		return nullptr;
	}


#pragma endregion

public: /* function */
	void Delete_UiComponents();
	void Update_UITransform();
	
	bool Clikced();
	bool Pressed();
	bool ClickedUp();
	bool MouseOn();

public: /* Get */
	const wstring&	Get_Name() const;
	UI_Component*	Get_Sprite();
	UI_Component*	Get_Text();

	const RECT&			Get_Rect() const;
	const Vector3&	Get_Position() const;
	const Vector3&	Get_Scale()	const;
	const Vector3&	Get_Rotation() const;
	const Vector3&	Get_Center() const;
	

public: /* Set */
	void			Set_Active(bool _onoff);
	void			Set_Alive(bool _FalseIsDead);
	void			Set_Button(bool _bButton);

	void			Set_Position(const Vector3& _vPos);
	void			Add_Position(const Vector3& _vPos);

	void			Set_Scale(const Vector3& _vScale);
	void			Add_Scale(const Vector3& _vScale);

	void			Set_Rotate(const Vector3& _vRot);
	void			Rotate(const Vector3& _vRot); //Add Rotation;
	//void			Set_Rotation(const Vector3& _vRot);
	//void			Add_Rotation()

	void			Set_Rect(const RECT& _tRect);
	void			Set_Width(float _fWidth);
	void			Set_Height(float _fHeight);


private:
	//tuple<wstring, Sprite*, Text*>	m_tupUIComponents;
	//Transform* m_pTransform = nullptr;

	Vector3				m_vPosition = { 720.f, 360.f,0.f };
	Vector3				m_vScale = { 1.f, 1.f, 0.f };
	Vector3				m_vRotation = { 0.f,0.f,0.f };
	
	float				m_fWidth;
	float				m_fHeight;
	Vector3				m_vCenter;
	RECT				m_tRect;

	bool				m_bButton = false;

	bool				m_bMouseOver = false; //for sound

	bool				m_bActive = true;
	bool				m_bAlive = true;
	bool				m_bDontDestroy;
	
	wstring				m_wName;
	UI_Component*		m_pSprite = nullptr;
	UI_Component*		m_pText = nullptr;

	////vector<UI_Component*>	m_vecUIComponents;
	

	unordered_map<wstring, UI_Component*> m_umSprites;
	unordered_map<wstring, UI_Component*> m_umTexts;

};

#endif //_UI_H_