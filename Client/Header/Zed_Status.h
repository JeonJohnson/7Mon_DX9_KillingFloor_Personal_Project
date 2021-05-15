#pragma once

#ifndef _ZED_STATUS_H_
#define _ZED_STATUS_H_

#include "Include.h"

#include "Component.h"

class Zed_Status :	public Component
{
public:
	struct Desc
	{
		
	};

public:
	Zed_Status(Desc* _desc);
	virtual ~Zed_Status();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

public:

private:
	ZED_INFO		m_tZedStatus;
};

#endif //_ZED_STATUS_H_