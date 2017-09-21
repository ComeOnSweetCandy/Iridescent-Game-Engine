/***********************************
* name     : IEProp.h
* creater  : cosc
* info     : every prop in scene
* date     : 2017/3/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PROP__
#define __IE_PROP__

#include "../IEAtom.h"

IE_BEGIN

/*
** �ڳ����е�prop�Ļ��ƺ��ڱ����еĻ����ǲ�ͬ�� ��Ҫ��������
*/

typedef enum IEPropState
{
	__prop_state_pick__,		//�����е� ����ʰȡ��prop
	__prop_state_pack__,		//�����е� ����ʹ�õ�prop
	__prop_state_max__
};

typedef enum IEPropType
{
	__prop_type_weapon__,		//������prop
	__prop_type_task__,			//������prop
	__prop_type_material__,		//������prop
	__prop_type_consumable__,	//������prop
	__prop_type_max__
};

class IECreature;

class __IE_DLL__ IEProp :public IEAtom
{
public:
	IEProp();
	virtual ~IEProp();
	virtual void Initialization(unsigned int propID, IEPropState propState);
	static IEProp * Create(unsigned int propID, IEPropState propState);

public:
	virtual void EquipProp() = 0;						//װ��prop
	virtual void UseProp() = 0;							//ʹ��prop
	virtual void PickProp(IECreature * creature) = 0;	//ʰȡprop

	void SetPropType(IEPropType propType);				//��ȡ��������
	void SetPropState(IEPropState propState);			//��ȡ����״̬
	void SetOwner(IECreature * creature);					//�趨������
	void SetPropID(unsigned int propID);					//�趨prop��ID
	unsigned int AddPropCount(unsigned int propCount);		//����prop������ ����ֵΪ ��û�зŽ�ȥ���� (�ܷ�����پͷ������)
	unsigned int AddPropCount(IEProp * prop);				//�����µ�prop
	unsigned int ReducePropCount(unsigned int count);		//����prop������ ����ֵΪ ����Ҫ��prop������ ˵���������� (����������Ѿ��еĲ��ᱻ����)
	void DelPropAll();										//�������е�Prop

	IECreature * GetOwner();				//��ȡ������
	IEPropType GetPropType();				//��ȡ��������
	IEPropState GetPropState();				//��ȡ����״̬
	int GetPropID();						//��ȡprop��ID
	unsigned int GetPropCount();			//�õ�prop������

protected:
	virtual void ArrangeInfo();				//ÿ�ε��ú� ������

	virtual void DrawNodeInScene(){};			//���Ƴ����е�prop
	virtual void DrawNodeInPack(){};			//����pack�е�prop

private:
	void InitUnit();						//��ʼ������

	void AddSelf();							//���볡����
	void DelSelf();							//�ӳ�������ɾ����ȥ

protected:
	IEPropState m_propState;				//��ǰ״̬
	IEPropType m_propType;					//����
	IECreature * m_owner;					//������

	unsigned int m_propID;					//ID
	unsigned int m_unitID;					//unit ID
	unsigned int m_pileMax;					//�ѵ����� ����ֵΪ1��ʱ�� �����ɶѵ�
	unsigned int m_propCount;				//��ǰ�ѵ�����
};

IE_END

#endif