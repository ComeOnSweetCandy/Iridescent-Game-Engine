/***********************************
* name     : IEThing.h
* creater  : cosc
* info     : base ting
* date     : 2017/3/19
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING__
#define __IE_THING__

#include "../IEBlock.h"

#include "../../trigger/IEtrigger.h"

IE_BEGIN

class __IE_DLL__ IEThing :public IEBlock
{
public:
	IEThing();
	virtual ~IEThing();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEThing * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	void SetThingType(unsigned int thingType);
	unsigned int GetThingType();
	void SetThingID(unsigned int thingID);
	unsigned int GetThingID();
	void SetOrder(unsigned int order);
	unsigned int GetOrder();
	void SetRelatedOrder(unsigned int relatedCreatedOrder);
	unsigned int GetRelatedOrder();
	void SetExpress(bool express);
	bool GetExpress();
	void SetLocations(int blockLocationX, int blockLocationY, int tinyLocationX, int tinyLocationY);	//��thing��¼������ĵ�λ�ò���
	int * GetLocations();																				//��ȡthing��λ�ò���

	virtual void SwitchStateTo(const char * stateName);													//ת��һ��״̬
	virtual void CallFinal();																			//����ȡ�������е���Ϣ�� ����һЩ��β�ļ���
	virtual void CheckAround(bool active);																//����Χ���м�� active���� ���Է��Լ�� ������ΧԪ����ʹ�µļ�� ��Ҫ��ֹ�ݹ����

private:
	void LoadXML();			//��XML�ж�ȡ������Ϣ
	void LoadLUA();			//���ؽű��ļ�

protected:
	unsigned int m_thingType;				//thing������
	unsigned int m_thingID;					//thing��ID
	unsigned int m_order;					//��thing�����
	unsigned int m_relatedOrder;			//��������������
	bool m_express;							//����ռ����λ���Ƿ��Ѿ���ȫ���
	int m_locations[4];						//��¼��thing��λ�ú�tiny��ȷλ��

	unsigned char m_maxState;				//����״ֵ̬
	unsigned char m_curState;				//��ǰ��״ֵ̬
};

IE_END

#endif