/***********************************
* name     : IEbesiegeThing.h
* creater  : cosc
* info     : besiege thing
* date     : 2017/5/17
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_BESIEGE_THING__
#define __IE_BESIEGE_THING__

#include "../IEthing.h"

IE_BEGIN

class __IE_DLL__ IEBesiegeThing :public IEThing
{
public:
	IEBesiegeThing();
	virtual ~IEBesiegeThing();
	virtual void Initialization(unsigned int thingID);
	static IEBesiegeThing * Create(unsigned int thingID);

public:
	void BindRelatedThing(IEThing * thing);

protected:
	virtual void DrawNode();

	virtual void InteractiveNode(IENode * strikeNode);
	virtual void SetPosition(const float &x, const float &y);

private:
	void BindInteractionTrigger();

private:
	IETrigger * m_trigger;
	IEThing * m_relatedThing;
};

IE_END

#endif