/***********************************
* name     : IEstring.h
* creater  : cosc
* info     : class string
* date     : 2016/11/18
* version  : 1.0
* remark   : string
************************************/

#ifndef __IE_STRING__
#define __IE_STRING__

#include "../core/IEobject.h"

IE_BEGIN

#define STRING_TO_NONE		0
#define STRING_TO_INT		1
#define STRING_TO_FLOAT		2
#define STRING_TO_STRING	3

#define pOBJECT_TO_pSTRING(__pObject__)\
	((IEString *)__pObject__)
#define pOBJECT_TO_cSTRING(__pObject__)\
	(*((IEString *)__pObject__))

class IEContainer;

class __IE_DLL__ IEString:public IEObject
{
public:
	IEString();
	IEString(const IEString &string);
	IEString(const char &c);
	IEString(const char *string);
	IEString(const int &value);
	virtual ~IEString();

	static IEString * Create();
	static IEString * Create(const char &c);
	static IEString * Create(const char *string);

public:
	unsigned int Length() const;
	unsigned int Size() const;
	void EmptyString();

	IEString operator +(const IEString &string) const;
	IEString operator +(const char * string) const;
	IEString operator +(const char &c) const;
	IEString operator +(const int &i) const;
	IEString operator +(const float &f) const;

	void operator =(const IEString &string);
	void operator =(const char *string);
	void operator =(const char &c);

	bool operator ==(const IEString &string);
	bool operator ==(const char *string);

	void operator +=(const IEString &string);
	void operator +=(const char *string);
	void operator +=(const char &c);

	char & operator[](unsigned short int index);

	IEString& operator <<(const IEString &string);
	IEString& operator <<(const char * string);
	IEString& operator <<(const char &c);
	IEString& operator <<(const int &i);

	const char * GetString() const;
	
public:
	IEString GetFileNameBody();											//如果是文件名，取得主体
	IEString GetFileNameExtensions();									//如果是文件名，取得拓展名

	bool isNote();														//针对文件内的内容而言，是否为注释行

public:
	IEContainer * SplitBy(char c);										//按某个字符串,分割
	IEContainer * SplitBy(char beginC, char endC);						//分割字符串 有开头和结尾的方式
	int PushSeveralChar(char c);										//向前推进几个字符
	int DetectedChar(char c);											//检测某个字符出现的次数
	int FindCharFromIndex(char c, int beginIndex, int findIndex);		//查询从beginIndex位置起的第findIndex个字符是否存在，及存在的index
	int FindString(char * string, int index = 1);						//查询第index个字符串出现在哪个位置
	void DeleteChar(char c);											//删除字符串中的某个字符
	int DeleteString(char * str, int deleteCount);						//删除字符串中的指定的字符串和个数 / 返回的结果 为成功删除的个数
	IEString * SubString(int beginIndex, int deleteLength);				//字符串截取
	void OverthrowString();												//颠倒字符串
	void LowerChar();													//全部转换为小写
	int DetectedType();													//当字符串可以转换为其它类型时候，检测类型
	int transToInt();													//转换为整形
	float transToFloat();												//转换为浮点型
	float * transToFloats();											//转换为无数个浮点数
	float transFromPercentToFloat();									//百分比转换为浮点型

private:
	char * m_string;
};

IE_END

#endif