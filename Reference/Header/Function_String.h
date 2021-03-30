#pragma once

#ifndef _FUNCTION_STRING_H_
#define _FUNCTION_STRING_H_

#include "Engine_Include.h"

class Function_String
{
public:
	Function_String();
	~Function_String();

public: /* to wstring */
	static wstring stringTowstring(const string& _str, wstring _wstr)
	{
		_wstr.assign(_str.begin(), _str.end());
	}

public:

public:

private:


};

#endif //_FUNCTION_STRING_H_