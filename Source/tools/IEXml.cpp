#define __IE_DLL_EXPORTS__
#include "IEXml.h"

#include "../core/container/IEcontianer.h"

#include "../tools/IEtime.h"

IE_BEGIN

IEXml::IEXml()
{
	m_value = NULL;
	m_valueType = __xml_value_none__;
}

IEXml::~IEXml()
{

}

void IEXml::Initialization()
{

}

IEXml * IEXml::Create()
{
	IEXml * xml = new IEXml();
	xml->Initialization();
	return xml;
}

IEContainer * IEXml::FindChilds(const char * key)
{
	IEContainer * arrays = IEContainer::Create();
	arrays->AutoRelease();

	IEXmlStack * endElement = (IEXmlStack *)m_value;
	IEXml * resultXml = NULL;
	while (endElement)
	{
		if (endElement->_Xml->m_key == key)
		{
			arrays->Push(endElement->_Xml);
		}
		endElement = endElement->_Next;
	}

	return arrays;
}

IEXml * IEXml::FindChild(const char * key)
{
	IEXmlStack * endElement = (IEXmlStack *)m_value;
	while (endElement)
	{
		if (endElement->_Xml->m_key == key)
		{
			return endElement->_Xml;
		}
		endElement = endElement->_Next;
	}

	return NULL;
}

int IEXml::ValueInt()
{
	return *((int *)m_value);
}

float IEXml::ValueFloat()
{
	return *((float *)m_value);
}

const char * IEXml::ValueString()
{
	return ((IEString *)m_value)->GetString();
}

void IEXml::ReadXML(char * file)
{
	//打开文件
	FILE * fp = fopen(file, "r");
	IEString content;
	char hrContent[256];

	//首先读取进入所有的字符串
	while (!feof(fp))
	{
		fscanf(fp, "%s", hrContent);
		content<<hrContent;
	}

	IEContainer * arrays = content.SplitBy('<', '>');

	//建立一个临时栈
	IEXmlStack * stackTop = new IEXmlStack();
	stackTop->_Next = NULL;

	//首先将当前的xml放置入栈顶
	stackTop->_Xml = this;
	stackTop->_Xml->m_key = ((IEString *)(arrays->Find(0)))->GetString();

	for (int index = 1; index < arrays->Count() - 1; index++)
	{
		IEString * string = (IEString *)(arrays->Find(index));
		const char * strs = string->GetString();

		if (strs[0] == '/')			//闭合标签
		{
			//首先检测整个栈，直接找到与该闭合标签对应的实例 理论上肯定在栈顶
			IEXmlStack * deleted = stackTop;
			stackTop = stackTop->_Next;

			deleted->_Next = NULL;
			delete deleted;
		}
		else if (strs[0] == '|')	//数据段
		{
			IEXml * xml = stackTop->_Xml;

			string->DeleteChar('|');
			int result = string->DetectedType();
			switch (result)
			{
			case STRING_TO_NONE:
				xml->AddNone();
				break;
			case STRING_TO_INT:
				xml->AddInt(string->transToInt());
				break;
			case STRING_TO_FLOAT:
				xml->AddFloat(string->transToFloat());
				break;
			case STRING_TO_STRING:
				xml->AddString(string->GetString());
				break;
			}
		}
		else						//开始区间
		{
			//首先创建一个
			IEXml * xml = IEXml::Create();

			//首先往栈顶的元素添加child
			stackTop->_Xml->AddChild(xml);

			//将新建立的xml放置在栈顶
			IEXmlStack * newStack = new IEXmlStack();
			newStack->_Next = stackTop;
			newStack->_Xml = xml;
			newStack->_Xml->m_key = strs;
			stackTop = newStack;
		}
	}
}

void IEXml::SaveXML(char * fileName)
{

}

void IEXml::AddNone()
{
	m_valueType = __xml_value_none__;
	m_value = NULL;
}

void IEXml::AddInt(int value)
{
	m_valueType = __xml_value_int__;
	m_value = new int(value);
}

void IEXml::AddFloat(float value)
{
	m_valueType = __xml_value_float__;
	m_value = new float(value);
}

void IEXml::AddString(const char * value)
{
	m_valueType = __xml_value_string__;
	m_value = IEString::Create(value);
}

void IEXml::AddChild(IEXml * xml)
{
	if (m_value == NULL)
	{
		m_valueType = __xml_value_xml__;

		IEXmlStack * m_childs = new IEXmlStack();
		m_childs->_Xml = xml;
		m_childs->_Next = NULL;
		m_value = m_childs;
	}
	else
	{
		IEXmlStack * newElement = new IEXmlStack();
		newElement->_Next = NULL;
		newElement->_Xml = xml;

		IEXmlStack * endElement = (IEXmlStack *)m_value;
		while (endElement->_Next)
		{
			endElement = endElement->_Next;
		}
		endElement->_Next = newElement;
	}
}

IE_END