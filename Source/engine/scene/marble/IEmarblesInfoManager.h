/***********************************
* name     : IEmarblesInfoManager.h
* creater  : cosc
* info     : marbles manager
* date     : 2017/5/3
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_MARBLES_INFO_MANAGER__
#define __IE_MARBLES_INFO_MANAGER__

#include "../../../global/IEstdafx.h"

IE_BEGIN

typedef struct
{
	unsigned int _MarbleID;
	unsigned char _BodyC;
	unsigned char _BorderC;
	unsigned char _CornerC;
	char _MarbleName[64];
}IEMarbleInfo;

class IEMarblesInfoManager
{
public:
	IEMarblesInfoManager();
	virtual ~IEMarblesInfoManager();
	virtual void Initialization();
	virtual void Release();
	static IEMarblesInfoManager * Share();

public:
	IEMarbleInfo * GetMarblesInfoList();
	unsigned int GetMarblesInfoCount();

private:
	void LoadMarblesInfo();
	void SaveMarblesInfo();

private:
	static IEMarblesInfoManager * m_staticBarblesManager;

	IEMarbleInfo * m_marblesInfoList;
	unsigned int m_marblesInfoCount;
};

IE_END

#endif