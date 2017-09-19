/***********************************
* name     : IEtrigger.h
* creater  : cosc
* info     : 触发器的作用在于 每当一个条件触发 会反馈给相应的节点
* date     : 2017/1/19
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TRIGGER__
#define __IE_TRIGGER__

#include "../../physic/IEphysicNode.h"

IE_BEGIN

class IEContainer; 
class IEAtom;

typedef void(IEAtom::*IETrggerStrike)(IEPhysicNode * physicNode);			//触发器触发了的情况

enum IETriggerType
{
	__trigger_warn_type__,			//警戒类型 在一定范围内就会触发
	__trigger_collision_type__,		//碰撞类型 碰撞了就会触发
	__trigger_interaction_type__,	//互动类型 
	__trigger_type_count__			//计数
};

class __IE_DLL__ IETrigger:public IEPhysicNode
{
public:
	IETrigger();
	virtual ~IETrigger();
	virtual void Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);
	static IETrigger * Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);

public:
	IETriggerType GetTriggerType();									//获取触发器类型
	void SetAllowStrikeRepeat(bool allowStrikeRepeat);				//设定是否允许重复触发
	void SetAllowStrikeRepeatByOne(bool allowStrikeRepeatByOne);	//设定是否允许被同一个物体重复触发

	void ActivateTrigger(IEAtom * self, IETrggerStrike function);		//设定一个新的trigger 绑定到一个atom上 并且绑定至物理世界

protected:
	virtual void RunTrigger();										//运行trigger
	virtual void Collision(IEPhysicNode * physicNode);				//重载碰撞
	virtual void TriggerStrike(IEPhysicNode * physicNode);			//最终判定触发器触发

protected:
	IETriggerType m_triggerType;			//触发器的类型
	IEAtom * m_attachAtom;					//触发器依附的atom
	IETrggerStrike m_function;				//触发器触发后的反馈

	bool m_allowStrikeRepeat;				//是否允许节点重复触发
	bool m_allowStrikeRepeatByOne;			//是否允许节点被同一个物体重复触发

	IEContainer * m_strikeNodes;			//已经启动过触发器的节点
};

IE_END

#endif