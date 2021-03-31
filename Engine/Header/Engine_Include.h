#pragma once

#ifndef _ENGINE_INCUDE_H_
#define _ENGINE_INCUDE_H_

/* Fuck the warning */
#pragma warning(disable : 4251)


/* Default */
#include <windows.h>

#include <assert.h>

#include <iostream>
using namespace std;
#include <ctime>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#include <string.h>
#include <tchar.h>

#include <math.h>

#include <algorithm>

/* Memory Leak */



/* MultiThread */
#include <process.h>


/* STL */
#include <map>
#include <unordered_map>
#include <vector>
#include <list>


/* Direct 9 */
#include <d3d9.h>
#include <d3dx9.h>
//#include <d3dx9math.h>


/* Custom */
#include "Engine_TypeDef.h"
#include "Engine_Define.h"
#include "Engine_Enum.h"
#include "Engine_Extern.h"
#include "Engine_Struct.h"


#endif //_ENGINE_INCUDE_H_