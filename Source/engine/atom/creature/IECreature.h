/***********************************
* name     : IECreature.h
* creater  : cosc
* info     : creature
* date     : 2017/1/4
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CREATURE__
#define __IE_CREATURE__

#include "../IEatom.h"
#include "IECreatureInfo.h"

#include "goal/IEGoalMachine.h"
#include "action/IEactionMachine.h"

IE_BEGIN

class IEText;
class IEProcessBar;

class __IE_DLL__ IECreature :public IEAtom
{
public:
	IECreature();
	virtual ~IECreature();
	virtual void Initialization(unsigned int creatureID, unsigned int creatureOrder);
	static IECreature * Create(unsigned int creatureID, unsigned int creatureOrder);

public:
	virtual void SetTranslate(const float &x, const float &y);
	virtual void SetPosition(const float &x, const float &y);
 
	IECreatureInfo * GetCreatureInfo();
	IECreatureUnit * GetCreatureUnit();
	IEActionMachine * GetActionMachine();

	//给予creature的情况反馈 与指令区分开 或者意为 通知当前creature所处于的状态
	void User();								//当前为用户控制
	void Await();								//无目标情况下的处理
	void Warning(IECreature * creature);		//警戒线视野内有enemy

	
	//给予creature的指令调用的统统为action组
	void Rest();								//action rest
	void Angry();								//action angry
	void Displacement(float x, float y);		//action displacement
	void Cured(int cureValue);
	void Damaged(int damageValue);

	void FollowEnemy();
	void FollowCreature(IECreature * creature);

protected:
	virtual void Born();
	virtual void Live();
	virtual void Die();

	virtual void TemporaryTextureEnd();

private:
	void InitUnit(unsigned int creatureID, int creatureOrder);
	void InitMachine();
	void InitCreatureTab();

	void AnalyseCommand(char * command);

	IEContainer * FindCreatureAround();				//获取周围所有的人的句柄
	void ArrangeInfo();								//处理一些 防止信息数值错误的操作

	void RunState();								//运行状态
	void RunGoal();									//运行目标
	void RunAction();								//运行动作

protected:
	IECreatureInfo * m_info;
	IECreatureUnit * m_unit;
	IEGoalMachine * m_goalMachine;
	IEActionMachine * m_actionMachine;

	IEText * m_nameDisplay;
	IEProcessBar * m_healthDisplay;
};

IE_END

#endif