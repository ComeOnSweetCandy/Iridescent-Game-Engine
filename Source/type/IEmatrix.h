/***********************************
* name     : IEmatrix.h
* creater  : cosc
* info     : 4*4 matrix
* date     : 2016/11/22
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_MATRIX__
#define __IE_MATRIX__

#include "../core/IEobject.h"
#include "IEvector.h"

IE_BEGIN

class __IE_DLL__ IEMatrix:public IEObject
{
public:
	IEMatrix();
	IEMatrix(IEMatrix &matrix);
	IEMatrix(float matrix[4][4]);
	virtual ~IEMatrix();

public:
	void RestMatrix();

	IEMatrix operator *(const IEMatrix &matrix) const;
	IEMatrix operator *(const float matrix[4][4]) const;

private:
	float m_matrix[4][4];
};

IE_END

#endif