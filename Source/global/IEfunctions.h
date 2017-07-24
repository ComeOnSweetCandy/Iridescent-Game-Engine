/***********************************
* name     : IEfunctions.h
* creater  : cosc
* info     : base functions
* date     : 2016/11/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_FUNCTIONS__
#define __IE_FUNCTIONS__

#include "IEvar.h"

/************
* number controll
*************/
#define __IE_ABS__(__x__)\
	__x__ > 0 ? __x__: -__x__

#define __IE_MAX__(__x__,__y__)\
	(__x__ > __y__) ? __x__ : __y__

#define __IE_MIN__(__x__,__y__)\
	(__x__ < __y__) ? __x__ : __y__

/************
* bit controll
*************/
#define __IE_INTREVERSE__(__value__)\
	(((__value__ << 24) & 0xff000000) | ((__value__ & 0x0000ff00) << 8) | ((__value__ & 0x00ff0000) >> 8) | ((__value__ >> 24) & 0x000000ff))

#define __IE_PTRTOINT__(__value__)\
	((*(__value__ + 3)) | (*(__value__ + 2)) | (*(__value__ + 1)) | (*(__value__ + 0)))

/************
* Release
*************/
#define __IE_DELETE__(__p__)\
if (__p__)\
{\
	delete __p__; \
	__p__ = NULL; \
}

#define __IE_DELETES__(__p__)\
if (__p__)\
{\
	delete[] __p__; \
	__p__ = NULL; \
}

#define __IE_RELEASE__(__p__)\
if (__p__)\
{\
	__p__->Release(); \
	__p__ = NULL; \
}

#define __IE_RELEASE_DIF__(__p__)\
if (__p__)\
{\
	__p__->ReleaseDisreference(); \
	__p__ = NULL; \
}

#define __IE_RELEASES_DIF__(__p__,__c__)\
for (int index = 0; index < __c__; index++)\
{\
	if (__p__[index])\
	{\
	__p__[index]->ReleaseDisreference(); \
	__p__[index] = NULL; \
	}\
}

#define __IE_LUA_RELEASE__(__p__)\
if (__p__)\
{\
	lua_close(__p__); \
	__p__ = NULL; \
}

#define __IE_FCLOSE__(__p__)\
if (__p__)\
{\
	fclose(__p__); \
	__p__ = NULL; \
}

/************
* Debug
*************/
#ifdef  __IE_DEBUG__
#define __IE_WARNING__(__content__)\
do\
{\
	printf("%s\n", __content__); \
}while (0)
#define __IE_ERROR__(__error__)\
do\
{\
	printf("%s\n", __error__); \
	throw __error__; \
}while (0)
#define __IE_MEMORY_LEAK_DETECTED_WITH_DELETE__\
	delete this; \
	_CrtDumpMemoryLeaks(); \
	exit(0);
#define __IE_MEMORY_LEAK_DETECTED__\
	_CrtDumpMemoryLeaks(); \
	exit(0);
#else
#define __IE_WARNING__(__content__)
#define __IE_ERROR__(__content__)
#define __IE_MEMORY_LEAK_DETECTED_WITH_DELETE__
#define __IE_MEMORY_LEAK_DETECTED__
#endif

/************
* Lua
*************/
extern "C"
{
#include "../../../libs/lua/src/lua.hpp"
}

extern "C" __IE_DLL__ float GetLuaFloatElement(lua_State * luaScript, const char * name);
extern "C" __IE_DLL__ int GetLuaIntElement(lua_State * luaScript, const char * name);
extern "C" __IE_DLL__ char *  GetLuaStringElement(lua_State * luaScript, const char * name);

extern "C" __IE_DLL__ void SetLuaUserdataElement(lua_State * luaScript, const char * paramName, const char * className, void * data);
extern "C" __IE_DLL__ void * GetLuaUserdataElement(lua_State * luaScript, const char * paramName);

extern "C" __IE_DLL__ bool AllocateLuaFunction(lua_State * luaScript, const char * functionName);

#endif