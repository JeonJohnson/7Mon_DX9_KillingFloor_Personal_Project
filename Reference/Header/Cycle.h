#pragma once

#ifndef _CYCLE_H_
#define _CYCLE_H_


class _declspec(dllexport) Cycle abstract
{
public:
	Cycle();
	virtual ~Cycle();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void ReadyRender();
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