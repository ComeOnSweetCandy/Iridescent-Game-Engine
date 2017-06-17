#define __IE_DLL_EXPORTS__
#include "IEstring.h"

#include "../core/container/IEcontianer.h"

IE_BEGIN

IEString::IEString()
{
	m_string = new char[1];
	m_string[0] = '\0';
}

IEString::IEString(const IEString &str)
{
	unsigned int strSize = str.Length() + 1;
	m_string = new char[strSize];
	strcpy(m_string, str.GetString());
}

IEString::IEString(const char &c)
{
	unsigned int strSize = 1 + 1;
	m_string = new char[strSize];
	m_string[0] = c;
	m_string[1] = '\0';
}

IEString::IEString(const char * str)
{
	unsigned int strSize = strlen(str) + 1;
	m_string = new char[strSize];
	strcpy(m_string, str);
}

IEString::IEString(const int &i)
{
	char str[12];
	sprintf(str, "%d", i);
	unsigned int strSize = strlen(str) + 1;
	m_string = new char[strSize];
	strcpy(m_string, str);
}

IEString::~IEString()
{
	this->EmptyString();
}

void IEString::EmptyString()
{
	if (m_string)
	{
		delete[] m_string;
	}
	m_string = NULL;
}

IEString * IEString::Create()
{
	IEString * newObject = new IEString();
	return newObject;
}

IEString * IEString::Create(const char &c)
{
	IEString * newObject = new IEString(c);
	return newObject;
}

IEString * IEString::Create(const char *str)
{
	IEString * newObject = new IEString(str);
	return newObject;
}

unsigned int IEString::Length() const
{
	return unsigned int(strlen(this->m_string));
}

unsigned int IEString::Size() const
{
	return unsigned int(strlen(this->m_string) + 1);
}

IEString IEString::operator +(const IEString &str) const
{
	unsigned int length_1 = this->Length();
	unsigned int length_2 = str.Length();
	unsigned int size = length_1 + length_2 + 1;
	
	char * newStr = new char[size];
	strcpy(newStr, this->m_string);
	strcat(newStr, str.GetString());

	IEString newString = IEString(newStr);
	delete [] newStr;

	return newString;
}

IEString IEString::operator +(const char *str) const
{
	unsigned int length_1 = this->Length();
	unsigned int length_2 = strlen(str);
	unsigned int size = length_1 + length_2 + 1;

	char * newStr = new char[size];
	strcpy(newStr, this->m_string);
	strcat(newStr, str);

	IEString newString = IEString(newStr);
	delete[] newStr;

	return newString;
}

IEString IEString::operator +(const char &str) const
{
	unsigned int length_1 = this->Length();
	unsigned int length_2 = 1;
	unsigned int size = length_1 + length_2 + 1;

	char * newStr = new char[size];
	strcpy(newStr, this->m_string);
	newStr[length_1] = str;
	newStr[length_1 + 1] = '\0';

	IEString newString = IEString(newStr);
	delete[] newStr;

	return newString;
}

IEString IEString::operator +(const int &i) const
{
	IEString addString = "";
	int n = i;
	if (n < 0)
	{
		n = -n;
	}

	int c2, c1;
	char c0 = i - 1 + '1';
	while (n>=10)
	{
		c2 = n / 10;
		c1 = n % 10;
		c0 = c1 - 1 + '1';
		addString = addString + c0;
	}
	addString = addString + c0;
	if (i < 0)
	{
		addString = addString + '-';
	}
	addString.OverthrowString();
	IEString newString = IEString(m_string) + addString;
	return newString;
}

void IEString::operator =(const IEString &str)
{
	this->EmptyString();

	unsigned int strSize = str.Length() + 1;
	m_string = new char[strSize];
	strcpy(m_string, str.GetString());
}

void IEString::operator =(const char * string)
{
	if (string)
	{
		this->EmptyString();

		unsigned int strSize = strlen(string) + 1;
		m_string = new char[strSize];
		strcpy(m_string, string);
	}
}

void IEString::operator = (const char &c)
{
	this->EmptyString();

	unsigned int strSize = 2;
	m_string = new char[strSize];
	m_string[0] = 'c';
	m_string[1] = '\0';
}

bool IEString::operator ==(const IEString &str)
{
	return !(strcmp(GetString(), str.GetString()));
}

bool IEString::operator ==(const char *str)
{
	return !(strcmp(GetString(), str));
}

void IEString::operator +=(const IEString &str)
{
	
}

void IEString::operator +=(const char *str)
{

}

void IEString::operator +=(const char &c)
{

}

char & IEString::operator[](unsigned short int index)
{
	return m_string[index];
}

const char * IEString::GetString() const
{
	return m_string;
}

IEContainer * IEString::SplitBy(char c, int &splitCount)
{
	unsigned int stringLength = this->Length();
	if (m_string[stringLength - 1] == c)
	{
		stringLength = stringLength - 1;
	}
	if (stringLength == 0)
	{
		return NULL;
	}

	splitCount = 1;
	bool isLastCharSpace = true;
	for (unsigned int index = 0; index < stringLength; index++)
	{
		if (this->m_string[index] == c)
		{
			if (isLastCharSpace == false)
			{
				splitCount++;
			}
			isLastCharSpace = true;
		}
		else
		{
			isLastCharSpace = false;
		}
	}

	IEString ** splitString = new IEString*[splitCount];
	IEContainer * stringArray = IEContainer::Create();
	for (int index = 0; index < splitCount; index++)
	{
		splitString[index] = IEString::Create();
		stringArray->Push(splitString[index]);
	}
	stringArray->AutoRelease();

	for (unsigned int index = 0, splitOrder = 0, isLastCharSpace = true; index < stringLength; index++)
	{
		if (this->m_string[index] == c)
		{
			if (isLastCharSpace == false)
			{
				splitOrder++;
			}
			isLastCharSpace = true;
		}
		else
		{
			*splitString[splitOrder] = *splitString[splitOrder] + m_string[index];
			isLastCharSpace = false;
		}
	}

	delete[] splitString;
	return stringArray;
}

IEContainer * IEString::SplitBy(char beginC, char endC, int &splitCount)
{
	int length = this->Length();
	if (length < 2)
	{
		//不正确的格式
		return NULL;
	}
	//if (m_string[0] != beginC || m_string[length - 1] != endC)
	//{
	//	//不正确的格式
	//	return NULL;
	//}

	//检查嵌套和是否数量匹配
	int mark = 0;
	for (int index = 0; index < length; index++)
	{
		//检查嵌套

		if (m_string[index] == beginC)
		{
			mark++;
		}
		else if (m_string[index] == endC)
		{
			mark--;
		}
		if (mark != 0 && mark != 1)
		{
			//嵌套错误 格式不正确
			return NULL;
		}
	}

	if (mark != 0)
	{
		//数量不匹配 格式不正确
		return NULL;
	}

	IEContainer * labelsArray = IEContainer::Create();
	labelsArray->AutoRelease();
	IEString * label = NULL;
	for (int index = 0; index < length; index++)
	{
		//检查嵌套

		if (m_string[index] == beginC)
		{
			label = IEString::Create();
		}
		else if (m_string[index] == endC)
		{
			labelsArray->Push(label);
			label = NULL;
		}
		else
		{
			if (label)
			{
				*label = *label + m_string[index];
			}
		}
	}

	return labelsArray;
}

void IEString::DeleteChar(char c)
{
	int length = this->Length();
	int charCount = DetectedChar(c);

	if (charCount == 0)
	{
		//没有空格 走人
		return;
	}

	char * newString = new char[length - charCount + 1];
	newString[length - charCount] = '\0';
	for (int index = 0, oldIndex = 0; index < length - charCount; index++, oldIndex++)
	{
		while (m_string[oldIndex] == c)
		{
			oldIndex++;
		}
		newString[index] = m_string[oldIndex];
	}

	delete[]m_string;
	m_string = newString;
}

void IEString::OverthrowString()
{
	int length = this->Length();
	if (length == 1)
	{
		return;
	}
	else
	{
		int begin = 0;
		int end = length - 1;
		while(begin < end)
		{
			char c;
			c = m_string[begin];
			m_string[begin] = m_string[end];
			m_string[end] = c;

			begin++;
			end--;
		}
	}
}

IEString IEString::GetFileNameBody()
{
	unsigned int stringLength = this->Length();
	if (stringLength < 3)
	{
		return "this is not a illegal file name";
	}

	unsigned int splitCount = 1;
	for (unsigned int index = 0; index < stringLength; index++)
	{
		if (this->m_string[index] == '.')
		{
			splitCount++;
		}
	}

	if (splitCount <= 1)
	{
		return "this is not a illegal file name";
	}

	IEString body = "";
	for (unsigned int index = 0, splitOrder = 0; index < stringLength; index++)
	{
		if (this->m_string[index] == '.')
		{
			splitOrder++;
			if (splitOrder + 1 == splitCount)
			{
				return body;
			}
			body = body + m_string[index];
		}
		else
		{
			body = body + m_string[index];
		}
	}

	return "error";
}

IEString IEString::GetFileNameExtensions()
{
	unsigned int stringLength = this->Length();
	if (stringLength < 3)
	{
		return "this is not a illegal file name";
	}

	unsigned int splitCount = 1;
	for (unsigned int index = 0; index < stringLength; index++)
	{
		if (this->m_string[index] == '.')
		{
			splitCount++;
		}
	}

	if (splitCount <= 1)
	{
		return "this is not a illegal file name";
	}

	IEString extensions = "";
	for (unsigned int index = 0, splitOrder = 0; index < stringLength; index++)
	{
		if (this->m_string[index] == '.')
		{
			splitOrder++;
		}
		else
		{
			if (splitOrder + 1 == splitCount)
			{
				extensions = extensions + m_string[index];
			}
		}
	}
	return extensions;
}

bool IEString::isNote()
{
	int count = this->Length();
	if (count < 2)
	{
		return false;
	}

	if (m_string[0] == '[' && m_string[count] == ']')
	{
		return true;
	}
	return false;
}

int IEString::DetectedChar(char c)
{
	int length = this->Length();
	int charCount = 0;

	for (int index = 0; index < length; index++)
	{
		if (m_string[index] == c)
		{
			charCount++;
		}
	}

	return charCount;
}

void IEString::LowerChar()
{
	int length = this->Length();
	for (int index = 0; index < length; index++)
	{
		if (m_string[index] >= 'A' && m_string[index] <= 'Z')
		{
			m_string[index] = m_string[index] + 32;
		}
	}
}

int IEString::DetectedType()
{
	int type = STRING_TO_INT;
	int length = this->Length();
	for (int index = 0; index < length; index++)
	{
		if (m_string[index] >= '0' && m_string[index] <= '9')
		{
			if (type < STRING_TO_INT)
			{
				type = STRING_TO_INT;
			}
		}
		else if (m_string[index] == '.')
		{
			if (type < STRING_TO_FLOAT)
			{
				type = STRING_TO_FLOAT;
			}
		}
		else
		{
			if (type < STRING_TO_STRING)
			{
				type = STRING_TO_STRING;
			}

		}
	}

	return type;
}

int IEString::transToInt()
{
	int length = this->Length();
	int res = 0;
	bool minus = false;

	for (int index = 0; index < length; index++)
	{
		if (m_string[index] == '-')
		{
			minus = true;
		}
		else if (m_string[index] >= '0' && m_string[index] <= '9')
		{
			int number = m_string[index] - '0';
			res = res * 10 + number;
		}
		else
		{
			__IE_WARNING__("IEString : error. transtoint.\n");
		}
	}

	if (minus)
	{
		res = -res;
	}
	return res;
}

float IEString::transToFloat()
{
	int length = this->Length();

	int spliteCount = 0;
	IEArray * spliteArray = SplitBy('.', spliteCount);
	if (spliteCount != 2)
	{
		__IE_WARNING__("IEString : error. transToFloat.\n");
	}

	IEString ** strs = (IEString **)(spliteArray->GetContainer());
	float part1 = float(strs[0]->transToInt());
	float part2 = float(strs[1]->transToInt());

	int part2length = strs[1]->Length();
	for (int index = 0; index < part2length; index++)
	{
		part2 = part2 / 10;
	}
	return part1 + part2;
}

float IEString::transFromPercentToFloat()
{
	IEString str = m_string;
	int index = str.FindCharFromIndex('%', 0, 1);
	if (index != -1)
	{
		str.DeleteChar('%');
		int number = str.transToInt();
		return (float)number / 100.0f;
	}
	else
	{
		index = str.FindCharFromIndex('.', 0, 1);
		if (index != -1)
		{
			float number = str.transToFloat();
			return number;
		}
		else
		{
			int number = str.transToInt();
			return (float)number / 100.0f;
		}
	}
}

int IEString::PushSeveralChar(char c)
{
	int length = this->Length();
	int index = 0;
	while (m_string[index] == c)
	{
		index++;
	}
	int markIndex = index;

	char * newString = new char[length - index + 1];
	newString[length - index] = '\0';
	int newIndex = 0;

	for (index; index < length; index++)
	{
		newString[newIndex++] = m_string[index];
	}

	delete[]m_string;
	m_string = newString;
	return markIndex;
}

IEString * IEString::SubString(int beginIndex, int deleteLength)
{
	int length = this->Length();
	IEString * subString = IEString::Create();
	subString->AutoRelease();
	char * newString = new char[length - deleteLength + 1];
	newString[length - deleteLength] = '\0';

	for (int index = 0, newIndex = 0; index < length; index++)
	{
		if (index >= beginIndex)
		{
			if (deleteLength)
			{
				*subString = *subString + m_string[index];
				deleteLength--;

				continue;
			}
		}
		newString[newIndex++] = m_string[index];
	}

	delete[]m_string;
	m_string = newString;
	return subString;
}

int IEString::DeleteString(char * string, int deleteCount)
{
	int length = this->Length();
	int strLength = strlen(string);
	int deletedCount = 0;

	for (int index = 0, delStringIndex = 0, startIndex = 0; index < (int)(this->Length()); index++, startIndex++)
	{
		while (m_string[index] == string[delStringIndex])
		{
			index++;
			delStringIndex++;

			if (delStringIndex >= strLength)
			{
				deletedCount++;
				index = 0;
				SubString(startIndex, delStringIndex);

				if (deleteCount != 0 && deletedCount == deleteCount)
				{
					return deletedCount;
				}

				break;
			}
		}
		delStringIndex = 0;
	}

	return deletedCount;
}

int IEString::FindCharFromIndex(char c, int beginIndex, int findIndex)
{
	int length = this->Length();
	int findedIndex = 0;
	for (int index = beginIndex; index < length; index++)
	{
		if (m_string[index] == c)
		{
			findedIndex++;

			if (findedIndex == findIndex)
			{
				return index;
			}
		}
	}

	return -1;
}

int IEString::FindString(char * string, int findIndex)
{
	if (findIndex < 1)
	{
		//不能够小于1
		return -1;
	}

	int length = this->Length();
	int strLength = strlen(string);
	int deletedCount = 0;

	for (int index = 0, delStringIndex = 0, startIndex = 0; index < (int)(this->Length()); index++, startIndex++)
	{
		while (m_string[index] == string[delStringIndex])
		{
			index++;
			delStringIndex++;

			if (delStringIndex >= strLength)
			{
				deletedCount++;

				if (deletedCount == findIndex)
				{
					return startIndex;
				}

				break;
			}
		}
		delStringIndex = 0;
	}

	return -1;
}

IE_END