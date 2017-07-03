#define __IE_DLL_EXPORTS__
#include "IEJoint.h"

#include "IEthingsInfoManager.h"

IE_BEGIN

#define __IE_INIT_ARRAY__(__array__,__count__,__value__)\
	for (int __array__##index = 0; __array__##index < __count__; __array__##index++){\
		__array__[__array__##index]=__value__;\
	}

IEJoint::IEJoint()
{
	__IE_INIT_ARRAY__(m_round, 4, false);
	__IE_INIT_ARRAY__(m_topBorder, 4, NULL);

	m_topBackground = NULL;
}

IEJoint::~IEJoint()
{

}

void IEJoint::Initialization(unsigned int thingID)
{
	IEThing::Initialization(thingID);
}

IEJoint * IEJoint::Create(unsigned int thingID)
{
	return NULL;
}

void IEJoint::SetRound(unsigned char roundIndex, unsigned int thingID)
{
	if (m_thingID == thingID)
	{
		//如果两者的thingID相同 才会继续下一步的步骤
		unsigned char index = (roundIndex + 2) % 4;

		m_round[index] = true;
	}
}

void IEJoint::BuildTopSprite(unsigned int thingID)
{
	IEAdorningInfo * infos = IEAdorningsInfoManager::Share()->GetAdorningsInfoList();
	unsigned int count = IEAdorningsInfoManager::Share()->GetAdorningsInfoCount();

	IEString backName = IEString(infos[thingID]._ThingName) + "_back";
	IEString borderName = IEString(infos[thingID]._ThingName) + "_border";

	m_topBackground = IESprite::Create(backName.GetString());

	for (unsigned char index = 0; index < 4; index++)
	{
		m_topBorder[index] = IESprite::Create(borderName.GetString());
	}
	
	

}

IE_END