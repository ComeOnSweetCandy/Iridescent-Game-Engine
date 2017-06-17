/***********************************
* name     : IEthing.h
* creater  : cosc
* info     : adorning tiny grid thing
* date     : 2017/3/19
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING__
#define __IE_THING__

#include "../base/IEblock.h"

IE_BEGIN

class __IE_DLL__ IEThing :public IEBlock
{
public:
	IEThing();
	virtual ~IEThing();
	virtual void Initialization(unsigned int thingID);
	static IEThing * Create(unsigned int thingID);

public:
	void Reload(unsigned int thingID);

	void SetTinyGridPosition(int x, int y);
	IEGrid GetTinyGridPosition();
	void SetThingID(unsigned int adorningID);
	unsigned int GetThingID();
	bool CheckTinyMask(unsigned short tinyMask, int number);

	virtual bool AllocateLuaFunction(const char * functionName);
	void SwitchState();

	void ChangeThingID(unsigned thingID);

	void SetRelatedCreatedOrder(unsigned int relatedCreatedOrder);
	unsigned int GetRelatedCreatedOrder();

	void SetThingLocations(int blockLocationX, int blockLocationY, int tinyLocationX, int tinyLocationY);
	int * GetThingLocations();

	void SetExpress(bool express);
	bool GetExpress();

protected:
	virtual void DrawNode();

private:
	void LoadScript();

protected:
	unsigned int m_thingID;
	unsigned int m_relatedCreatedOrder;
	bool m_express;

	IEGrid m_tinyGridPosition;
	int m_locations[4];

	unsigned char m_maxState;
	unsigned char m_curState;;
};

IE_END

#endif