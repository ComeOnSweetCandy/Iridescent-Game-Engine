/***********************************
* name     : IEBlock
* creater  : cosc
* info     : block
* date     : 2016/12/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_BLOCK__
#define __IE_BLOCK__

#include "../atom/IEstill.h"

IE_BEGIN

class __IE_DLL__ IEBlock :public IEStill
{
public:
	IEBlock();
	virtual ~IEBlock();
	virtual void Initialization();
	static IEBlock * Create();
	
public:
	virtual void SetTranslate(float x, float y);	//重载该函数 可以在进行位置定位时 确定physicNode的位置

	void SetOrder(unsigned int order);
	unsigned int GetOrder();

protected:
	unsigned int m_order;							//代表被创造的顺序 在terrain和thing中会起到作用 所有都从1开始 0作为空置位
};

IE_END

#endif