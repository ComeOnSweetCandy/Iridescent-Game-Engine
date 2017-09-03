#define __IE_DLL_EXPORTS__
#include "IEPackerTexture.h"

#include "../core/container/IEcontianer.h"
#include "../core/container/IEdictionary.h"

#include "IEtime.h"
#include "../thread/IEthread.h"

IE_BEGIN

IEPackerTexture::IEPackerTexture()
{
	m_groupCount = 0;
	m_textureId = NULL;
	m_textureGroups = NULL;
	m_textureWidth = 0;
	m_textureHeight = 0;
}

IEPackerTexture::~IEPackerTexture()
{
	if (m_textureGroups)
	{
		for (unsigned char index = 0; index < m_groupCount; index++)
		{
			for (unsigned char index1 = 0; index1 < m_textureGroups[index]._SameCount; index1++)
			{
				delete[]m_textureGroups[index]._Same[index1]._Fraps;
			}
			delete[]m_textureGroups[index]._Same;
			delete[]m_textureGroups[index]._Name;
			delete[]m_textureGroups[index]._Assort;
		}
		delete[]m_textureGroups;
	}
	delete[]m_textureId;
}

void IEPackerTexture::Initialization(IEXml * xml)
{
	const char * textureName = LoadXML(xml);
	LoadTexture(textureName);
}

void IEPackerTexture::Initialization(const char * textureName)
{
	LoadTexture(textureName);
	ForgeryXML(textureName);
}

IEPackerTexture * IEPackerTexture::Create(IEXml * xml)
{
	const char * textureName = xml->FindChild("tex")->ValueString();
	IEObject * resource = RESOURCE[textureName];
	if (resource == NULL)
	{
		IEPackerTexture * texture = new IEPackerTexture();
		texture->Initialization(xml);
		RESOURCE[textureName] = texture;
		return texture;
	}
	else
	{
		return (IEPackerTexture *)resource;
	}
}

IEPackerTexture * IEPackerTexture::Create(const char * textureName)
{
	IEObject * resource = RESOURCE[textureName];
	if (resource == NULL)
	{
		IEPackerTexture * texture = new IEPackerTexture();
		texture->Initialization(textureName);
		RESOURCE[textureName] = texture;
		return texture;
	}
	else
	{
		return (IEPackerTexture *)resource;
	}
}

void IEPackerTexture::GetTexture(IETextureUnitState * unitState)
{
	if (unitState->_TextureID == 0)
	{
		//如果当前所制定的group不存在 则直接返回
		return;
	}

	unitState->_CurTime += IETime::Share()->GetLastFrapPassingTime();
	unsigned char groupIndex = unitState->_GroupIndex;
	unsigned char sameIndex = unitState->_SameIndex;
	unsigned char frapIndex = unitState->_FrapIndex;

	if (unitState->_CurTime >= m_textureGroups[groupIndex]._Same[sameIndex]._Fraps[frapIndex]._End)
	{
		frapIndex++;

		if (frapIndex >= m_textureGroups[groupIndex]._Same[sameIndex]._FrapsCount)
		{
			frapIndex = 0;
			unitState->_CurTime = 0.0f;
		}
	}

	unitState->_FrapIndex = frapIndex;
	unitState->_X = m_textureGroups[groupIndex]._Same[sameIndex]._Fraps[frapIndex]._X;
	unitState->_Y = m_textureGroups[groupIndex]._Same[sameIndex]._Fraps[frapIndex]._Y;
	unitState->_Width = m_textureGroups[groupIndex]._Same[sameIndex]._Fraps[frapIndex]._Width;
	unitState->_Height = m_textureGroups[groupIndex]._Same[sameIndex]._Fraps[frapIndex]._Height;

	unitState->_BeginX = ((float)unitState->_X) / ((float)m_textureWidth);
	unitState->_BeginY = ((float)unitState->_Y) / ((float)m_textureHeight);
	unitState->_EndX = ((float)unitState->_X + (float)unitState->_Width) / ((float)m_textureWidth);
	unitState->_EndY = ((float)unitState->_Y + (float)unitState->_Height) / ((float)m_textureHeight);
}

void IEPackerTexture::ChangeAssort(IETextureUnitState * textureUnitState, const char * assortName)
{

}

void IEPackerTexture::ChangeGroup(IETextureUnitState * textureUnitState, const char * groupName, unsigned char sameIndex)
{
	//先进行检测是否为重复修改group 
	//但是首先得确定 之前一个groupIndex为空 也就是textureID是否为零
	if (textureUnitState->_TextureID != 0)
	{
		int res = strcmp(m_textureGroups[textureUnitState->_GroupIndex]._Name, groupName);
		if (res == 0)
		{
			if (sameIndex - 1 == textureUnitState->_SameIndex)
			{
				return;
			}
		}
	}

	for (unsigned char index = 0; index < m_groupCount; index++)
	{
		int res = strcmp(m_textureGroups[index]._Name, groupName);
		if (res == 0)
		{
			if (sameIndex>m_textureGroups[index]._SameCount)
			{
				//超出了最大值
				break;
			}
			if (sameIndex == __IE_GROUP_RAND__)
			{
				//同名group之中随机一个
				sameIndex = rand() % m_textureGroups[index]._SameCount;
			}
			else
			{
				sameIndex--;
			}

			textureUnitState->_TextureID = *m_textureId;
			textureUnitState->_GroupIndex = index;
			textureUnitState->_SameIndex = sameIndex;
			textureUnitState->_FrapIndex = 0;
			textureUnitState->_CurTime = 0.0f;

			return;
		}
	}

	//如果没有找到
	textureUnitState->_TextureID = 0;
}

const char * IEPackerTexture::LoadXML(IEXml * xml)
{
	const char * textureName = xml->FindChild("tex")->ValueString();
	m_textureWidth = xml->FindChild("width")->ValueInt();
	m_textureHeight = xml->FindChild("height")->ValueInt();
	
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

		//拷贝组别
		const char * assort = xmls[index]->FindChild("assort")->ValueString();
		int assortLength = strlen(assort);
		m_textureGroups[index]._Assort = new char[assortLength + 1];
		strcpy(m_textureGroups[index]._Assort, assort);

		//获取同名的数目
		m_textureGroups[index]._SameCount = xmls[index]->FindChild("sameCount")->ValueInt();
		m_textureGroups[index]._Same = new IETextureSame[m_textureGroups[index]._SameCount];

		for (unsigned char sameIndex = 0; sameIndex < m_textureGroups[index]._SameCount; sameIndex++)
		{
			IEXml * sameXML = xmls[index]->FindChild("same", sameIndex);
			IEContainer * frapsXMLS = sameXML->FindChilds("frap");

			m_textureGroups[index]._Same[sameIndex]._FrapsCount = sameXML->FindChild("frapsCount")->ValueInt();
			m_textureGroups[index]._Same[sameIndex]._Fraps = new IETextureFrap[m_textureGroups[index]._Same[sameIndex]._FrapsCount];
			for (unsigned char index1 = 0; index1 < m_textureGroups[index]._Same[sameIndex]._FrapsCount; index1++)
			{
				FillTextureFrap(m_textureGroups[index]._Same[sameIndex]._Fraps[index1], (IEXml *)(frapsXMLS->Find(index1)));
			}
		}
	}
	return textureName;
}

void IEPackerTexture::ForgeryXML(const char * textureName)
{
	m_groupCount = 1;
	m_textureGroups = new IETextureGroup[m_groupCount];

	m_textureGroups[0]._Name = new char[4];
	strcpy(m_textureGroups[0]._Name, "def");

	m_textureGroups[0]._Assort = new char[7];
	strcpy(m_textureGroups[0]._Assort, "normal");

	m_textureGroups[0]._SameCount = 1;
	m_textureGroups[0]._Same = new IETextureSame[1];

	m_textureGroups[0]._Same[0]._FrapsCount = 1;
	m_textureGroups[0]._Same[0]._Fraps = new IETextureFrap[1];
	m_textureGroups[0]._Same[0]._Fraps[0]._X = 0;
	m_textureGroups[0]._Same[0]._Fraps[0]._Y = 0;
	m_textureGroups[0]._Same[0]._Fraps[0]._Width = m_textureWidth;
	m_textureGroups[0]._Same[0]._Fraps[0]._Height = m_textureHeight;
	m_textureGroups[0]._Same[0]._Fraps[0]._End = 0.0f;
}

void IEPackerTexture::FillTextureFrap(IETextureFrap& textureFrap, IEXml * xml)
{
	textureFrap._X = xml->FindChild("x")->ValueInt();
	textureFrap._Y = xml->FindChild("y")->ValueInt();
	textureFrap._Width = xml->FindChild("width")->ValueInt();
	textureFrap._Height = xml->FindChild("height")->ValueInt();
	textureFrap._End = xml->FindChild("end")->ValueFloat();

	//图片翻转
	textureFrap._Y = m_textureHeight - textureFrap._Y - textureFrap._Height;
}

void IEPackerTexture::LoadTexture(const char * textureName)
{
	IEString * texturesFileBaseDir = (IEString *)(SETTING["TexDir"]);
	IEString textureFileDir = *texturesFileBaseDir + textureName;

	m_textureId = new GLuint[1];
	IEImage * m_image = new IEImage();
	m_image->LoadImageData(textureFileDir);

	//释放前一些信息记录的保存
	m_textureWidth = m_image->m_imgWidth;
	m_textureHeight = m_image->m_imgHeight;

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glGenTextures(1, m_textureId);

	glBindTexture(GL_TEXTURE_2D, *m_textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//IEThreadProtocol::Share()->ThreadLoadImage(m_image);

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

	m_image->ReleaseDisreference();
}

IE_END