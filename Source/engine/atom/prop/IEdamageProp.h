/***********************************
* name     : IEdamageProp.h
* creater  : cosc
* info     : damage prop
* date     : 2017/3/28
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DAMAGE_PROP__
#define __IE_DAMAGE_PROP__

#include "../IEprop.h"

IE_BEGIN

class __IE_DLL__ IEDamageProp :public IEProp
{
public:
	IEDamageProp();
	virtual ~IEDamageProp();
	virtual void Initialization(int propIndex, IETrigger * trigger, IECreature * propOwner, int damage);
	static IEDamageProp * Create(int propIndex, IETrigger * trigger, IECreature * propOwner, int damage);

public:
	virtual void InteractiveNode(IENode * strikeNode);
	void SetDamage(int damage);

private:
	int m_damage;
};

IE_END

#endif