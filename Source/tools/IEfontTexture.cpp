#define __IE_DLL_EXPORTS__
#include "IEfontTexture.h"

IE_BEGIN

IEFontTexture * IEFontTexture::m_fontTexture = NULL;

IEFontTexture::IEFontTexture()
{
	m_textureId = NULL;
	m_textureSize = IEGrid(0, 0);
	m_textureName = "../Debug/data/font/font_0.data";
}

IEFontTexture::~IEFontTexture()
{
	delete[] m_textureId;
}

void IEFontTexture::Initialization(const IEString &textureName)
{
	m_textureName = textureName;

	LoadFontTexture();
}

IEFontTexture * IEFontTexture::Create(const char * textureName)
{
	if (m_fontTexture == NULL)
	{
		m_fontTexture = new IEFontTexture();
		m_fontTexture->Initialization(textureName);
	}
	return m_fontTexture;
}

IEFontTexture * IEFontTexture::Share()
{
	if (m_fontTexture == NULL)
	{
		__IE_WARNING__("IEFontTexture : error.\n");
	}
	return m_fontTexture;
}

void IEFontTexture::PreloadFontTexture(const char * textureName)
{

}

void IEFontTexture::LoadFontTexture()
{
	m_textureId = new GLuint[1];
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glGenTextures(1, &m_textureId[0]);

	IEImage * image = IEImage::Create();
	image->LoadImageData(m_textureName);
	m_textureSize = IEGrid(image->m_imgWidth, image->m_imgHeight);

	glBindTexture(GL_TEXTURE_2D, m_textureId[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	if (image->m_imgWidth == image->m_imgHeight)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, image->m_imgComponents, image->m_imgWidth, image->m_imgHeight, 0, image->m_imgFormat, GL_UNSIGNED_BYTE, image->m_imgData);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, image->m_imgComponents, image->m_imgWidth, image->m_imgHeight, 0, image->m_imgFormat, GL_UNSIGNED_BYTE, NULL);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->m_imgWidth, image->m_imgHeight, image->m_imgFormat, GL_UNSIGNED_BYTE, image->m_imgData);
	}
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	image->Release();
	image = NULL;
}

IE_END