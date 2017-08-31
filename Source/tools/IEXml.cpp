#define __IE_DLL_EXPORTS__
#include "IEXml.h"

#include "../core/container/IEcontianer.h"
#include "../core/container/IEdictionary.h"

#include "../tools/IEtime.h"

IE_BEGIN

IEXml::IEXml()
{
	m_value = NULL;
	m_valueType = __XML_value_none__;
}

IEXml::~IEXml()
{
	ClearSelf();
}

void IEXml::Initialization()
{

}

void IEXml::Initialization(const char * fileName)
{
	IEXml::ReadXML(fileName);
}

IEXml * IEXml::Create()
{
	IEXml * xml = new IEXml();
	xml->Initialization();
	return xml;
}

IEXml * IEXml::Create(const char * fileName)
{
	IEXml * xml = new IEXml();
	xml->Initialization(fileName);
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
		if (endElement->_XML->m_key == key)
		{
			arrays->Push(endElement->_XML);
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
		if (endElement->_XML->m_key == key)
		{
			return endElement->_XML;
		}
		endElement = endElement->_Next;
	}

	return NULL;
}

IEXml * IEXml::FindChild(const char * key, unsigned int index)
{
	IEXmlStack * endElement = (IEXmlStack *)m_value;
	while (endElement)
	{
		if (endElement->_XML->m_key == key)
		{
			if (index == 0)
			{
				return endElement->_XML;
			}
			else
			{
				index--;
			}
		}
		endElement = endElement->_Next;
	}

	return NULL;
}

int IEXml::ValueInt()
{
	IEString * valueString = (IEString *)m_value;
	return valueString->transToInt();
}

float IEXml::ValueFloat()
{
	IEString * valueString = (IEString *)m_value;
	return valueString->transToFloat();
}

const char * IEXml::ValueString()
{
	return ((IEString *)m_value)->GetString();
}

void IEXml::ReadXML(const char * fileName)
{
	IEString * baseDir = (IEString *)(SETTING["xmlDir"]);
	IEString fileDir = *baseDir + fileName;

	//���ļ�
	FILE * fp = fopen(fileDir.GetString(), "r");
	if (fp == NULL)
	{
		return;
	}

	IEString content;
	char hrContent[1024];

	//���ȶ�ȡ�������е��ַ���
	while (!feof(fp))
	{
		fscanf(fp, "%s", hrContent);
		content<<hrContent;
	}

	IEContainer * arrays = content.SplitBy('<', '>');

	//����һ����ʱջ
	IEXmlStack * stackTop = new IEXmlStack();
	stackTop->_Next = NULL;

	//���Ƚ���ǰ��xml������ջ��
	stackTop->_XML = this;
	stackTop->_XML->m_key = ((IEString *)(arrays->Find(0)))->GetString();

	for (int index = 1; index < arrays->Count(); index++)
	{
		IEString * string = (IEString *)(arrays->Find(index));
		const char * strs = string->GetString();

		if (strs[0] == '/')			//�պϱ�ǩ
		{
			//���ȼ������ջ��ֱ���ҵ���ñպϱ�ǩ��Ӧ��ʵ�� �����Ͽ϶���ջ��
			IEXmlStack * deleted = stackTop;
			stackTop = stackTop->_Next;

			deleted->_Next = NULL;
			delete deleted;
		}
		else if (strs[0] == '|')	//���ݶ�
		{
			IEXml * xml = stackTop->_XML;
			IEString * value = IEString::Create(string->GetString() + 1);
			
			xml->m_value = value;
			xml->m_valueType = __XML_value_string__;
		}
		else						//��ʼ����
		{
			//���ȴ���һ��
			IEXml * xml = IEXml::Create();

			//������ջ����Ԫ�����child
			stackTop->_XML->AddChild(xml);

			//���½�����xml������ջ��
			IEXmlStack * newStack = new IEXmlStack();
			newStack->_Next = stackTop;
			newStack->_XML = xml;
			newStack->_XML->m_key = strs;
			stackTop = newStack;
		}
	}

	fclose(fp);
}

void IEXml::SaveXML(const char * fileName)
{

}

void IEXml::AddChild(IEXml * xml)
{
	xml->Retain();

	if (m_value == NULL)
	{
		m_valueType = __XML_value_XML__;

		IEXmlStack * m_childs = new IEXmlStack();
		m_childs->_XML = xml;
		m_childs->_Next = NULL;
		m_value = m_childs;
	}
	else
	{
		IEXmlStack * newElement = new IEXmlStack();
		newElement->_Next = NULL;
		newElement->_XML = xml;

		IEXmlStack * endElement = (IEXmlStack *)m_value;
		while (endElement->_Next)
		{
			endElement = endElement->_Next;
		}
		endElement->_Next = newElement;
	}
}

void IEXml::ClearSelf()
{
	if (m_valueType == __XML_value_XML__)
	{
		IEXmlStack * nextElement = (IEXmlStack *)m_value;
		IEXmlStack * deletedElement;

		while (nextElement)
		{
			if (nextElement->_XML)
			{
				deletedElement = nextElement;
				nextElement = nextElement->_Next;

				deletedElement->_XML->Release();
				delete deletedElement;
				deletedElement = NULL;
			}
		}
	}
	else if (m_valueType == __XML_value_string__)
	{
		IEString * deletedString = (IEString *)m_value;
		deletedString->ReleaseDisreference();
	}
	else
	{
		//__IE_WARNING__("IEXml : ClearSelf() : error.\n");
	}

	m_value = NULL;
}

void WriteToXml(FILE * file, const char * content)
{
	static int level = 0;

	if (*(content + 1) == '/')
	{
		level--;
	}
	for (int index = 0; index < level; index++)
	{
		fprintf(file, "\t");
	}

	fprintf(file, content);

	if (*(content + 1) != '/')
	{
		level++;

		//����Ƿ��п��Ϻͱպ�
		IEString str(content);
		int count = str.DetectedChar('<');
		if (count == 2)
		{
			level--;
		}
	}

	fprintf(file, "\n");
}

IE_END