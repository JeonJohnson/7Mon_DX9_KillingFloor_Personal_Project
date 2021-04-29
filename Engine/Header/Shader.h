#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

#include "Engine_Include.h"

#include "Component.h"

class DLL_STATE Shader : public Component
{
public:
	Shader();
	virtual ~Shader();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

private:
		
};

#endif //_SHADER_H_