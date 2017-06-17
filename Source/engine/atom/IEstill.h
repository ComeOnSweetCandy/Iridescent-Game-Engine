/***********************************
* name     : IEstill.h
* creater  : cosc
* info     : still thing
* date     : 2017/2/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_STILL__
#define __IE_STILL__

#include "IEatom.h"

IE_BEGIN

class __IE_DLL__ IEStill :public IEAtom
{
public:
	IEStill();
	virtual ~IEStill();
	virtual void Initialization(char * still);
	static IEStill * Create(char * still);

private:

};

IE_END

#endif