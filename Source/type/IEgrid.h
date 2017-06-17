/***********************************
* name     : IEgrid.h
* creater  : cosc
* info     : int vector
* date     : 2016/11/25
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_GRIE__
#define __IE_GRIE__

#include "../core/IEobject.h"

IE_BEGIN

class IEVector;

class __IE_DLL__ IEGrid :public IEObject
{
public:
	IEGrid();
	IEGrid(IEGrid &grid);
	IEGrid(IEVector &vector);
	IEGrid(int x, int y);
	IEGrid(int value);
	virtual ~IEGrid();
	virtual void Initialization();
	static IEGrid * Create(int x, int y);

public:
	IEGrid operator +(IEGrid &grid);
	IEGrid operator -(IEGrid &grid);
	IEGrid operator *(int value);
	IEVector operator *(float value);
	IEGrid operator /(int value);
	IEGrid operator %(int value);
	bool operator ==(IEGrid &grid);
	bool operator !=(IEGrid &grid);
	IEVector operator +(IEVector &vector);

	IEGrid Absolute();
	void Abs();

public:
	int m_x;
	int m_y;
};

IE_END

#endif