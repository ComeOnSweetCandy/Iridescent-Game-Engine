/***********************************
* name     : IEXml.h
* creater  : cosc
* info     : xml reader
* date     : 2017/07/06
* version  : 1.0
* remark   : 首先明确，任何一个节点都可以单独出来成为一个xml类 有点类似于domer的方式
             XML格式能保存相当多的信息
************************************/

#ifndef __IE_XML__
#define __IE_XML__

#include "../core/IEobject.h"
#include "../type/IEstring.h"

IE_BEGIN

typedef enum __ieXmlValueType
{
	__xml_value_none__,			//值为空
	__xml_value_int__,			//值为整形
	__xml_value_float__,		//值为浮点数
	__xml_value_string__,		//值为字符串
	__xml_value_xml__			//值为xml
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
	IEString m_key;					//键
	void * m_value;					//值
	IEXmlValueType m_valueType;		//值的类型
};

void WriteToXml(FILE * file, const char * content);

IE_END

#endif