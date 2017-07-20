/***********************************
* name     : IECreaturesInfoManager.h
* creater  : cosc
* info     : all creatures manager
* date     : 2017/2/15
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CREATURES_INFO_MANAGER__
#define __IE_CREATURES_INFO_MANAGER__

#include "IECreature.h"

IE_BEGIN

class IECreaturesInfoManager
{
public:
	IECreaturesInfoManager();
	virtual ~IECreaturesInfoManager();
	virtual void Initialization();
	virtual void Release();
	static IECreaturesInfoManager * Share();

public:
	void LoadCreaturesInfo();
	void SaveCreaturesInfo();

private:
	static IECreaturesInfoManager * m_staticCreaturesManager;

	IECreatureInfo * m_creaturesInfoList;
	unsigned int m_creaturesInfoCount;

	friend class IECreature;
};

IE_END

#endif