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
#include "../../physic/IEphysicNode.h"
#include "creature/action/IEActionMachine.h"
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
	virtual void ChangeState(const char * stateName);									//�ı����ﵱǰ��״̬
	virtual void ChangeGroup(const char * groupName, unsigned int sameIndex = 1);		//���ظ�����ͼ���¼�

	void AddTrigger(IETrigger * trigger);										//���һ��������
	void AddTrigger(IETrigger * trigger, const char * functionLua);				//���һ��������
	void DelTrigger(IETriggerType type);										//ɾ��һ��������
	void TriggerStrike(IEPhysicNode * physicNode);								//����������

	lua_State * GetLuaScript();

public:
	virtual void Update();				//ÿ��ˢ��

	virtual void Born();				//ÿһ֡�Ĵ���
	virtual void Live();				//liveʱ�Ĵ���
	virtual void Die();					//dieʱ�Ĵ���

protected:
	unsigned m_triggersCount;			//����������
	IETrigger * m_triggers;				//�������������͵Ĵ�����
	lua_State * m_LUA;					//�ű��ļ�
	IEXml * m_XML;						//��Դ��Ϣ�ļ�

	//��ʾ��ǰ��״̬��ż����״ֵ̬
	unsigned int m_curStateIndex;
	unsigned int m_maxStateCount;
};

IE_END

#endif