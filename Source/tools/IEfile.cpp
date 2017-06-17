#define __IE_DLL_EXPORTS__
#include "IEfile.h"

IE_BEGIN

IEFile::IEFile()
{

}

IEFile::~IEFile()
{

}

void IEFile::Initialization()
{

}

IEFile * IEFile::Create()
{
	IEFile * object = new IEFile();
	object->Initialization();
	return object;
}

void IEFile::OpenFile(const char * fileName, const char * type)
{
	m_filePoint = fopen(fileName, type);
	if (!m_filePoint)
	{
		__IE_WARNING__("the file does not exiets");
	}
	if (m_filePoint) 
	{
		fseek(m_filePoint, 0, SEEK_END);
		m_fileLength = ftell(m_filePoint);
	}
	m_fileBody = (void *)malloc(sizeof(char)* m_fileLength);
	fread(m_fileBody, m_fileLength, 1, m_filePoint);
}

unsigned int IEFile::GetFileLength()
{
	return m_fileLength;
}

void IEFile::CloseFile()
{
	fclose(m_filePoint);
}

IEFile * fopen_ie(const char * fileName, const char * type)
{
	IEFile * fp = IEFile::Create();
	fp->OpenFile(fileName, type);
	return fp;
}

void fclose_ie(IEFile * file)
{
	file->CloseFile();
	delete file;
}

void fread_ie(void * buffer, unsigned int size, unsigned int count, IEFile * file)
{

}

void fwrite_ie(void * buffer, unsigned int size, unsigned int count, IEFile * file)
{

}

IE_END