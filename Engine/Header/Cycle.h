#pragma once

#ifndef _CYCLE_H_
#define _CYCLE_H_


class DLL_STATE Cycle abstract
{
public:
	Cycle();
	virtual ~Cycle();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void ReadyRender() = 0;
	virtual void Render(); 
	virtual void Release() = 0;

public:
	//Active On/Off
	virtual void On_Active();
	virtual void Off_Active();

public:
	//collision


};

#endif