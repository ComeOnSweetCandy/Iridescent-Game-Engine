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
	static IEXml * Create();
	static IEXml * Create(char * key);

public:
	void SetKey(const char * key);
	void ReadXML(char * file);
	void SaveXML(char * fileName);

protected:
	void AddNone();
	void AddInt();
	void AddFloat();
	void AddString();
	void AddChild(IEXml * xml);

private:
	IEString m_key;					//��
	void * m_value;					//ֵ
	IEXmlValueType m_valueType;		//ֵ������
	//IEXmlStack * m_childs;			//���е��ӽڵ�
};

IE_END

#endif