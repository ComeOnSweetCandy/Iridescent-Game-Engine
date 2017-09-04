/***********************************
* name     : IEThingList.h
* creater  : cosc
* info     : thing list
* date     : 2017/4/4
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING_LIST__
#define __IE_THING_LIST__

#include "../../../global/IEstdafx.h"
#include "../../../tools/IEXml.h"

IE_BEGIN

typedef struct
{
	unsigned int _ThingID;
	unsigned char _X;
	unsigned char _Y;
	unsigned short _Mask;				//16λ �������4*4�ķ���
}IEAdorningOccupyInfo;

typedef struct _ieThingEntry
{
	_ieThingEntry()
	{
		_ThingID = 0;
		_OccupyCount = 0;
		_OccupyInfo = NULL;
		_LUA = NULL;
		_XML = NULL;
	};
	~_ieThingEntry()
	{ 
		__IE_LUA_RELEASE__(_LUA);
		__IE_RELEASE_DIF__(_XML);
	};

	//ÿ��thing����Ψһ��ID �Լ���ʾthing������
	unsigned int _ThingID;
	char _ThingName[64];

	//������ϵͳ����ռ�ݵ���������
	unsigned short _OccupyCount;
	IEAdorningOccupyInfo * _OccupyInfo;

	//�ű���XML
	lua_State * _LUA;
	IEXml * _XML;
}IEThingEntry;

class IEThingList
{
public:
	IEThingList();
	virtual ~IEThingList();
	virtual void Initialization();
	virtual void Release();
	static IEThingList * Share();

public:
	IEThingEntry * GetEntrys();
	unsigned int GetEntrysCount();

	void AddEntry(const char * thingName);
	void DelEntry(const char * thingName);
	void DelEntry(unsigned int tingID);

	void LoadList();
	void SaveList();

private:
	static IEThingList * m_stateList;

	IEThingEntry * m_entrys;
	unsigned int m_entrysCount;
};

IE_END

#endif