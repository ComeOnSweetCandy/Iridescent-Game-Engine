/***********************************
* name     : IEpathGrid.h
* creater  : cosc
* info     : path grid
* date     : 2017/4/15
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PATH_GRID__
#define __IE_PATH_GRID__

#include "../IEBlock.h"

#define PATH_PRECISION 4

IE_BEGIN

class __IE_DLL__ IEPathGrid :public IEBlock
{
public:
	IEPathGrid();
	virtual ~IEPathGrid();
	virtual void Initialization();
	static IEPathGrid * Create();

public:
	void SetGridGrid(int x, int y);
	IEGrid GetGridGrid();

	void SetTunnel(int x, int y, unsigned char tunnel);
	unsigned char GetGridTunnelPassed(int x, int y);

protected:
	virtual void DrawNode();

private:
	void ResetTunnel();

private:
	unsigned char m_tunnel[PATH_PRECISION][PATH_PRECISION];
	IEGrid m_gridGrid;
};

IE_END

#endif