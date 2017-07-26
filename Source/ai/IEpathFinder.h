/***********************************
* name     : IEPathFinder.h
* creater  : cosc
* info     : find path
* date     : 2017/3/15
* version  : 1.1
* remark   : there are more things i should do. base on a*.
************************************/

#ifndef __IE_PATH_FINDER__
#define __IE_PATH_FINDER__

#include "../engine/atom/creature/IECreature.h"

IE_BEGIN

class IEPathArea;
class IETerrainArea;
class IETerrain;

class __IE_DLL__ IEPathNode :public IEObject
{
public:
	IEPathNode(){};
	virtual ~IEPathNode(){};

public:
	IEGrid m_grid;
	IEGrid m_tunnel;
	IEPathNode * m_parentPathNode;
	int m_estimate;
	int m_pass;
	int m_last;
};

class __IE_DLL__ IEPathFinder :public IEObject
{
public:
	IEPathFinder();
	virtual ~IEPathFinder();
	virtual void Initialization(IEPathArea * path);
	static IEPathFinder * Create(IEPathArea * path);

public:
	void SetPath(IEPathArea * path);
	IEArray * FindPaths(IEGrid staGrid, IEGrid staTunnel, IEGrid endGrid, IEGrid endTunnel);
	IEArray * FindPath(IEPhysicNode * physicNode, IEVector staPosition, IEVector endPosition);

	bool CheckVolumn(IEGrid curGrid, IEGrid curTunnel);
	bool InVolumn(float radius,IEVector center, IEGrid grid, IEGrid tunnel);

private:
	int EstimateStraightDistance(IEGrid curGrid, IEGrid curTunnel, IEGrid endGrid, IEGrid endTunnel);
	IEPathNode * FindNodeInActiveList(IEGrid grid, IEGrid tunnel);
	IEPathNode * FindNodeInCloseList(IEGrid grid, IEGrid tunnel);

	void HandleGrid(IEVector staPosition, IEVector endPosition, IEGrid &startGrid, IEGrid &startTunnel, IEGrid &endGrid, IEGrid &endTunnel);

private:
	IEPathArea * m_path;
	IEArray * m_activeList;
	IEArray * m_closeList;
	IEArray * m_list;

	IEPhysicNode * m_roadPhysicNode;
};

IE_END

#endif