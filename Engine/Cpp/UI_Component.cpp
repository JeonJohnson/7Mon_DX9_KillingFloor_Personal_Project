#include "..\Header\UI_Component.h"

#include "Transform.h"

void UI_Component::Initialize()
{

}

void UI_Component::Update()
{

}

void UI_Component::LateUpdate()
{

}

void UI_Component::ReadyRender()
{

}

void UI_Component::Render()
{

}

void UI_Component::Release()
{

}

bool UI_Component::Get_Active() const
{
	return m_bActive;
}

bool UI_Component::Get_Alive() const
{
	return m_bAlive;
}


void UI_Component::Set_Active(bool _onoff)
{
	m_bActive = _onoff;
}

void UI_Component::Set_Alive(bool _FalseIsDead)
{
	m_bAlive = _FalseIsDead;
}

void UI_Component::Set_UiObject(UI * _uiobj)
{
	m_UiObject = _uiobj;
}

