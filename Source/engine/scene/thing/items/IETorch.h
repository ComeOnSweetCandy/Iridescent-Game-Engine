/***********************************
* name     : IETorch.h
* creater  : cosc
* info     : fire
* date     : 2017/4/24
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TORCH__
#define __IE_TORCH__

#include "../IEThing.h"

IE_BEGIN

class __IE_DLL__ IETorch :public IEThing
{
public:
	IETorch();
	virtual ~IETorch();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IETorch * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

protected:
	virtual void Update();
	virtual void DrawNode();
	virtual void DrawLight();
	virtual void DrawFire();

private:
	void SetProperty();

private:
	IEColor m_lightColor;			//torch的颜色
	float m_distance;				//距离
	float m_baseLight;				//基础亮度
	float m_intension;				//衰减值
	float m_curIntension;			//当前衰减值

	float _curMulti;
	int _value;
	float _speed;
};

IE_END

#endif