#define __IE_DLL_EXPORTS__
#include "IEshader.h"

IE_BEGIN

#define MAX_SHADER_INFO_LOG_SIZE 2048

IEShader::IEShader()
{
	m_glslFile = IEString("");
	m_vsText = NULL;
	m_fsText = NULL;
}

IEShader::IEShader(const char *file)
{
	m_glslFile = file;
	m_vsText = NULL;
	m_fsText = NULL;
}

IEShader::IEShader(IEString &file)
{
	m_glslFile = file;
	m_vsText = NULL;
	m_fsText = NULL;
}

IEShader::~IEShader()
{

}

void IEShader::Initialization()
{
	LoadShaderText();
	CreateShader();
}

IEShader * IEShader::Create(IEString &file)
{
	IEObject * obj = RESOURCE[(char *)(file.GetString())];
	if (obj == NULL)
	{
		IEShader * object = new IEShader(file);
		object->Initialization();
		RESOURCE[(char *)(file.GetString())] = (IEObject *)object;
		return object;
	}
	else
	{
		return (IEShader *)obj;
	}
}

IEShader * IEShader::Create(const char *file)
{
	IEObject * obj = RESOURCE[file];
	if (obj == NULL)
	{
		IEShader * object = new IEShader(file);
		object->Initialization();
		RESOURCE[file] = (IEObject *)object;
		return object;
	}
	else
	{
		return (IEShader *)obj;
	}
}

void IEShader::ResetShader()
{
	LoadShaderText();
	CreateShader();
}

void IEShader::LoadShaderText()
{
	IEString * texturesFileBaseDir = (IEString *)(SETTING["ShaderDir"]);

	IEString body = m_glslFile.GetFileNameBody();
	IEString vsFile = *texturesFileBaseDir + body + ".vs.glsl";
	IEString fsFile = *texturesFileBaseDir + body + ".fs.glsl";

	int shaderLength = 0;
	FILE *vsFp = fopen(vsFile.GetString(), "r");
	if (vsFp != NULL)
	{
		while (fgetc(vsFp) != EOF)
		{
			shaderLength++;
		}
		rewind(vsFp);
		m_vsText = (char *)malloc(shaderLength + 1);
		if (m_vsText != NULL)
		{
			fread(m_vsText, 1, shaderLength, vsFp);
		}
		m_vsText[shaderLength] = '\0';
		fclose(vsFp);
	}

	shaderLength = 0;
	FILE *fsFp = fopen(fsFile.GetString(), "r");
	if (fsFp != NULL)
	{
		while (fgetc(fsFp) != EOF)
		{
			shaderLength++;
		}
		rewind(fsFp);
		m_fsText = (char *)malloc(shaderLength + 1);
		if (m_fsText != NULL)
		{
			fread(m_fsText, 1, shaderLength, fsFp);
		}
		m_fsText[shaderLength] = '\0';
		fclose(fsFp);
	}
}

void IEShader::CreateShader()
{
	m_fShader = glCreateShader(GL_FRAGMENT_SHADER);
	m_vShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vsStringPtr[1];
	const GLchar *fsStringPtr[1];
	int success;
	vsStringPtr[0] = m_vsText;
	fsStringPtr[0] = m_fsText;

	glShaderSource(m_fShader, 1, fsStringPtr, NULL);
	glShaderSource(m_vShader, 1, vsStringPtr, NULL);


	glCompileShader(m_vShader);
	glGetShaderiv(m_vShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[MAX_SHADER_INFO_LOG_SIZE];
		glGetShaderInfoLog(m_vShader, MAX_SHADER_INFO_LOG_SIZE, NULL, infoLog);
		printf("%s\n", infoLog);
	}
	glCompileShader(m_fShader);
	glGetShaderiv(m_fShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[MAX_SHADER_INFO_LOG_SIZE];
		glGetShaderInfoLog(m_fShader, MAX_SHADER_INFO_LOG_SIZE, NULL, infoLog);
		printf("%s\n", infoLog);
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_vShader);
	glAttachShader(m_shaderProgram, m_fShader);
	//glDetachShader(m_shaderProgram, m_vShader);
	//glDetachShader(m_shaderProgram, m_fShader);
	glLinkProgram(m_shaderProgram);
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[MAX_SHADER_INFO_LOG_SIZE];
		glGetProgramInfoLog(m_shaderProgram, MAX_SHADER_INFO_LOG_SIZE, NULL, infoLog);
		printf("%s\n", infoLog);
	}

	free(m_vsText);
	free(m_fsText);
	glUseProgram(NULL);
}

unsigned int &IEShader::GetShaderProgram()
{
	return m_shaderProgram;
}

IE_END
