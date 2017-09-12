#define __IE_DLL_EXPORTS__
#include "IETorch.h"

IE_BEGIN

#define number 5
float vertexs[number][2] = { 0.5f, 1.5f, 1.0f, 1.0f, 3.0f, 1.0f, 2.0f, 3.0f, 1.0f, 2.5f };
bool res = true;
int minIndex, maxIndex;

float vffunction(float x0, float y0, float x1, float y1, float x, float y)
{
	float finalValue = (y - y0)*(x1 - x0) - (x - x0)*(y1 - y0);
	return finalValue;
}

bool ffunction(float x0, float y0, float x1, float y1, float x, float y)
{
	float finalValue = (y - y0)*(x1 - x0) - (x - x0)*(y1 - y0);
	return finalValue >= 0.0f;
}

IETorch::IETorch()
{
	_curMulti = 1.0f;
	_value = 1;
	_speed = 0.001f;
}

IETorch::~IETorch()
{

}

void IETorch::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);

	SetProperty();

	///////////////////////
	minIndex = maxIndex = 0;

	for (unsigned int index = 1; index < number; index++)
	{
		//��������
		float res1 = vertexs[index][1] * vertexs[minIndex][0] - vertexs[index][0] * vertexs[minIndex][1];
		float res2 = vertexs[index][1] * vertexs[maxIndex][0] - vertexs[index][0] * vertexs[maxIndex][1];

		if (res1 < 0)
		{
			minIndex = index;
		}
		if (res2 > 0)
		{
			maxIndex = index;
		}
	}

	if (maxIndex < minIndex)
	{
		int z = maxIndex;
		maxIndex = minIndex;
		minIndex = z;
	}

	//�������ж� �Ǵ�minIndex->maxIndex ����maxIndex->minIndex
	//ֻ��Ҫ�����һ�� ��minIndex �ҷ�maxIndex
	int judgeIndex = minIndex + 1;

	//(0,0) (minIndex) (maxIndex) ��Χ�ɵ������� (judgeIndex)�Ƿ�������
	bool res1 = ffunction(0.0f, 0.0f, vertexs[minIndex][0], vertexs[minIndex][1], vertexs[judgeIndex][0], vertexs[judgeIndex][1]);
	bool res2 = ffunction(vertexs[minIndex][0], vertexs[minIndex][1], vertexs[maxIndex][0], vertexs[maxIndex][1], vertexs[judgeIndex][0], vertexs[judgeIndex][1]);
	bool res3 = ffunction(vertexs[maxIndex][0], vertexs[maxIndex][1], 0.0f, 0.0f, vertexs[judgeIndex][0], vertexs[judgeIndex][1]);
	if (res1 == res2 && res2 == res3)
	{
		res = true;
	}
	else
	{
		res = false;
		judgeIndex = minIndex--;
	}

	//���ʱ�� ��������һ���� 
	float randomPoint[2] = { 4.0f, 4.0f };

	float res11 = vffunction(0.0f, 0.0f, vertexs[minIndex][0], vertexs[minIndex][1], randomPoint[0], randomPoint[1]);
	float res12 = vffunction(vertexs[maxIndex][0], vertexs[maxIndex][1], 0.0f, 0.0f, randomPoint[0], randomPoint[1]);

	if (res11*res12 > 0.0f)
	{
		//�ڷ�Χ��
		printf("yes.\n");
	}
	else
	{
		//���ڷ�Χ��
		printf("no.\n");
	}
}

IETorch * IETorch::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IETorch * thing = new IETorch();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IETorch::Update()
{
	//����Ч��
	static float maxMulti = 1.1f;
	static float minMulti = 0.9f;

	m_curIntension = m_intension * _curMulti;
	_curMulti = _curMulti + _speed * _value;

	if (_curMulti > maxMulti)
	{
		_value = -1;
	}
	else if (_curMulti < minMulti)
	{
		_value = 1;
	}
}

void IETorch::DrawNode()
{
	DrawFire();
	DrawLight();

	glColor3f(1.0f, 1.0f, 1.0f);
	glShadeModel(GL_FLAT);
	glBegin(GL_POLYGON);
	for (int index = 0; index < number; index++)
	{
		if (res)
		{
			if (index>minIndex && index <= maxIndex)
			{
				glColor3f(0.0f, 1.0f, 0.0f);
			}
			else
			{
				glColor3f(1.0f, 0.0f, 0.0f);
			}
		}
		else
		{
			if (index <= minIndex || index > maxIndex)
			{
				glColor3f(0.0f, 1.0f, 0.0f);
			}
			else
			{
				glColor3f(1.0f, 0.0f, 0.0f);
			}
		}

		glVertex2f(vertexs[index][0], vertexs[index][1]);
	}
	glEnd();
}

void IETorch::DrawLight()
{
	glPushMatrix();
	//glTranslatef(m_size[0] / 2, m_size[1] / 2, 0.0f);

	glDisable(GL_TEXTURE);
	if (m_shader)
	{
		glUseProgram(m_shader->GetShaderProgram());

		GLint radius = glGetUniformLocation(m_shader->GetShaderProgram(), "radius");
		glUniform1f(radius, m_distance);

		GLint intension = glGetUniformLocation(m_shader->GetShaderProgram(), "intension");
		glUniform1f(intension, m_curIntension);

		GLint baseLight = glGetUniformLocation(m_shader->GetShaderProgram(), "baseLight");
		glUniform1f(baseLight, m_baseLight);

		//�������Ķ��㴫�͹�ȥ
		//float * vectors = (float *)vertexs;
		//GLint wallVectors = glGetUniformLocation(m_shader->GetShaderProgram(), "wallVectors");
		//glUniform2fv(wallVectors, 5, vectors);

		GLint minPoint = glGetUniformLocation(m_shader->GetShaderProgram(), "minPoint");
		glUniform2fv(minPoint, 1, vertexs[minIndex]);

		GLint maxPoint = glGetUniformLocation(m_shader->GetShaderProgram(), "maxPoint");
		glUniform2fv(maxPoint, 1, vertexs[maxIndex]);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glColor4f(m_lightColor.m_r, m_lightColor.m_g, m_lightColor.m_b, m_lightColor.m_a);
	glBegin(GL_QUADS);
	glVertex2f(-m_distance * 2, -m_distance * 2);
	glVertex2f(m_distance * 2, -m_distance * 2);
	glVertex2f(m_distance * 2, m_distance * 2);
	glVertex2f(-m_distance * 2, m_distance * 2);
	glEnd();

	glDisable(GL_BLEND);
	glUseProgram(NULL);

	glPopMatrix();
}

void IETorch::DrawFire()
{
	//if (m_shader)
	//{
	//	glUseProgram(m_shader->GetShaderProgram());
	//}

	//static float drawX, drawY;		//���ն�����Ƶķ����
	//drawX = m_drawDirection[0] ? 0 : m_size[0];
	//drawY = m_drawDirection[1] ? 0 : m_size[1];

	//glBindTexture(GL_TEXTURE_2D, m_textureUnit->_TextureID);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glColor4f(m_backColor[0], m_backColor[1], m_backColor[2], m_backColor[3]);
	//glBegin(GL_QUADS);
	////glTexCoord2f(m_textureUnit->_BeginX, m_textureUnit->_BeginY); glVertex2f(0, 0);
	////glTexCoord2f(m_textureUnit->_EndX, m_textureUnit->_BeginY); glVertex2f(m_size[0], 0);
	////glTexCoord2f(m_textureUnit->_EndX, m_textureUnit->_EndY); glVertex2f(m_size[0], m_size[1]);
	////glTexCoord2f(m_textureUnit->_BeginX, m_textureUnit->_EndY); glVertex2f(0, m_size[1]);

	//glTexCoord2f(m_textureUnit->_BeginX, m_textureUnit->_BeginY); glVertex2f(drawX, drawY);
	//glTexCoord2f(m_textureUnit->_EndX, m_textureUnit->_BeginY); glVertex2f(m_size[0] - drawX, drawY);
	//glTexCoord2f(m_textureUnit->_EndX, m_textureUnit->_EndY); glVertex2f(m_size[0] - drawX, m_size[1] - drawY);
	//glTexCoord2f(m_textureUnit->_BeginX, m_textureUnit->_EndY); glVertex2f(drawX, m_size[1] - drawY);
	//glEnd();

	//glDisable(GL_BLEND);
	//glBindTexture(GL_TEXTURE_2D, NULL);
}

void IETorch::SetProperty()
{
	//��ȡshader Ȼ�����
	IEShader * shader = IEShader::Create(m_XML->FindChild("script")->ValueString());
	IENode::AttachShader(shader);

	//��ȡ��������
	m_distance = m_XML->FindChild("property")->FindChild("distance")->ValueFloat();
	m_baseLight = m_XML->FindChild("property")->FindChild("baseLight")->ValueFloat();
	m_intension = m_XML->FindChild("property")->FindChild("intension")->ValueFloat();

	IEString * colorString = m_XML->FindChild("property")->FindChild("intension")->Value();
	m_lightColor = IEColor(1.0f, 0.0f, 0.0f, 1.0f);
}

IE_END