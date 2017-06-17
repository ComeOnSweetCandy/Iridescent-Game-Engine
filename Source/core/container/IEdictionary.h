/***********************************
* name     : IEdictionary.h
* creater  : cosc
* info     : shared dictionary pool
* date     : 2016/11/28
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DICTIONARY__
#define __IE_DICTIONARY__

#include "../IEobject.h"

IE_BEGIN

#define IE_ENTRY_WORD_COUNT 39

class IEObject;

class __IE_DLL__ IEEntry
{
public:
	IEEntry();
	~IEEntry();
	IEEntry(IEObject * object);

public:
	IEObject * m_object;
	IEEntry * m_nextEntry[IE_ENTRY_WORD_COUNT];
};

class __IE_DLL__ IEDictionary:public IEObject
{
public:
	IEDictionary();
	virtual ~IEDictionary();
	virtual void Initialization();
	static IEDictionary * CreateAndRetain();

public:
	IEObject*& operator[](const char * keyString);

	IEEntry * AddEntry(IEObject * object, const char * keyString);
	IEEntry * FindEntry(const char * keyString);
	IEEntry * FindEntry2(const char * keyString);
	
	void InsertKeyString(const char * string);
	void InsertKeyStrings(char ** string, unsigned int count);
	void InsertKeyChar(const char &c);
	void InsertKeyInt(const int &i);
	void GetCurEntry();
	IEObject * GetCufFind();

	void BurnEntry(IEEntry * entry);
	void DeleteEntry(const char * keyString);

	inline void ConvertKeyChar(unsigned char &newKey);
	unsigned char * ConvertKeyString(const char * keyString, int &keyLength);

private:
	IEEntry * m_head;
	IEEntry * m_curEntry;
};

class __IE_DLL__ IEResourcesDictionary :public IEDictionary
{
public:
	IEResourcesDictionary(){};
	virtual ~IEResourcesDictionary(){};
	virtual void Release(){ delete this; };
	static IEResourcesDictionary & Alias()
	{
		if (m_StaticResourceDictionary == NULL)
		{
			m_StaticResourceDictionary = new IEResourcesDictionary();
			m_StaticResourceDictionary->Initialization();
		}
		return *m_StaticResourceDictionary;
	}
	static IEResourcesDictionary * Share()
	{
		if (m_StaticResourceDictionary == NULL)
		{
			m_StaticResourceDictionary = new IEResourcesDictionary();
			m_StaticResourceDictionary->Initialization();
		}
		return m_StaticResourceDictionary;
	}

private:
	static IEResourcesDictionary * m_StaticResourceDictionary;
};

#define RESOURCE IEResourcesDictionary::Alias()

class __IE_DLL__ IESettingDictionary :public IEDictionary
{
public:
	IESettingDictionary(){};
	virtual ~IESettingDictionary(){};
	virtual void Initialization();
	virtual void Release(){ delete this; };
	static IESettingDictionary & Alias()
	{
		if (m_StaticEngineDictionary == NULL)
		{
			m_StaticEngineDictionary = new IESettingDictionary();
			m_StaticEngineDictionary->Initialization();
		}
		return *m_StaticEngineDictionary;
	}
	static IESettingDictionary * Share()
	{
		if (m_StaticEngineDictionary == NULL)
		{
			m_StaticEngineDictionary = new IESettingDictionary();
			m_StaticEngineDictionary->Initialization();
		}
		return m_StaticEngineDictionary;
	}

public:
	void LoadSettings();
	void AnalyzeSetting(char * setting);

private:
	static IESettingDictionary * m_StaticEngineDictionary;
};

#define SETTING IESettingDictionary::Alias()

IE_END

#endif