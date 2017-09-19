/***********************************
* name     : IEtrigger.h
* creater  : cosc
* info     : ���������������� ÿ��һ���������� �ᷴ������Ӧ�Ľڵ�
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

typedef void(IEAtom::*IETrggerStrike)(IEPhysicNode * physicNode);			//�����������˵����

enum IETriggerType
{
	__trigger_warn_type__,			//�������� ��һ����Χ�ھͻᴥ��
	__trigger_collision_type__,		//��ײ���� ��ײ�˾ͻᴥ��
	__trigger_interaction_type__,	//�������� 
	__trigger_type_count__			//����
};

class __IE_DLL__ IETrigger:public IEPhysicNode
{
public:
	IETrigger();
	virtual ~IETrigger();
	virtual void Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);
	static IETrigger * Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);

public:
	IETriggerType GetTriggerType();									//��ȡ����������
	void SetAllowStrikeRepeat(bool allowStrikeRepeat);				//�趨�Ƿ������ظ�����
	void SetAllowStrikeRepeatByOne(bool allowStrikeRepeatByOne);	//�趨�Ƿ�����ͬһ�������ظ�����

	void ActivateTrigger(IEAtom * self, IETrggerStrike function);		//�趨һ���µ�trigger �󶨵�һ��atom�� ���Ұ�����������

protected:
	virtual void RunTrigger();										//����trigger
	virtual void Collision(IEPhysicNode * physicNode);				//������ײ
	virtual void TriggerStrike(IEPhysicNode * physicNode);			//�����ж�����������

protected:
	IETriggerType m_triggerType;			//������������
	IEAtom * m_attachAtom;					//������������atom
	IETrggerStrike m_function;				//������������ķ���

	bool m_allowStrikeRepeat;				//�Ƿ�����ڵ��ظ�����
	bool m_allowStrikeRepeatByOne;			//�Ƿ�����ڵ㱻ͬһ�������ظ�����

	IEContainer * m_strikeNodes;			//�Ѿ��������������Ľڵ�
};

IE_END

#endif