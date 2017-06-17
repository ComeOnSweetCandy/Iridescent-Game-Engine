#define __IE_DLL_EXPORTS__
#include "IEtexture.h"

#include "../core/container/IEdictionary.h"

IE_BEGIN

IETexture::IETexture()
{
	m_textureFramesCount = 0;
	m_textureId = NULL;
	m_textureSize = NULL;
}

IETexture::~IETexture()
{
	delete[] m_textureId;
	delete[] m_textureSize;
	delete[] m_timeAxis;
}

void IETexture::Initialization(const char * textureName)
{
	m_textureName = textureName;
	RESOURCE[textureName] = (IEObject *)this;

	LoadTextureInfo();
	LoadTexture();
}

IETexture * IETexture::Create(const char * textureName)
{
	IEObject * resource = RESOURCE[textureName];
	if (resource == NULL)
	{
		IETexture * texture = new IETexture();
		texture->Initialization(textureName);
		return texture;
	}
	else
	{
		return (IETexture *)resource;
	}
}

GLuint * IETexture::GetTexturesId()
{
	return m_textureId;
}

void IETexture::PreloadTexture(const char * textureName)
{

}

void IETexture::LoadTextureInfo()
{
	IEString * texturesFileBaseDir = (IEString *)(SETTING["TexDir"]);
	IEString textureFileDir = *texturesFileBaseDir + m_textureName;
	IEString fileBody = textureFileDir.GetFileNameBody();
	IEString fileExtension = textureFileDir.GetFileNameExtensions();

	FILE * fp = fopen((fileBody + ".data").GetString(), "r");

	if (fp)
	{
		fscanf(fp, "%d", &m_textureFramesCount);
		m_timeAxis = new float[m_textureFramesCount];
		for (int index = 0; index < m_textureFramesCount; index++)
		{
			fscanf(fp, "%f", &m_timeAxis[index]);
		}
		fscanf(fp, "%d", &m_triggerAxis);
		fclose(fp);
	}
	else
	{
		m_textureFramesCount = 1;
		m_timeAxis = new float[m_textureFramesCount];
		m_timeAxis[0] = 0.0f;
	}
}

void IETexture::LoadTexture()
{
	IEString * texturesFileBaseDir = (IEString *)(SETTING["TexDir"]);
	IEString textureFileDir = *texturesFileBaseDir + m_textureName;

	IEString fileBody = textureFileDir.GetFileNameBody();
	IEString fileExtension = textureFileDir.GetFileNameExtensions();

	int exist = 0;
	while (exist == 0)
	{
		IEString fileName = fileBody + "_" + IEString(m_textureFramesCount) + "." + fileExtension;
		exist = _access(fileName.GetString(), 0);

		if (exist == 0)
		{
			m_textureFramesCount++;
		}
	}

	if (m_textureFramesCount == 0)
	{
		printf("IETexture : error.\n");
	}

	m_textureId = new GLuint[m_textureFramesCount];
	m_textureSize = new IEGrid[m_textureFramesCount];
	IEImage ** m_image = new IEImage*[m_textureFramesCount];
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glGenTextures(m_textureFramesCount, &m_textureId[0]);

	for (int index = 0; index < m_textureFramesCount; index++)
	{
		IEString fileName = fileBody + "_" + IEString(index) + "." + fileExtension;
		m_image[index] = IEImage::Create();
		m_image[index]->LoadImageData(fileName);
		m_textureSize[index] = IEGrid(m_image[index]->m_imgWidth, m_image[index]->m_imgHeight);

		glBindTexture(GL_TEXTURE_2D, m_textureId[index]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if (m_image[index]->m_imgWidth == m_image[index]->m_imgHeight)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, m_image[index]->m_imgComponents, m_image[index]->m_imgWidth, m_image[index]->m_imgHeight, 0, m_image[index]->m_imgFormat, GL_UNSIGNED_BYTE, m_image[index]->m_imgData);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, m_image[index]->m_imgComponents, m_image[index]->m_imgWidth, m_image[index]->m_imgHeight, 0, m_image[index]->m_imgFormat, GL_UNSIGNED_BYTE, NULL);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_image[index]->m_imgWidth, m_image[index]->m_imgHeight, m_image[index]->m_imgFormat, GL_UNSIGNED_BYTE, m_image[index]->m_imgData);
		}
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		m_image[index]->Release();
	}
	delete[] m_image;
	m_image = NULL;
}

IE_END
