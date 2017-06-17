/***********************************
* name     : IEfile.h
* creater  : cosc
* info     : read file only enterence
* date     : 2016/11/28
* version  : 1.0
* remark   : rewrite file control sys.
************************************/

#ifndef __IE_FILE__
#define __IE_FILE__

#include "../global/IEstdafx.h"

IE_BEGIN

class __IE_DLL__ IEFile
{
public:
	IEFile();
	~IEFile();
	void Initialization();
	static IEFile * Create();

public:
	void OpenFile(const char * fileName, const char * type);
	void CloseFile();

public:


public:
	unsigned int GetFileLength();

public:
	FILE * m_filePoint;
	void * m_fileBody;
	unsigned int m_fileLength;
};

IEFile * fopen_ie(const char * fileName, const char * mode);
void fclose_ie(IEFile * file);
void fread_ie(void * buffer, unsigned int size, unsigned int count, IEFile * file);
void fwrite_ie(void * buffer, unsigned int size, unsigned int count, IEFile * file);

void addFile(IEFile * file, FILE * addFile);

IE_END

#endif