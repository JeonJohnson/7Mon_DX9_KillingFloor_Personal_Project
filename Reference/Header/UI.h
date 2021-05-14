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
		//�ù� ��� ã����� string�� �ʿ��ϳ�
		string strName = typeid(T).name(); //Ŭ���� �̸��� string������ �ٱ���
		
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

	void			Set_Position(const Vector3& _vPos);
	void			Add_Position(const Vector3& _vPos);

	void			Set_Scale(const Vector3& _vScale);
	void			Add_Scale(const Vector3& _vScale);

	void			Set_Rotate(const Vector3& _vRot);
	void			Rotate(const Vector3& _vRot); //Add Rotation;
	//void			Set_Rotation(const Vector3& _vRot);
	//void			Add_Rotation()

private:
	//tuple<wstring, Sprite*, Text*>	m_tupUIComponents;
	//Transform* m_pTransform = nullptr;

	Vector3				m_vPosition;
	Vector3				m_vScale;
	Vector3				m_vRotation;
	
	float				m_fWidth;
	float				m_fHeight;
	Vector3				m_vCenter;
	RECT				m_tRect;

	bool				m_bActive;
	bool				m_bAlive;
	bool				m_bDontDestroy;
	
	wstring				m_wName;
	UI_Component*		m_pSprite = nullptr;
	UI_Component*		m_pText = nullptr;
	//vector<UI_Component*>	m_vecUIComponents;
	

	unordered_map<wstring, UI_Component*> m_umSprites;
	unordered_map<wstring, UI_Component*> m_umTexts;

};

#endif //_UI_H_