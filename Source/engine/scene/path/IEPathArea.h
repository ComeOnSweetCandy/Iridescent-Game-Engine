/***********************************
* name     : IEPathArea.h
* creater  : cosc
* info     : path area
* date     : 2017/4/15
* version  : 1.0
* remark   : path area which binded so much road.
************************************/

#ifndef __IE_PATH_AREA__
#define __IE_PATH_AREA__

#include "../IEArea.h"
#include "IEPathChunk.h"

IE_BEGIN

class IEPhysicNode;

class __IE_DLL__ IEPathArea :public IEArea
{
public:
	IEPathArea();
	virtual ~IEPathArea();
	virtual void Initialization(IEMap * map, int halfViewBlocks, int blockSize);
	static IEPathArea * Create(IEMap * map, int halfViewBlocks, int blockSize);

public:
	void ReckonAddPath(IEPhysicNode * physicNode);				//����������physicNode��ռ�ݵ�ͨ��
	void ReckonDelPath(IEPhysicNode * physicNode);				//����ȥ����physicNode��ռ�ݵ�ͨ��

	void ReckonPhysicNodeDot(IEPhysicNode * physicNode, IEGrid curGrid, IEGrid curTunnelGrid);	//����õ��Ƿ����б��� �ҽ���ͨ������
	bool ReckonDotInPhysicNode(IEPhysicNode * physicNode, IEVector position);					//�жϵ��Ƿ���physicNode��

protected:
	virtual void Visit();

	virtual IEChunk * CreateChunk();

private:
	IEArray * m_list;

	friend class IEMap;
};

IE_END

#endif