/***********************************
* name     : IEpropsInfoManger.h
* creater  : cosc
* info     : creature
* date     : 2017/4/26
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PROPS_INFO_MANAGER__
#define __IE_PROPS_INFO_MANAGER__

#include "../../../global/IEstdafx.h"

IE_BEGIN

struct IEPropInfo
{
	int s_index;
	char s_name[64];
};

class __IE_DLL__ IEPropsInfoManager
{
public:
	IEPropsInfoManager();
	~IEPropsInfoManager();
	void Initialization();
	void Release();
	static IEPropsInfoManager * Share();

public:
	IEPropInfo& LoadPropInfo(unsigned int propInfoIndex);

private:
	void LoadPropInfos();

private:
	static IEPropsInfoManager * m_propsInfoManager;

	IEPropInfo * m_propsInfoList;
	unsigned int m_propsInfoCount;
};

IE_END

#endif