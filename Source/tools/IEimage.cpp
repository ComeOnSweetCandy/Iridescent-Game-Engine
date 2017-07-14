#define __IE_DLL_EXPORTS__
#include "IEimage.h"
#include "../core/container/IEdictionary.h"

#include "IEcrc.h"

IE_BEGIN

IEImage::IEImage()
{
	m_imgData = NULL;
	m_imgWidth = 0;
	m_imgHeight = 0;
	m_imgComponents = 0;
	m_imgFormat = 0;
}

IEImage::~IEImage()
{
	if (m_imgData != NULL)
	{
		free(m_imgData);
	}
	m_imgData = NULL;
}

void IEImage::Initialization()
{

}

IEImage * IEImage::Create()
{
	IEImage * object = new IEImage();
	object->Initialization();
	return object;
}

IEImage * IEImage::Create(unsigned int x, unsigned int y)
{
	IEImage * object = new IEImage();
	object->Initialization();
	return object;
}

void IEImage::LoadImageData(const char * file)
{
	this->CheckType(IEString(file));
}

void IEImage::LoadImageData(IEString &file)
{
	this->CheckType(file);
}

void IEImage::CheckType(IEString &file)
{
	IEString extensions = file.GetFileNameExtensions();

	if (extensions == "tga" || extensions == "TGA")
	{
		LoadTGA(file.GetString(), &m_imgWidth, &m_imgHeight, &m_imgComponents, &m_imgFormat);
	}
	else if (extensions == "png" || extensions == "PNG")
	{
		LoadPNG(file.GetString(), &m_imgWidth, &m_imgHeight, &m_imgComponents, &m_imgFormat);
	}
	else
	{
		__IE_WARNING__("this type can not be readed\n");
	}
}

void IEImage::LoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;

	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_BGR_EXT;
	*iComponents = GL_RGB8;

	pFile = fopen(szFileName, "rb");
	if (pFile == NULL)
		return;

	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

	int i = sizeof(TGAHEADER);

	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return;

	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	m_imgData = (GLubyte*)malloc(lImageSize * sizeof(GLubyte));
	if (m_imgData == NULL)
		return;

	if (fread(m_imgData, lImageSize, 1, pFile) != 1)
	{
		free(m_imgData);
		return;
	}

	switch (sDepth)
	{
	case 3:
		*eFormat = GL_BGR_EXT;
		*iComponents = GL_RGB8;
		break;
	case 4:
		*eFormat = GL_BGRA_EXT;
		*iComponents = GL_RGBA8;
		break;
	case 1:
		*eFormat = GL_LUMINANCE;
		*iComponents = GL_LUMINANCE8;
		break;
	};

	fclose(pFile);
	return;
}

void IEImage::WriteTGA(const char *filename, DWORD width, DWORD height, const byte *data)
{
	FILE *savefile = fopen(filename, "wb");

	byte type_header[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	fwrite(type_header, 12 * sizeof(byte), 1, savefile);

	byte header[6];
	header[0] = width % 256;
	header[1] = width / 256;
	header[2] = height % 256;
	header[3] = height / 256;
	header[4] = 32;
	header[5] = 8;

	fwrite(header, 6 * sizeof(byte), 1, savefile);

	unsigned int image_size = 4 * width*height;
	byte * invert_data = new byte[image_size];
	memset(invert_data, 0, image_size*sizeof(byte));

	for (unsigned int i = 0; i<image_size; i++)
	{
		invert_data[i] = data[i];
	}

	// Swap red and blue,RGBתΪBGR  
	for (unsigned int cswap = 0; cswap < image_size; cswap += 4)
	{
		byte r = invert_data[cswap];
		invert_data[cswap] = invert_data[cswap + 2];
		invert_data[cswap + 2] = r;
	}

	fwrite(invert_data, image_size*sizeof(byte), 1, savefile);
	fclose(savefile);
	delete[] invert_data;
}

void IEImage::LoadPNG(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE * pFile;
	GLubyte bitDepth;
	GLubyte colorType;
	GLubyte pass;
	bool isLoading = true;

	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_BGR_EXT;
	*iComponents = GL_RGB8;

	pFile = fopen(szFileName, "rb");
	if (pFile == NULL)
	{
		return;
	}

	PNGCHUNK chunk;
	GLubyte byte[8];
	fread(byte, sizeof(GLint)* 2, 1, pFile);

	while (isLoading)
	{
		fread(&chunk, sizeof(GLint)* 2, 1, pFile);
		chunk.chunkLength = __IE_INTREVERSE__(chunk.chunkLength);
		chunk.chunkData = (GLubyte *)malloc(sizeof(GLubyte)* chunk.chunkLength);
		fread(chunk.chunkData, sizeof(GLubyte)*chunk.chunkLength, 1, pFile);
		fread(&chunk.chunkCRC, sizeof(GLint), 1, pFile);

		if (chunk.chunkType == CHUNK_IHDR)
		{
			*iWidth = __IE_INTREVERSE__(*((int *)chunk.chunkData));
			*iHeight = __IE_INTREVERSE__(*((int *)(chunk.chunkData + 4)));

			bitDepth = *(chunk.chunkData + 8);
			colorType = *(chunk.chunkData + 9);

			switch (colorType)
			{
			case 2:
				*eFormat = GL_BGR_EXT;
				*iComponents = 3;
				pass = 3;
				break;
			case 3:
				*eFormat = GL_LUMINANCE;
				*iComponents = 1;
				pass = 1;
				break;
			case 6:
				*eFormat = GL_RGBA;
				*iComponents = 4;
				pass = 4;
				break;
			default:
				break;
			}
		}
		else if (chunk.chunkType == CHUNK_IDAT)
		{
			GLint bodySize = sizeof(GLubyte)* (*iWidth) * (*iHeight) * pass;
			GLint extraSize = sizeof(GLubyte)*(*iHeight);
			GLulong len_dest;
			GLulong len_src = (GLulong)chunk.chunkLength;
			GLubyte * pixelData = (GLubyte *)malloc(bodySize + extraSize);
			m_imgData = (GLubyte *)malloc(bodySize);
			uncompress(pixelData, &len_dest, chunk.chunkData, len_src);

			for (int index = 0; index < *iHeight; index++)
			{
				GLubyte filter = *(pixelData + index*(*iWidth) * pass + index);
				GLubyte * basePtr = m_imgData + (*iHeight - index - 1)* (*iWidth) * pass;
				memcpy(m_imgData + (*iHeight - index - 1)*(*iWidth) * pass, pixelData + index*(*iWidth) * pass + index + 1, (*iWidth)*pass);

				if (filter == 0)
				{

				}
				else if (filter == 1)
				{
					for (int pixelIndex = pass; pixelIndex < (*iWidth)*pass; pixelIndex = pixelIndex + pass)
					{
						GLubyte * ptr = basePtr + pixelIndex;
						for (int tunnel = 0; tunnel < pass; tunnel++)
						{
							*(ptr + tunnel) = *(ptr + tunnel - pass) + *(ptr + tunnel);
						}
					}
				}
				else if (filter == 2)
				{
					if (index != 0)
					{
						for (int pixelIndex = 0; pixelIndex < (*iWidth)*pass; pixelIndex = pixelIndex + pass)
						{
							GLubyte * ptr = basePtr + pixelIndex;
							for (int tunnel = 0; tunnel < pass; tunnel++)
							{
								*(ptr + tunnel) = *(ptr + tunnel + (*iWidth) * pass) + *(ptr + tunnel);
							}
						}
					}
				}
				else if (filter == 3)
				{
					if (index != 0)
					{
						//先处理位于第一个位置的数值
						GLubyte * ptr = basePtr;
						for (int tunnel = 0; tunnel < pass; tunnel++)
						{
							*(ptr + tunnel) = (*(ptr + tunnel + (*iWidth) * pass) + 0) / 2 + *(ptr + tunnel);
						}

						for (int pixelIndex = pass; pixelIndex < (*iWidth)*pass; pixelIndex = pixelIndex + pass)
						{
							GLubyte * ptr = basePtr + pixelIndex;
							for (int tunnel = 0; tunnel < pass; tunnel++)
							{
								*(ptr + tunnel) = (*(ptr + tunnel + (*iWidth) * pass) + *(ptr + tunnel - pass))/2 + *(ptr + tunnel);
							}
						}
					}
				}
				else if (filter == 4)
				{
					if (index == 0)
					{
						for (int pixelIndex = pass; pixelIndex < (*iWidth)*pass; pixelIndex = pixelIndex + pass)
						{
							GLubyte * ptr = basePtr + pixelIndex;
							for (int tunnel = 0; tunnel < pass; tunnel++)
							{
								*(ptr + tunnel) = *(ptr + tunnel - pass) + *(ptr + tunnel);
							}
						}
					}
					else
					{
						GLubyte * ptr = basePtr;
						for (int tunnel = 0; tunnel < pass; tunnel++)
						{
							*(ptr + tunnel) = *(ptr + tunnel + (*iWidth) * pass) + *(ptr + tunnel);
						}

						for (int pixelIndex = pass; pixelIndex < (*iWidth)*pass; pixelIndex = pixelIndex + pass)
						{
							GLubyte * ptr = basePtr + pixelIndex;
							for (int tunnel = 0; tunnel < pass; tunnel++)
							{
								GLubyte a = *(ptr + tunnel - pass);
								GLubyte b = *(ptr + tunnel + (*iWidth) * pass);
								GLubyte c = *(ptr + tunnel + (*iWidth) * pass - pass);
								GLint p = a + b - c;
								GLint pa = abs(p - (GLint)a);
								GLint pb = abs(p - (GLint)b);
								GLint pc = abs(p - (GLint)c);
								GLubyte pr;

								if (pa <= pb && pa <= pc)
								{
									pr = a;
								}
								else if (pb <= pc)
								{
									pr = b;
								}
								else
								{
									pr = c;
								}

								*(ptr + tunnel) = pr + *(ptr + tunnel);
							}
						}
					}
				}
			}
			free(pixelData);
		}
		else if (chunk.chunkType == CHUNK_IEND)
		{
			isLoading = false;
		}
		free(chunk.chunkData);
	}

	fclose(pFile);
	return;
}

void IEImage::SavePNG(const char * fileName)
{
	FILE * pFile = fopen(fileName, "wb");
	bool isWriting = true;

	GLubyte byte[8] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
	fwrite(byte, sizeof(GLint)* 2, 1, pFile);

	//WRITE IHDR
	PNGCHUNK ihdr_chunk;
	unsigned char ihdr_head[4] = { 0x49, 0x48, 0x44, 0x52 };
	unsigned char ihdr_data[13] = { 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x08, 0x06, 0x00, 0x00, 0x00 };
	unsigned char in[17] = { 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x08, 0x06, 0x00, 0x00, 0x00 };

	ihdr_chunk.chunkLength = __IE_INTREVERSE__(13);
	ihdr_chunk.chunkType = CHUNK_IHDR;
	ihdr_chunk.chunkData = ihdr_data;

	//修改宽度和高度
	int * ww = (int *)in + 1;
	int * hh = (int *)in + 2;
	*ww = __IE_INTREVERSE__(m_imgWidth);
	*hh = __IE_INTREVERSE__(m_imgHeight);
	ww = (int *)ihdr_data;
	hh = (int *)ihdr_data + 1;
	*ww = __IE_INTREVERSE__(m_imgWidth);
	*hh = __IE_INTREVERSE__(m_imgHeight);
	ihdr_chunk.chunkCRC = __IE_INTREVERSE__(crc(in, 17));

	fwrite(&ihdr_chunk, 8, 1, pFile);
	fwrite(ihdr_chunk.chunkData, 1, 13, pFile);
	fwrite(&(ihdr_chunk.chunkCRC), 1, 4, pFile);

	//WRITE DATA
	int pass = 4;
	PNGCHUNK idat_chunk;
	unsigned char idat_head[4] = { 0x49, 0x44, 0x41, 0x54 };

	idat_chunk.chunkType = CHUNK_IDAT;
	idat_chunk.chunkData = NULL;
	
	//这里采用滤波方式0
	int srcSize = (m_imgWidth * m_imgHeight) * pass + m_imgHeight + 4;
	GLubyte * dataStart = NULL;
	idat_chunk.chunkData = new unsigned char[srcSize];
	dataStart = idat_chunk.chunkData + 4;

	for (int index = 0; index < m_imgHeight; index++)
	{
		*(dataStart + index * (m_imgWidth) * pass + index) = 0;
		memcpy(dataStart + index * (m_imgWidth)* pass + index + 1, m_imgData + index * (m_imgWidth)* pass, m_imgWidth * pass);
	}

	GLulong len_dest;
	GLulong len_src = 1;
	GLubyte * resultData = new unsigned char[srcSize * 2 + 4];
	compress(resultData + 4, &len_dest, dataStart, srcSize - 4);

	GLuint * type = (GLuint *)resultData;
	*type = CHUNK_IDAT;

	idat_chunk.chunkLength = __IE_INTREVERSE__(len_dest);			//???
	idat_chunk.chunkCRC = __IE_INTREVERSE__(crc(resultData, len_dest + 4));	//???

	fwrite(&idat_chunk, 8, 1, pFile);
	fwrite(resultData + 4, 1, len_dest, pFile);
	fwrite(&(idat_chunk.chunkCRC), 1, 4, pFile);

	//清理空间
	delete[]idat_chunk.chunkData;
	delete[]resultData;

	//WRITE END
	PNGCHUNK iend_chunk;
	unsigned char iend_head[4] = { 0x49, 0x45, 0x4e, 0x44 };

	iend_chunk.chunkLength = 0;
	iend_chunk.chunkType = CHUNK_IEND;
	iend_chunk.chunkData = NULL;
	iend_chunk.chunkCRC = __IE_INTREVERSE__(crc(iend_head, 4));

	fwrite(&iend_chunk, 8, 1, pFile);
	fwrite(&(iend_chunk.chunkCRC), 1, 4, pFile);

	fclose(pFile);
	return;
}

IE_END