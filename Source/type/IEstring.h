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
	IEString GetFileNameBody();											//������ļ�����ȡ������
	IEString GetFileNameExtensions();									//������ļ�����ȡ����չ��

	bool isNote();														//����ļ��ڵ����ݶ��ԣ��Ƿ�Ϊע����

public:
	IEContainer * SplitBy(char c);										//��ĳ���ַ���,�ָ�
	IEContainer * SplitBy(char beginC, char endC);						//�ָ��ַ��� �п�ͷ�ͽ�β�ķ�ʽ
	int PushSeveralChar(char c);										//��ǰ�ƽ������ַ�
	int DetectedChar(char c);											//���ĳ���ַ����ֵĴ���
	int FindCharFromIndex(char c, int beginIndex, int findIndex);		//��ѯ��beginIndexλ����ĵ�findIndex���ַ��Ƿ���ڣ������ڵ�index
	int FindString(char * string, int index = 1);						//��ѯ��index���ַ����������ĸ�λ��
	void DeleteChar(char c);											//ɾ���ַ����е�ĳ���ַ�
	int DeleteString(char * str, int deleteCount);						//ɾ���ַ����е�ָ�����ַ����͸��� / ���صĽ�� Ϊ�ɹ�ɾ���ĸ���
	IEString * SubString(int beginIndex, int deleteLength);				//�ַ�����ȡ
	void OverthrowString();												//�ߵ��ַ���
	void LowerChar();													//ȫ��ת��ΪСд
	int DetectedType();													//���ַ�������ת��Ϊ��������ʱ�򣬼������
	int transToInt();													//ת��Ϊ����
	float transToFloat();												//ת��Ϊ������
	float * transToFloats();											//ת��Ϊ������������
	float transFromPercentToFloat();									//�ٷֱ�ת��Ϊ������

private:
	char * m_string;
};

IE_END

#endif