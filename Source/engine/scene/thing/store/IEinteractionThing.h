/***********************************
* name     : IEinteractionThing.h
* creater  : cosc
* info     : interactionThing
* date     : 2017/4/25
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_INTERACTION_THING__
#define __IE_INTERACTION_THING__

#include "../IEthing.h"

IE_BEGIN

class __IE_DLL__ IEInteractionThing :public IEThing
{
public:
	IEInteractionThing();
	virtual ~IEInteractionThing();
	virtual void Initialization(unsigned int thingID);
	static IEInteractionThing * Create(unsigned int thingID);

public:
	void BindRelatedThing(IEThing * thing);

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
	IEThing * m_relatedThing;
};

IE_END

#endif