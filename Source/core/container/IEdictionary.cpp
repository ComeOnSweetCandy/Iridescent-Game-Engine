#define __IE_DLL_EXPORTS__
#include "IEdictionary.h"

#include "../../type/IEstring.h"
#include "../../type/IEbaseType.h"
#include "IEcontianer.h"

IE_BEGIN

IEEntry::IEEntry()
{
	m_object = NULL;
	for (int index = 0; index < IE_ENTRY_WORD_COUNT; index++)
	{
		m_nextEntry[index] = NULL;
	}
}

IEEntry::~IEEntry()
{
	if (m_object)
	{
		m_object->ReleaseDisreference();
	}
}

IEDictionary::IEDictionary()
{
	m_head = NULL;
}

IEDictionary::~IEDictionary()
{
	BurnEntry(m_head);
}

void IEDictionary::Initialization()
{
	m_head = new IEEntry();
	m_curEntry = m_head;
}

IEDictionary * IEDictionary::CreateAndRetain()
{
	IEDictionary * object = new IEDictionary();
	object->Initialization();
	object->Retain();
	return object;
}

IEObject*& IEDictionary::operator[](const char * keyString)
{
	IEEntry * entry = FindEntry2(keyString);
	if (entry)
	{
		return entry->m_object;
	}
	else
	{
		entry = AddEntry(NULL, keyString);
		return entry->m_object;
	}
}

IEEntry * IEDictionary::AddEntry(IEObject * object, const char * keyString)
{
	int keyLength;
	unsigned char * converedKey = ConvertKeyString(keyString, keyLength);

	IEEntry * lastEntry = m_head;
	IEEntry * curEntry = m_head;
	for (int index = 0; index < keyLength; index++)
	{
		unsigned char c = converedKey[index];

		if (curEntry)
		{
			lastEntry = curEntry;
			curEntry = curEntry->m_nextEntry[c];
		}
		else
		{
			int lastC = converedKey[index - 1];

			curEntry = new IEEntry();
			lastEntry->m_nextEntry[lastC] = curEntry;

			lastEntry = curEntry;
			curEntry = curEntry->m_nextEntry[c];
		}
	}
	
	if (curEntry && curEntry->m_object)
	{
		__IE_WARNING__("IEDictionary : error . the entry have been exist.\n");
	}
	else
	{
		int lastC = converedKey[keyLength - 1];

		curEntry = new IEEntry();
		curEntry->m_object = object;
		lastEntry->m_nextEntry[lastC] = curEntry;
	}

	delete[]converedKey;
	return curEntry;
}

IEEntry * IEDictionary::FindEntry2(const char * keyString)
{
	int keyLength = strlen(keyString);

	IEEntry * curEntry = m_head;
	unsigned char c;

	for (int index = 0; index < keyLength; index++)
	{
		c = keyString[index];
		//ConvertKeyChar(c);

		if (c >= 'a' && c <= 'z')
		{
			c = c - 'a';
		}
		else if (c >= 'A' && c <= 'Z')
		{
			c = c + 32 - 'a';
		}
		else if (c == '.')
		{
			c = 26;
		}
		else if (c == '/')
		{
			c = 27;
		}
		else if (c == '_')
		{
			c = 28;
		}
		else if (c >= '0' && c <= '9')
		{
			c = 29 + c - '0';
		}
		else
		{
			__IE_WARNING__("IEDictionary : error.\n");
		}

		if (curEntry)
		{
			curEntry = curEntry->m_nextEntry[c];
		}
		else
		{
			return NULL;
		}
	}

	return curEntry;
}

IEEntry * IEDictionary::FindEntry(const char * keyString)
{
	int keyLength;
	unsigned char * converedKey = ConvertKeyString(keyString, keyLength);

	IEEntry * lastEntry = m_head;
	IEEntry * curEntry = m_head;
	for (int index = 0; index < keyLength; index++)
	{
		unsigned char c = converedKey[index];

		if (curEntry)
		{
			lastEntry = curEntry;
			curEntry = curEntry->m_nextEntry[c];
		}
		else
		{
			delete[]converedKey;
			return NULL;
		}
	}

	delete[]converedKey;
	return curEntry;
}

void IEDictionary::InsertKeyString(const char * string)
{
	int keyLength = strlen(string);
	unsigned char c;

	for (int index = 0; index < keyLength; index++)
	{
		c = string[index];
		ConvertKeyChar(c);

		if (m_curEntry)
		{
			m_curEntry = m_curEntry->m_nextEntry[c];
		}
	}
}

void IEDictionary::InsertKeyStrings(char ** string, unsigned int count)
{
	m_curEntry = m_head;
	int keyLength;
	unsigned char c;

	for (unsigned int index = 0; index < count; index++)
	{
		keyLength = strlen(string[index]);

		for (int strIndex = 0; strIndex < keyLength; strIndex++)
		{
			c = string[index][strIndex];

			if (c >= 'a' && c <= 'z')
			{
				c = c - 'a';
			}
			else if (c >= 'A' && c <= 'Z')
			{
				c = c + 32 - 'a';
			}
			else if (c == '.')
			{
				c = 26;
			}
			else if (c == '/')
			{
				c = 27;
			}
			else if (c == '_')
			{
				c = 28;
			}
			else if (c >= '0' && c <= '9')
			{
				c = 29 + c - '0';
			}
			else
			{
				__IE_WARNING__("IEDictionary : error.\n");
			}

			if (m_curEntry)
			{
				m_curEntry = m_curEntry->m_nextEntry[c];
			}
		}
	}
}

void IEDictionary::InsertKeyChar(const char &c)
{
	unsigned char newC = c;
	ConvertKeyChar(newC);

	if (m_curEntry)
	{
		m_curEntry = m_curEntry->m_nextEntry[c];
	}
}

void IEDictionary::InsertKeyInt(const int &i)
{
	unsigned char c = 29 + i;

	if (m_curEntry)
	{
		m_curEntry = m_curEntry->m_nextEntry[c];
	}
}

void IEDictionary::GetCurEntry()
{

}

IEObject * IEDictionary::GetCufFind()
{
	IEEntry * curFinder = m_curEntry;
	m_curEntry = NULL;

	if (curFinder)
	{
		return curFinder->m_object;
	}
	else
	{
		return NULL;
	}
}

void IEDictionary::BurnEntry(IEEntry * entry)
{
	if (entry)
	{
		for (int index = 0; index < IE_ENTRY_WORD_COUNT; index++)
		{
			BurnEntry(entry->m_nextEntry[index]);
		}
		delete entry;
	}
}

void IEDictionary::DeleteEntry(const char * keyString)
{
	int keyLength;
	unsigned char * converedKey = ConvertKeyString(keyString, keyLength);

	IEEntry * burnEntry = m_head;
	IEEntry * burnLastEntry = m_head;
	unsigned char burnC;

	IEEntry * lastEntry = m_head;
	IEEntry * curEntry = m_head;
	for (int index = 0; index < keyLength; index++)
	{
		unsigned char c = converedKey[index];

		if (curEntry)
		{
			lastEntry = curEntry;
			curEntry = curEntry->m_nextEntry[c];

			for (int burnIndex = 0; burnIndex < IE_ENTRY_WORD_COUNT; burnIndex++)
			{
				if (lastEntry->m_nextEntry[c] != NULL && burnIndex != c)
				{
					burnLastEntry = lastEntry;
					burnEntry = curEntry;
					burnC = c;
				}
			}
		}
		else
		{
			delete[]converedKey;
			return;
		}
	}

	delete[]converedKey;
	BurnEntry(burnEntry);
	burnLastEntry->m_nextEntry[burnC] = NULL;
}

void IEDictionary::ConvertKeyChar(unsigned char &key)
{
	if (key >= 'a' && key <= 'z')
	{
		key = key - 'a';
	}
	else if (key >= 'A' && key <= 'Z')
	{
		key = key + 32 - 'a';
	}
	else if (key == '.')
	{
		key = 26;
	}
	else if (key == '/')
	{
		key = 27;
	}
	else if (key == '_')
	{
		key = 28;
	}
	else if (key >= '0' && key <= '9')
	{
		key = 29 + key - '0';
	}
	else
	{
		__IE_WARNING__("IEDictionary : error.\n");
	}
}

unsigned char * IEDictionary::ConvertKeyString(const char * keyString, int &keyLength)
{
	keyLength = strlen(keyString);
	unsigned char * keys = new unsigned char[keyLength];

	for (int index = 0; index < keyLength; index++)
	{
		if (keyString[index] >= 'a' && keyString[index] <= 'z')
		{
			keys[index] = keyString[index] - 'a';
		}
		else if (keyString[index] >= 'A' && keyString[index] <= 'Z')
		{
			keys[index] = keyString[index] + 32 - 'a';
		}
		else if (keyString[index] == '.')
		{
			keys[index] = 26;
		}
		else if (keyString[index] == '/')
		{
			keys[index] = 27;
		}
		else if (keyString[index] == '_')
		{
			keys[index] = 28;
		}
		else if (keyString[index] >= '0' && keyString[index] <= '9')
		{
			keys[index] = 29 + keyString[index] - '0';
		}
		else
		{
			__IE_WARNING__("IEDictionary : error.\n");
		}
	}

	return keys;
}

IEResourcesDictionary * IEResourcesDictionary::m_StaticResourceDictionary = NULL;
IESettingDictionary * IESettingDictionary::m_StaticEngineDictionary = NULL;

void IESettingDictionary::Initialization()
{
	IEDictionary::Initialization();

	LoadSettings();
}

void IESettingDictionary::LoadSettings()
{
	IEString baseDir = IEString("../Debug/data/");
	IEString settingFileDir = baseDir + "setting.txt";

	FILE * p = fopen(settingFileDir.GetString(), "r");
	char setting[256];
	while (fgets(setting, 256, p) != NULL)
	{
		AnalyzeSetting(setting);
	}
	fclose(p);
}

void IESettingDictionary::AnalyzeSetting(char * setting)
{
	IEString set = setting;
	set.DeleteChar(' ');
	set.DeleteChar('\n');
	
	if (set.isNote())
	{
		//检测是否为注释行
		return;
	}

	int equalCount = set.DetectedChar('=');
	if (equalCount != 1)
	{
		//没有或者不止一个符号 错误的设置格式
		return;
	}

	int splitRes = -1;
	IEArray * stringArray = set.SplitBy('=', splitRes);
	if (splitRes != 2)
	{
		//分割的结果不为2 错误的设置格式
		return;
	}

	IEString ** strings = (IEString **)(stringArray->GetContainer());
	strings[0]->LowerChar();
	int resType = strings[1]->DetectedType();

	IEObject * value = NULL;
	IEString * key = IEString::Create(strings[0]->GetString());
	key->AutoRelease();

	int intValue;
	float floatValue;

	switch (resType)
	{
	case 1:
		intValue = strings[1]->transToInt();
		value = new IEBaseType<int>(intValue);
		break;
	case 2:
		floatValue = strings[1]->transToFloat();
		value = new IEBaseType<int>(floatValue);
		break;
	case 3:
		value = IEString::Create(strings[1]->GetString());
		IEString * s = (IEString *) value;
		break;
	}

	AddEntry(value, key->GetString());
}

IE_END