#pragma once



class _declspec(dllexport) Cycle abstract
{
public:
	Cycle();
	virtual ~Cycle();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Release() = 0;

public:
	//Active On/Off

public:
	//collision


};

