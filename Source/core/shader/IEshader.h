/***********************************
* name     : IEshader.h
* creater  : cosc
* info     : shader manager
* date     : 2016/11/26
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_SHADER__
#define __IE_SHADER__

#include "../../global/IEstdafx.h"
#include "../../type/IEstring.h"
#include "../container/IEdictionary.h"

IE_BEGIN

class __IE_DLL__ IEShader:public IEObject
{
public:
	IEShader();
	IEShader(const char *file);
	IEShader(IEString &file);
	virtual ~IEShader();
	void Initialization();
	static IEShader * Create(IEString &file);
	static IEShader * Create(const char *file);

public:
	void ResetShader();
	void LoadShaderText();
	void CreateShader();
	unsigned int & GetShaderProgram();

private:
	IEString m_glslFile;
	char * m_vsText;
	char * m_fsText;

	unsigned int m_vShader;
	unsigned int m_fShader;
	unsigned int m_shaderProgram;
};

IE_END

#endif
