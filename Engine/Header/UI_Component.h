#pragma once

#ifndef _UI_COMPONENT_H_
#define _UI_COMPONENT_H_

#include "Engine_Include.h"

#include "Cycle.h"

class UI;
class Transform;

class UI_Component : public Cycle
{
public:
	explicit UI_Component() = default;
	virtual ~UI_Component() = 0;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Render() override;
	virtual void Release() override;

#pragma region	Template
public:



#pragma endregion

public:

public:

public:

private:
	
};

#endif //_UI_COMPONENT_H_