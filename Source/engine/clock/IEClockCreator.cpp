#define __IE_DLL_EXPORTS__
#include "IEClockCreator.h"

#include "IETimeClock.h"
#include "IECountClock.h"

IE_BEGIN

IEClock * CreateClock(IEClockType clockType, int param)
{
	IEClock * clock = CreateClockByType(clockType, param);

	return clock;
}

IEClock * CreateClockByType(IEClockType clockType, int param)
{
	switch (clockType)
	{
	case __clock_none_type__:
		return NULL;
		break;
	case __clock_time_type__:
		return IETimeClock::Create(param);
		break;
	case __clock_count_type__:
		return IECountClock::Create(param);
		break;
	default:
		return NULL;
		break;
	}
}

IE_END