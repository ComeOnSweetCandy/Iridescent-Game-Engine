/***********************************
* name     : IEAtom.h
* creater  : cosc
* info     : everthing in this world were based atom
* date     : 2016/12/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ATOM__
#define __IE_ATOM__

#include "../../core/element/IEsprite.h"
#include "../trigger/IEtrigger.h"

IE_BEGIN

class __IE_DLL__ IEAtom:public IESprite
{                              
public:
	IEAtom();
	virtual ~IEAtom();
	virtual void Initialization();
	static IEAtom * Create();

public:
	virtual void SetTranslate(const float &x, const float &y);							//如果有phsyicNode

	virtual void ChangeState(const char * stateName);									//改变事物当前的状态
	virtual void ChangeGroup(const char * groupName, unsigned int sameIndex = 1);		//重载更改贴图组事件
	virtual void ChangeGroup(const char * groupName, unsigned int sameIndex, unsigned int playTimes, IEFunctionTexturePlayEnded playEndedFunction);	//带次数的动作更改

	void AddTrigger(IETrigger * trigger);										//添加一个触发器
	void AddTrigger(IETrigger * trigger, const char * functionLua);				//添加一个触发器
	void DelTrigger(IETriggerType type);										//删除一个触发器
	void TriggerStrike(IEPhysicNode * physicNode);								//触发器触发

	lua_State * GetLuaScript();

protected:
	virtual void ArrangeInfo();			//大多数调用后 进行自身的处理

protected:
	unsigned m_triggersCount;			//触发器计数
	IETrigger * m_triggers;				//保存有所有类型的触发器

	lua_State * m_LUA;					//脚本文件
	IEXml * m_XML;						//资源信息文件
};

IE_END

#endif