#define __IE_DLL_EXPORTS__
#include "IEfontTTF.h"

IE_BEGIN

IEFontTTF * IEFontTTF::m_fontTTF = NULL;

IEFontTTF::IEFontTTF()
{
	m_fontSize = 14;
	m_charactersInfo = NULL;
}

IEFontTTF::~IEFontTTF()
{
	FT_Done_Face(m_fontFace);
	FT_Done_FreeType(m_library);

	delete[]m_displayStringUnicode;
	delete[]m_charactersInfo;
}

IEFontTTF * IEFontTTF::Create(const char * string, const char * fontName, unsigned int fontSize)
{
	if (m_fontTTF == NULL)
	{
		m_fontTTF = new IEFontTTF();
		m_fontTTF->Initialization(string, fontName, fontSize);
	}
	return m_fontTTF;
}

IEFontTTF * IEFontTTF::Share()
{
	if (m_fontTTF == NULL)
	{
		m_fontTTF = new IEFontTTF();
	}
	return m_fontTTF;
}

void IEFontTTF::Initialization(const char * string, const char * fontName, unsigned int fontSize)
{
	m_displayString = string;
	m_fontName = fontName;
	m_fontSize = fontSize;

	if (FT_Init_FreeType(&m_library))
	{
		printf("FT_Init_FreeType failed\n");
	}
	if (FT_New_Face(m_library, fontName, 0, &m_fontFace))
	{
		printf("FT_New_Face failed (there is probably a problem with your font file\n");
	}
	//FT_Set_Char_Size(m_fontFace, fontSize << 6, fontSize << 6, 93, 93);
	FT_Set_Pixel_Sizes(m_fontFace, 0, fontSize);

	GBKToUnicode();
}

void IEFontTTF::ReadFontInfoFile()
{
	FILE * f = fopen("../Debug/data/font/font_0.data", "rb");
	int count = 256 * 256;
	m_charactersInfo = new IECharacterInfo[count];
	fread(m_charactersInfo, sizeof(IECharacterInfo), count, f);
	fread(&m_fontSize, 4, 1, f);
	fread(&m_offsetTop, 4, 1, f);
	fread(&m_offsetBottom, 4, 1, f);
	fclose(f);
}

void IEFontTTF::WriteFontInfoFile()
{
	char * infoFilePosition = "../Debug/data/font/font_0.data";
	FILE * f = fopen(infoFilePosition, "wb");
	int count = 256 * 256;
	fwrite(m_charactersInfo, sizeof(IECharacterInfo), count, f);
	fwrite(&m_fontSize, 4, 1, f);
	fwrite(&m_offsetTop, 4, 1, f);
	fwrite(&m_offsetBottom, 4, 1, f);
	fclose(f);
}

void IEFontTTF::GBKToUnicode()
{
	int size = m_displayString.Size();
	m_displayStringUnicode = new wchar_t[size * 2];
	int num = 0;
	size_t readlen = 0;

	num = MultiByteToWideChar(CP_ACP, 0, m_displayString.GetString(), -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, m_displayString.GetString(), -1, m_displayStringUnicode, num);
}

void IEFontTTF::SetDisplayString(char *str)
{
	m_displayString = str;
}

void IEFontTTF::DrawNode()
{
	DrawTTFText();
}

void IEFontTTF::DrawTTFText()
{
	glPushAttrib(GL_TRANSFORM_BIT);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(viewport[0], viewport[2], viewport[1]-100, viewport[3]);
	glPopAttrib();

	float h = m_fontSize;
	const char *start_line = (char *)m_displayStringUnicode;
	const char *c = (char *)m_displayStringUnicode;
	unsigned int len = 0;
	while (*c || *(c + 1))
	{
		len++;
		c = c + 2;
	}

	IEString preString = "";
	if (start_line)
	{
		for (const char *n = start_line; n < c; n++)
		{
			preString = preString + *n;
		}
	}

	glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float modelview_matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

	glPushMatrix();
	glLoadIdentity();
	glMultMatrixf(modelview_matrix);

	for (unsigned int index = 0; index < len*2; index++)
	{
		unsigned char a = ((unsigned char *)m_displayStringUnicode)[index];
		unsigned char b = ((unsigned char *)m_displayStringUnicode)[index + 1];

		DrawWord(b * 256 + a, index);
		index++;
	}
	glPopMatrix();
	glPopAttrib();

	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
}

void IEFontTTF::DrawWord(unsigned short int ch, int index)
{
	if (FT_Load_Glyph(m_fontFace, FT_Get_Char_Index(m_fontFace, ch), FT_LOAD_DEFAULT))
	{
		printf("FT_Load_Glyph failed");
	}
	FT_Glyph glyph;
	if (FT_Get_Glyph(m_fontFace->glyph, &glyph))
	{
		printf("FT_Get_Glyph failed\n");
	}
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	int width = next_p2(bitmap.width);
	int height = next_p2(bitmap.rows);
	GLubyte* expanded_data = new GLubyte[width * height];
	memset(expanded_data, 0, width*height);

	for (int j = 0; j <height; j++) 
	{
		for (int i = 0; i < width; i++)
		{
			expanded_data[(i + j*width)] = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];
		}
	}

	GLuint *tex = new GLuint[1];
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, expanded_data);

	delete[] expanded_data;

	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glPushMatrix();
	glTranslatef(bitmap_glyph->left, 0, 0);
	glTranslatef(0, bitmap_glyph->top - bitmap.rows, 0);

	float x = (float)bitmap.width / (float)width;
	float y = (float)bitmap.rows / (float)height;

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex2f(0, bitmap.rows);
	glTexCoord2d(0, y); glVertex2f(0, 0);
	glTexCoord2d(x, y); glVertex2f(bitmap.width, 0);
	glTexCoord2d(x, 0); glVertex2f(bitmap.width, bitmap.rows);
	glEnd();
	glPopMatrix();
	glTranslatef(m_fontFace->glyph->advance.x >> 6, 0, 0);
}

void * IEFontTTF::GetWordInfo(unsigned short int ch, int &wwidth, int &hheight, int &offsetX, int &offsetY, int &occupyWidth, void * data)
{
	if (FT_Load_Glyph(m_fontFace, FT_Get_Char_Index(m_fontFace, ch), FT_LOAD_DEFAULT))
	{
		printf("FT_Load_Glyph failed");
	}
	FT_Glyph glyph;
	if (FT_Get_Glyph(m_fontFace->glyph, &glyph))
	{
		printf("FT_Get_Glyph failed\n");
	}
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	wwidth = bitmap.width;
	hheight = bitmap.rows;
	offsetX = bitmap_glyph->left;
	offsetY = bitmap_glyph->top - bitmap.rows;
	occupyWidth = m_fontFace->glyph->advance.x >> 6;

	if (occupyWidth <= wwidth)
	{
		occupyWidth = occupyWidth + 1;
	}

	return  bitmap.buffer;
}

void IEFontTTF::WriteFontFile(unsigned short fontNumber, int everyFile, char * filePosition, char *infoFilePosition)
{
	if (fontNumber == 0)
	{
		return;
	}

	int fileCount = fontNumber / (everyFile*everyFile);
	int fileCountExtra = fontNumber % (everyFile*everyFile);
	m_charactersInfo = new IECharacterInfo[everyFile*everyFile];

	if (fileCountExtra != 0)
	{
		fileCount++;
	}

	IEString fileName = filePosition;
	int fileWidth = m_fontSize * everyFile;
	int fileHeight = m_fontSize * everyFile;
	int fileSize = fileWidth * fileHeight * 4;
	m_offsetTop = 0;
	m_offsetBottom = 0;
	void * data = (GLubyte*)malloc(fileSize * sizeof(GLubyte));
	memset(data, 0, fileSize);

	for (int row = 0; row < everyFile; row++)
	{
		for (int column = 0; column < everyFile; column++)
		{
			int ch = row * everyFile + column;
			int characterWidth;
			int characterHeight;
			int offsetX = 0;
			int offsetY = 0;
			int occupyWidth = 0;
			void * ddd = NULL;
			ddd = GetWordInfo(ch, characterWidth, characterHeight, offsetX, offsetY, occupyWidth, NULL);
			m_charactersInfo[ch].s_offsetX = offsetX;
			m_charactersInfo[ch].s_offsetY = offsetY;
			m_charactersInfo[ch].s_occupyWidth = occupyWidth;

			if (offsetY >= 0)
			{
				int o = characterHeight + offsetY - m_fontSize;
				m_offsetTop = m_offsetTop > o ? m_offsetTop : o;
			}
			else
			{
				int o = -offsetY;
				m_offsetBottom = m_offsetBottom>o ? m_offsetBottom : o;
			}

			for (int pixelRow = 0; pixelRow < m_fontSize; pixelRow++)
			{
				for (int pixelColumn = 0; pixelColumn < m_fontSize; pixelColumn++)
				{
					int offsetRow = m_fontSize - characterHeight;

					if (pixelColumn < characterWidth && pixelRow <(characterHeight + offsetRow) && pixelRow >= offsetRow)
					{
						int zindex = (everyFile - row - 1)*everyFile * m_fontSize * m_fontSize + (m_fontSize - pixelRow - 1) * m_fontSize * everyFile + (column * m_fontSize + pixelColumn);
						zindex = zindex * 4;

						int color = *(((unsigned char *)ddd + (pixelRow - offsetRow)* characterWidth + pixelColumn));

						*((unsigned char *)data + zindex + 0) = color;
						*((unsigned char *)data + zindex + 1) = color;
						*((unsigned char *)data + zindex + 2) = color;
						*((unsigned char *)data + zindex + 3) = color > 0 ? 255 : 0;
					}
				}
			}
		}
	}

	IEFontTTF::WriteFontInfoFile();
	IEImage::WriteTGA(fileName.GetString(), fileWidth, fileHeight, (const byte *)data);

	//∂¡»°
	ReadFontFile("../Debug/data/font/font_0.tga", "../Debug/data/font/font_0.data");
}

void IEFontTTF::ReadFontFile(char * filePosition, char *infoFilePosition)
{
	IEFontTexture::Create("../Debug/data/font/font_0.tga");
	ReadFontInfoFile();
}

int IEFontTTF::next_p2(int a)
{
	int rval = 1;
	while (rval<a) rval <<= 1;
	return rval;
}

IE_END