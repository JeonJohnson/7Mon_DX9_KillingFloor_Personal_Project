#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Engine_Include.h"
#include "Cycle.h"
#include "GameObject.h"

class _declspec(dllexport) Component : public Cycle
{
public:
	Component();
	~Component();

protected:
	virtual void Initialize() override = 0;
	virtual void Update() override = 0;
	virtual void LateUpdate() override = 0;
	virtual void Release() override = 0;

public: /* functions */
	//template<class T>
	//void Add_Component(T::Desc* _desc)
	//{
	//	m_GameObject->Add_Component<T>(_desc);
	//}

public:

public:

protected:
	GameObject*		m_GameObject;
	//Transform*		m_Transform;

private:

};

#endif