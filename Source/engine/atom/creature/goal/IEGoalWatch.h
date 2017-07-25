/***********************************
* name     : IEGoalAwait.h
* creater  : cosc
* info     : single goal watch
* date     : 2017/7/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_GOAL_WATCH__
#define __IE_GOAL_WATCH__

#include "IEGoal.h"

IE_BEGIN

typedef enum __ieGoalWatchState
{
	__goal_watch_rest_state__,
	__goal_watch_angry_state__
}IEGoalWatchState;

class __IE_DLL__ IEGoalWatch :public IEGoal
{
public:
	IEGoalWatch();
	virtual ~IEGoalWatch();
	virtual void Initialization();
	static IEGoalWatch * Create();

protected:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
	bool m_watchSomething;				//�Ƿ��м��ӵ�creature �����ظ�ת��״̬
	IEGoalWatchState m_watchState;		//��ǰcreature watch״���µ�״̬
	unsigned char m_cycle;				//������� ����ÿһ֡������м�� ���Ǽ�֡����һ��
};

IE_END

#endif