/***********************************
* name     : IEPropPack.h
* creater  : cosc
* info     : bag
* date     : 2017/3/31
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PROP_PACK__
#define __IE_PROP_PACK__

#include "IEProp.h"

IE_BEGIN

class IESlot;

class __IE_DLL__ IEPropPack:public IEObject
{
public:
	IEPropPack();
	virtual ~IEPropPack();
	virtual void Initialization(IEArmer * creature, unsigned int packCapacity);
	static IEPropPack * Create(IEArmer * creature, unsigned int packCapacity);

public:
	virtual void UpdateUI();								//���°󶨵�UI
	void ListProp();										//�оٱ������������Ʒ

	void AddProp(IEProp * prop);							//����prop
	void DropProp(unsigned int packIndex);					//����prop
	void DropProp(IEProp * prop);							//����prop
	void UseProp(unsigned int packIndex);					//ʹ��prop

	void ChangePropIndex(IEProp * prop1, IEProp * prop2);	//��������propλ��
	int GetPropIndex(IEProp * prop);						//��ȡprop��λ��

private:
	void SetSlot(IESlot * shortCut);					//???

	void SetPackCapacity(unsigned int packCapacity);	//�趨pack����
	void SetPackOwner(IEArmer * creature);				//�趨pack��ӵ����

	unsigned int GetPackCapacity();						//��ȡpack����
	IEArmer * GetPackOwner();							//��ȡpackӵ����

public:
	unsigned int m_packCapacity;						//pack�������
	IEProp ** m_props;									//pack�����е�prop
	IEArmer * m_owner;									//ӵ����

	IESlot * m_slot;
};

IE_END

#endif