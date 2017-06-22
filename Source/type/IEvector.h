/***********************************
* name     : IEvector.h
* creater  : cosc
* info     : 2d vector
* date     : 2016/11/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_VECTOR__
#define __IE_VECTOR__

#include "../core/IEobject.h"

IE_BEGIN

class IEGrid;

class __IE_DLL__ IEVector:public IEObject
{
public:
	IEVector();
	IEVector(float value);
	IEVector(float x, float y);
	IEVector(IEGrid &grid);
	virtual ~IEVector();

public:
	IEVector operator +(const IEVector &vector) const;
	IEVector operator -(const IEVector &vector) const;
	IEVector operator *(const float &value) const;
	IEVector operator *(const int &value) const;
	IEVector operator *(const unsigned int &value) const;
	IEVector operator /(const int &value) const;
	IEVector operator /(const unsigned int &value) const;
	IEVector operator /(const float &value) const;
	IEVector operator /(IEVector &vector) const;
	float operator *(const IEVector &vector) const;
	float operator ^(const IEVector &vector) const;
	IEVector operator -(void) const;
	void operator =(const IEVector &vector);
	void operator =(const float &value);
	bool operator ==(const IEVector &vector);
	float& operator [](const int& value);

	//grid
	IEVector operator -(const IEGrid &grid) const;

	friend IEVector operator * (float value, const IEVector &vector);

public:
	static float CrossProduct(IEVector &x, IEVector &y);
	static float DotProduct(const IEVector &x, const IEVector &y);

	float Length() const;
	void Normalize();
	void Abs();

public:
	float m_x;
	float m_y;
};

IE_END

#endif