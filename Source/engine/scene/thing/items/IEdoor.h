/***********************************
* name     : IEdoor.h
* creater  : cosc
* info     : door
* date     : 2017/5/17
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DOOR__
#define __IE_DOOR__

#include "../IEthing.h"

IE_BEGIN

class IEStateThing;

class __IE_DLL__ IEInteractionThing :public IEThing
{
public:
	IEInteractionThing();
	virtual ~IEInteractionThing();
	virtual void Initialization(unsigned int thingID);
	static IEInteractionThing * Create(unsigned int thingID);

public:
	void BindStateThing(IEStateThing * thing);

protected:
	virtual void DrawNode();
	virtual void EndVisit();

	virtual void InteractiveNode(IENode * strikeNode);
	virtual void SetPosition(const float &x, const float &y);

private:
	void BindInteractionTrigger();
	void PormptInitialization();

private:
	IESprite * m_prompt;
	IETrigger * m_trigger;
	IEStateThing * m_stateThing;
};

IE_END

#endif