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

	//����creature��������� ��ָ�����ֿ� ������Ϊ ֪ͨ��ǰcreature�����ڵ�״̬
	void User();								//��ǰΪ�û�����
	void Await();								//��Ŀ������µĴ���
	void Warning(IECreature * creature);		//��������Ұ����enemy

	
	//����creature��ָ����õ�ͳͳΪaction��
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

	IEContainer * FindCreatureAround();				//��ȡ��Χ���е��˵ľ��
	void ArrangeInfo();								//����һЩ ��ֹ��Ϣ��ֵ����Ĳ���

	void RunState();								//����״̬
	void RunGoal();									//����Ŀ��
	void RunAction();								//���ж���

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