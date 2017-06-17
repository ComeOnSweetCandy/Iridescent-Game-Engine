#define __IE_DLL_EXPORTS__
#include "IEtext.h"
#include "../../type/IEbaseType.h"

IE_BEGIN

IEText::IEText()
{
	m_textAlign = __text_align_left__;
	m_defaultBackground = "texture/default/default.png";
}

IEText::~IEText()
{
	if (m_unicodeText)
	{
		delete[]m_unicodeText;
		m_unicodeText = NULL;
	}
}

void IEText::Initialization(const char * text)
{
	IESprite::Initialization(m_defaultBackground.GetString());
	setText(text);
}

IEText * IEText::Create(const char * text)
{
	IEText * sprite = new IEText();
	sprite->Initialization(text);
	return sprite;
}

void IEText::DrawNode()
{
	IESprite::DrawNode();

	if (IEFontTTF::Share()->m_charactersInfo == NULL)
	{
		//防止文字贴图未成功加载
		return;
	}

	float everyPixelLengh = ((IEBaseType<float> *)SETTING["PixelLength"])->GetData();

	float characterSize = everyPixelLengh * IEFontTTF::Share()->m_fontSize;
	int offsetBottom = IEFontTTF::Share()->m_offsetBottom;
	m_size[1] = (IEFontTTF::Share()->m_offsetBottom + IEFontTTF::Share()->m_offsetTop + 20) * everyPixelLengh;
	m_size[0] = 0.0f;

	glTranslatef(0.0f, offsetBottom * everyPixelLengh, 0.0f);
	glBindTexture(GL_TEXTURE_2D, IEFontTexture::Share()->m_textureId[0]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int index = 0; index < m_textCount; index++)
	{
		unsigned char unicodeHead = (unsigned char)IE_UNICODE_HEAD(m_unicodeText[index]);
		unsigned char unicodeTail = (unsigned char)IE_UNICODE_TAIL(m_unicodeText[index]);
		unicodeHead = 255 - unicodeHead;
		float positionU = (float)unicodeTail / 256.0f;
		float positionV = (float)unicodeHead / 256.0f;
		int characterIndex = m_unicodeText[index];
		IECharacterInfo * charactersInfo = IEFontTTF::Share()->m_charactersInfo;

		glTranslatef(charactersInfo[characterIndex].s_offsetX * everyPixelLengh, charactersInfo[characterIndex].s_offsetY * everyPixelLengh, 0.0f);

		glBegin(GL_QUADS);
		glTexCoord2f(positionU, positionV);											glVertex2f(0, 0);
		glTexCoord2f(positionU + 1.0f / 256.0f, positionV);							glVertex2f(characterSize, 0);
		glTexCoord2f(positionU + 1.0f / 256.0f, positionV + 1.0f / 256.0f);			glVertex2f(characterSize, characterSize);
		glTexCoord2f(positionU, positionV + 1.0f / 256.0f);							glVertex2f(0, characterSize);
		glEnd();

		glTranslatef(-charactersInfo[characterIndex].s_offsetX * everyPixelLengh, -charactersInfo[characterIndex].s_offsetY * everyPixelLengh, 0.0f);
		glTranslatef(charactersInfo[characterIndex].s_occupyWidth* everyPixelLengh, 0.0f, 0.0f);
		m_size[0] = m_size[0] + charactersInfo[characterIndex].s_occupyWidth * everyPixelLengh;
	}

	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glUseProgram(NULL);
}

void IEText::GBKToUnicode()
{
	if (m_unicodeText)
	{
		delete[]m_unicodeText;
		m_unicodeText = NULL;
	}

	int size = m_text.Size();
	wchar_t * unicodeText;
	int num = 0;

	unicodeText = new wchar_t[size * 2];
	num = MultiByteToWideChar(CP_ACP, 0, m_text.GetString(), -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, m_text.GetString(), -1, unicodeText, num);

	//size个文字
	m_unicodeText = (unsigned short *)unicodeText;
	for (int index = 0; index < size; index++)
	{
		if (m_unicodeText[index] != 0)
		{
			unsigned char unicodeHead = IE_UNICODE_HEAD(m_unicodeText[index]);
			unsigned char unicodeTail = IE_UNICODE_TAIL(m_unicodeText[index]);
		}
		else
		{
			size = index;
			m_textCount = size;
		}
	}
}

void CalTextWidthHieght()
{

}

void IEText::setText(const char * text)
{
	m_text = text;
	GBKToUnicode();
	ReckonTextareaSize();
}

void IEText::setAlign(IETextAlign textAlign)
{

}

void IEText::ReckonTextareaSize()
{
	float pixelLength = ((IEBaseType<float> *)SETTING["PixelLength"])->GetData();
	m_size[1] = (IEFontTTF::Share()->m_offsetBottom + IEFontTTF::Share()->m_offsetTop + 20) * pixelLength;
	m_size[0] = 0.0f;

	IECharacterInfo * charactersInfo = IEFontTTF::Share()->m_charactersInfo;
	if (charactersInfo == NULL)
	{
		return;
	}

	for (int index = 0; index < m_textCount; index++)
	{
		unsigned char unicodeHead = (unsigned char)IE_UNICODE_HEAD(m_unicodeText[index]);
		unsigned char unicodeTail = (unsigned char)IE_UNICODE_TAIL(m_unicodeText[index]);
		int characterIndex = m_unicodeText[index];
		m_size[0] = m_size[0] + charactersInfo[characterIndex].s_occupyWidth * pixelLength;
	}
}

IE_END