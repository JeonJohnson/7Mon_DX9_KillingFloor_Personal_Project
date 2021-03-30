#pragma once

#ifndef _CRESOURCE_H_
#define _CRESOURCE_H_

#include "Engine_Include.h"

class DLL_STATE CResource abstract
{
	friend class ResourceManager;

public:
	CResource();
	virtual ~CResource();

protected:
	virtual void Initialize() = 0;
	virtual void Release() = 0;
	
	
};

#endif //_RESOURCE_H_