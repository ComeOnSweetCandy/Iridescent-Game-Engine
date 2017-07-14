/***********************************
* name     : IEXml.h
* creater  : cosc
* info     : xml reader
* date     : 2017/07/06
* version  : 1.0
* remark   : ������ȷ���κ�һ���ڵ㶼���Ե���������Ϊһ��xml�� �е�������domer�ķ�ʽ
             XML��ʽ�ܱ����൱�����Ϣ
************************************/

#ifndef __IE_XML__
#define __IE_XML__

#include "../core/IEobject.h"
#include "../type/IEstring.h"

IE_BEGIN

typedef enum __ieXmlValueType
{
	__xml_value_none__,			//ֵΪ��
	__xml_value_int__,			//ֵΪ����
	__xml_value_float__,		//ֵΪ������
	__xml_value_string__,		//ֵΪ�ַ���
	__xml_value_xml__			//ֵΪxml
}IEXmlValueType;

class IEXml;

typedef struct __ieXmlStack
{
	IEXml * _Xml;
	struct __ieXmlStack * _Next;
}IEXmlStack;

class __IE_DLL__ IEXml:public IEObject
{
public:
	IEXml();
	~IEXml();
	void Initialization();
	void Initialization(const char * fileName);
	static IEXml * Create();
	static IEXml * Create(const char * fileName);

public:
	void ReadXML(const char * fileName);
	void SaveXML(const char * fileName);

	int ValueInt();
	float ValueFloat();
	const char * ValueString();
	IEXml * FindChild(const char * key);
	IEContainer * FindChilds(const char * key);

protected:
	void AddChild(IEXml * xml);

private:
	void ClearSelf();

private:
	IEString m_key;					//��
	void * m_value;					//ֵ
	IEXmlValueType m_valueType;		//ֵ������
};

void WriteToXml(FILE * file, const char * content);

IE_END

#endif