#define __IE_DLL_EXPORTS__
#include "IEPackerTexture.h"

#include "../core/container/IEcontianer.h"
#include "../core/container/IEdictionary.h"
#include "IEtime.h"

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

GLuint * IEPackerTexture::GetTexture(IETextureUnitState * unitState)
{
	unitState->_CurTime += IETime::Share()->GetLastFrapPassingTime();
	unsigned char groupIndex = unitState->_GroupIndex;
	unsigned char frapIndex = unitState->_FrapIndex;

	if (unitState->_CurTime >= m_textureGroups[groupIndex]._Fraps[frapIndex]._End)
	{
		frapIndex++;

		if (frapIndex >= m_textureGroups[groupIndex]._FrapsCount)
		{
			frapIndex = 0;
		}
	}

	unitState->_FrapIndex = frapIndex;
	unitState->_X = m_textureGroups[groupIndex]._Fraps[frapIndex]._X;
	unitState->_Y = m_textureGroups[groupIndex]._Fraps[frapIndex]._Y;
	unitState->_Width = m_textureGroups[groupIndex]._Fraps[frapIndex]._Width;
	unitState->_Height = m_textureGroups[groupIndex]._Fraps[frapIndex]._Height;

	return m_textureId;
}

const char * IEPackerTexture::LoadXML(IEXml * xml)
{
	const char * textureName = xml->FindChild("tex")->ValueString();
	IEContainer * arrays = xml->FindChilds("group");
	IEXml ** xmls = (IEXml **)(arrays->GetContainer());
	m_groupCount = arrays->Count();

	if (m_groupCount != 0)
	{
		m_textureGroups = new IETextureGroup[m_groupCount];
	}

	for (unsigned char index = 0; index < m_groupCount; index++)
	{
		//拷贝名字
		const char * name = xmls[index]->FindChild("name")->ValueString();
		int nameLength = strlen(name);
		m_textureGroups[index]._Name = new char[nameLength + 1];
		strcpy(m_textureGroups[index]._Name, name);

		//获取帧数
		m_textureGroups[index]._FrapsCount = xmls[index]->FindChild("frapsCount")->ValueInt();
		IEContainer * fraps = xmls[index]->FindChilds("frap");

		m_textureGroups[index]._Fraps = new IETextureFrap[m_textureGroups[index]._FrapsCount];
		for (unsigned char index1 = 0; index1 < m_textureGroups[index]._FrapsCount; index1++)
		{
			FillTextureFrap(m_textureGroups[index]._Fraps[index1], (IEXml *)(fraps->Find(index1)));
		}
	}
	return textureName;
}

void IEPackerTexture::FillTextureFrap(IETextureFrap& textureFrap, IEXml * xml)
{
	textureFrap._X = xml->FindChild("x")->ValueInt();
	textureFrap._Y = xml->FindChild("y")->ValueInt();
	textureFrap._Width = xml->FindChild("width")->ValueInt();
	textureFrap._Height = xml->FindChild("height")->ValueInt();
	textureFrap._End = xml->FindChild("end")->ValueFloat();
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