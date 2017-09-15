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

#include "../IEAtom.h"

#include "IECreatureList.h"
#include "goal/IEGoalMachine.h"
#include "action/IEactionMachine.h"
#include "state/IEStateMachine.h"

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
	virtual void SetTranslate(const float &x, const float &y);		//设置当前位置

	IECreatureEntry * GetCreatureEntry();
	IECreatureUnit * GetCreatureUnit();

	IEGoalMachine * GetGoalMachine();
	IEActionMachine * GetActionMachine();
	IEStateMachine * GetStateMachine();

	//给予creature的情况反馈 与指令区分开 或者意为 通知当前creature所处于的状态 通知类型的反馈
	virtual void Born();
	virtual void Live();
	virtual void Die();

	void User();								//当前为用户控制
	void Await();								//无目标情况下的处理
	void Warning(IECreature * creature);		//警戒线视野内有enemy
	
	//给予creature的指令调用的统统为action组
	void Rest();								//action rest
	void Angry();								//action angry
	void Displacement(float x, float y);		//action displacement
	void Cured(int cureValue);					//
	void Damaged(int damageValue);				//

protected:
	void RunGoal();									//运行目标
	void RunAction();								//运行动作
	void RunState();								//运行状态

	void ArrangeInfo();								//处理一些 防止信息数值错误的操作

private:
	void InitUnit(unsigned int creatureID, int creatureOrder);		//初始化自身数据
	void InitMachine();												//初始化各种 控制机
	void InitCreatureTab();											//初始化显示的面板

protected:
	IECreatureEntry * _Entry;
	IECreatureUnit * _Unit;

	//三个控制器
	IEGoalMachine * m_goalMachine;
	IEActionMachine * m_actionMachine;
	IEStateMachine * m_stateMachine;

	//显示面板
	IEText * m_nameDisplay;
	IEProcessBar * m_healthDisplay;
};

extern "C" __IE_DLL__ bool __CreatureOpposite(IECreature * creatureA, IECreature * creatureB);
extern "C" __IE_DLL__ IEContainer * FindCreaturesAround(IECreature * creature);
extern "C" __IE_DLL__ IEContainer * FindAllCreatures(IECreature * creature);

IE_END

#endif