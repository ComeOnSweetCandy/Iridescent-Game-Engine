#define __IE_DLL_EXPORTS__
#include "IEXml.h"

#include "../core/container/IEcontianer.h"

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

void IEXml::ReadXML(char * file)
{
	//���ļ�
	FILE * fp = fopen(file, "r");
	IEString content;
	char hrContent[256];

	//���ȶ�ȡ�������е��ַ���
	while (!feof(fp))
	{
		fscanf(fp, "%s", hrContent);
		content = content + hrContent;
	}

	int count = 0;
	IEContainer * arrays = content.SplitBy('<', '>', count);
	count = arrays->Count();

	//����һ����ʱջ
	IEXmlStack * stackTop = new IEXmlStack();
	stackTop->_Next = NULL;

	//���Ƚ���ǰ��xml������ջ��
	stackTop->_Xml = this;
	stackTop->_Xml->m_key = ((IEString *)(arrays->Find(0)))->GetString();

	for (int index = 1; index < arrays->Count() - 1; index++)
	{
		IEString * string = (IEString *)(arrays->Find(index));
		const char * strs = string->GetString();

		printf("%s\n", strs);

		if (strs[0] == '/')			//�պϱ�ǩ
		{
			//���ȼ������ջ��ֱ���ҵ���ñպϱ�ǩ��Ӧ��ʵ�� �����Ͽ϶���ջ��
			const char * strsBody = strs + 1;
			if (stackTop->_Xml->m_key == strsBody)
			{
				IEXmlStack * deleted = stackTop;
				stackTop = stackTop->_Next;

				deleted->_Next = NULL;
				delete deleted;
			}
		}
		else if (strs[0] == '|')	//���ݶ�
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
		else						//��ʼ����
		{
			//���ȴ���һ��
			IEXml * xml = IEXml::Create();

			//������ջ����Ԫ�����child
			stackTop->_Xml->AddChild(xml);

			//���½�����xml������ջ��
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
		m_childs->_Xml = this;
		m_childs->_Next = NULL;
		m_value = m_childs;
	}

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

IE_END