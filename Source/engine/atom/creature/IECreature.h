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
	virtual void SetTranslate(const float &x, const float &y);		//���õ�ǰλ��

	IECreatureEntry * GetCreatureEntry();
	IECreatureUnit * GetCreatureUnit();

	IEGoalMachine * GetGoalMachine();
	IEActionMachine * GetActionMachine();
	IEStateMachine * GetStateMachine();

	//����creature��������� ��ָ�����ֿ� ������Ϊ ֪ͨ��ǰcreature�����ڵ�״̬ ֪ͨ���͵ķ���
	virtual void Born();
	virtual void Live();
	virtual void Die();

	void User();								//��ǰΪ�û�����
	void Await();								//��Ŀ������µĴ���
	void Warning(IECreature * creature);		//��������Ұ����enemy
	
	//����creature��ָ����õ�ͳͳΪaction��
	void Rest();								//action rest
	void Angry();								//action angry
	void Displacement(float x, float y);		//action displacement
	void Cured(int cureValue);					//
	void Damaged(int damageValue);				//

protected:
	void RunGoal();									//����Ŀ��
	void RunAction();								//���ж���
	void RunState();								//����״̬

	void ArrangeInfo();								//����һЩ ��ֹ��Ϣ��ֵ����Ĳ���

private:
	void InitUnit(unsigned int creatureID, int creatureOrder);		//��ʼ����������
	void InitMachine();												//��ʼ������ ���ƻ�
	void InitCreatureTab();											//��ʼ����ʾ�����

protected:
	IECreatureEntry * _Entry;
	IECreatureUnit * _Unit;

	//����������
	IEGoalMachine * m_goalMachine;
	IEActionMachine * m_actionMachine;
	IEStateMachine * m_stateMachine;

	//��ʾ���
	IEText * m_nameDisplay;
	IEProcessBar * m_healthDisplay;
};

extern "C" __IE_DLL__ bool __CreatureOpposite(IECreature * creatureA, IECreature * creatureB);
extern "C" __IE_DLL__ IEContainer * FindCreaturesAround(IECreature * creature);
extern "C" __IE_DLL__ IEContainer * FindAllCreatures(IECreature * creature);

IE_END

#endif