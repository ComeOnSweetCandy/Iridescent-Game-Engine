/***********************************
* name     : IEvar.h
* creater  : cosc
* info     : base defined
* date     : 2016/11/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_VAR__
#define __IE_VAR__

/************
* engine info
*************/
#define IE_VERSION 1.0.0

/************
* Exprots
*************/
#ifdef __IE_DLL_EXPORTS__  
#define __IE_DLL__ __declspec(dllexport)   
#else  
#define __IE_DLL__ __declspec(dllimport)   
#endif

/************
* Namespace
*************/
#define IE_BEGIN	namespace IridescentEngine{
#define IE_END		}
#define USEIE		using namespace IridescentEngine

/************
* Base number
*************/
#define IEPI 3.1415926

#define __IE_DEBUG__

#pragma warning(disable:4477)
#pragma warning(disable:4996)

#endif