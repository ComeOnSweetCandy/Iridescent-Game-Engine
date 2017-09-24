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
	virtual void SetTranslate(const float &x, const float &y);							//�����phsyicNode

	virtual void ChangeState(const char * stateName);									//�ı����ﵱǰ��״̬
	virtual void ChangeGroup(const char * groupName, unsigned int sameIndex = 1);		//���ظ�����ͼ���¼�
	virtual void ChangeGroup(const char * groupName, unsigned int sameIndex, unsigned int playTimes, IEFunctionTexturePlayEnded playEndedFunction);	//�������Ķ�������

	void AddTrigger(IETrigger * trigger);										//���һ��������
	void AddTrigger(IETrigger * trigger, const char * functionLua);				//���һ��������
	void DelTrigger(IETriggerType type);										//ɾ��һ��������
	void TriggerStrike(IEPhysicNode * physicNode);								//����������

	lua_State * GetLuaScript();

protected:
	virtual void ArrangeInfo();			//��������ú� ��������Ĵ���

protected:
	unsigned m_triggersCount;			//����������
	IETrigger * m_triggers;				//�������������͵Ĵ�����

	lua_State * m_LUA;					//�ű��ļ�
	IEXml * m_XML;						//��Դ��Ϣ�ļ�
};

IE_END

#endif