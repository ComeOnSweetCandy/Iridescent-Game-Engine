/***********************************
* name     : IEimage.h
* creater  : cosc
* info     : load images
* date     : 2016/11/20
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_IMAGE__
#define __IE_IMAGE__

#include "../../../libs/zlib/src/zlib.h"

#include "../global/IEstdafx.h"
#include "../type/IEstring.h"
#include "../type/IEvector.h"

IE_BEGIN

class IEResourcesDictionary;

enum IEImageSupportList
{
	IEImageTGA,
	IEImagePNG
};

#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为1字节对齐
typedef struct
{
	GLbyte	identsize;
	GLbyte	colorMapType;
	GLbyte	imageType;
	unsigned short	colorMapStart;
	unsigned short	colorMapLength;
	unsigned char 	colorMapBits;
	unsigned short	xstart;
	unsigned short	ystart;
	unsigned short	width;
	unsigned short	height;
	GLbyte	bits;
	GLbyte	descriptor;
}TGAHEADER;
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
typedef struct
{
	GLint		chunkLength;
	GLint		chunkType;
	GLubyte *	chunkData;
	GLint		chunkCRC;
}PNGCHUNK;
#pragma pack(pop)

#define CHUNK_IHDR ((0x49)|(0x48<<8)|(0x44<<16)|(0x52<<24))
#define CHUNK_IDAT ((0x49)|(0x44<<8)|(0x41<<16)|(0x54<<24))
#define CHUNK_IEND ((0x49)|(0x45<<8)|(0x4e<<16)|(0x44<<24))

class __IE_DLL__ IEImage
{
public:
	IEImage();
	~IEImage();
	static IEImage * Create();
	static IEImage * Create(unsigned int x, unsigned int y);
	void Release();
	void Initialization();

public:
	void LoadImageData(IEString &file);
	void CheckType(IEString &file);

	static void WriteTGA(const char *filename, DWORD width, DWORD height, const byte *data);
	void LoadTGA(const char * szFileName, GLint * iWidth, GLint * iHeight, GLint * iComponents, GLenum * eFormat);
	void LoadPNG(const char * szFileName, GLint * iWidth, GLint * iHeight, GLint * iComponents, GLenum * eFormat);
	void SavePNG(const char * fileName);

private:
	unsigned char * m_imgData;
	int m_imgWidth;
	int m_imgHeight;
	int m_imgComponents;
	unsigned int m_imgFormat;

	friend class IETexture;
	friend class IEFontTexture;
};

IE_END

#endif