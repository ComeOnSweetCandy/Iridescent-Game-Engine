/***********************************
* name     : IEElement.h
* creater  : cosc
* info     : draw element base
* date     : 2016/11/24
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ELEMENT__
#define __IE_ELEMENT__

#include "../IEnode.h"
#include "../shader/IEshader.h"

IE_BEGIN

class __IE_DLL__ IEElement :public IENode
{
public:
	IEElement();
	virtual ~IEElement();
	virtual void Initialization();
	static IEElement * Create();
	
protected:
	virtual void ChangeModelMatrix();
	virtual void RevertModelMatrix();
	virtual void DrawNode();

public:
	virtual void SetUnitPiexls(int unitPiexls);
	virtual void SetRegularization(bool regularization);
	virtual void ReckonSize();

protected:
	bool m_regularization;
	unsigned int m_unitPixels;
};

IE_END

#endif