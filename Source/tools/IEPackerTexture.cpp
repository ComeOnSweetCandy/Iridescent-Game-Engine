#define __IE_DLL_EXPORTS__
#include "IEPackerTexture.h"

#include "../core/container/IEcontianer.h"
#include "../core/container/IEdictionary.h"

IE_BEGIN

IEPackerTexture::IEPackerTexture()
{
	m_groupCount = 0;
	m_textureId = NULL;
}

IEPackerTexture::~IEPackerTexture()
{
	delete[] m_textureId;
}

void IEPackerTexture::Initialization(IEXml * xml)
{
	const char * textureName = LoadXML(xml);
	LoadTexture(textureName);
}

IEPackerTexture * IEPackerTexture::Create(IEXml * xml)
{
	IEPackerTexture * texture = new IEPackerTexture();
	texture->Initialization(xml);
	return texture;
}

GLuint * IEPackerTexture::GetTexture(float& beginX, float& beginY, float& sizeX, float& sizeY)
{
	return m_textureId;
}

const char * IEPackerTexture::LoadXML(IEXml * xml)
{
	const char * textureName = xml->FindChild("tex")->ValueString();
	IEContainer * arrays = xml->FindChilds("ground");
	IEXml ** xmls = (IEXml **)(arrays->GetContainer());
	m_groupCount = arrays->Count();
	m_textureGroups = new IETextureGroup[m_groupCount];


	for (unsigned char index = 0; index < m_groupCount; index++)
	{
		xmls[index];
		m_textureGroups[index]

	}


	return textureName;
}

void IEPackerTexture::LoadTexture(const char * textureName)
{
	IEString * texturesFileBaseDir = (IEString *)(SETTING["TexDir"]);
	IEString textureFileDir = *texturesFileBaseDir + textureName;

	m_textureId = new GLuint[1];
	IEImage * m_image = new IEImage();
	m_image->LoadImageData(textureFileDir);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glGenTextures(1, m_textureId);

	glBindTexture(GL_TEXTURE_2D, *m_textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (m_image->m_imgComponents == 3)
	{
		int size = m_image->m_imgWidth * m_image->m_imgHeight * 4;
		unsigned char * newData = new unsigned char[size];

		for (int iii = 0; iii < m_image->m_imgWidth * m_image->m_imgHeight; iii++)
		{
			memcpy(newData + iii * 4, m_image->m_imgData + iii * 3, 3);
			*(newData + iii * 4 + 3) = 0xFF;
		}

		delete[]m_image->m_imgData;
		m_image->m_imgData = newData;

		m_image->m_imgComponents = 4;
		m_image->m_imgFormat = GL_RGBA;
	}

	if (m_image->m_imgWidth == m_image->m_imgHeight)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, m_image->m_imgComponents, m_image->m_imgWidth, m_image->m_imgHeight, 0, m_image->m_imgFormat, GL_UNSIGNED_BYTE, m_image->m_imgData);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, m_image->m_imgComponents, m_image->m_imgWidth, m_image->m_imgHeight, 0, m_image->m_imgFormat, GL_UNSIGNED_BYTE, NULL);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_image->m_imgWidth, m_image->m_imgHeight, m_image->m_imgFormat, GL_UNSIGNED_BYTE, m_image->m_imgData);
	}
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	m_image->Release();
}

IE_END