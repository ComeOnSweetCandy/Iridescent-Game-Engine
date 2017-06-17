/***********************************
* name     : IEcreature.h
* creater  : cosc
* info     : creature
* date     : 2017/1/4
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CREATURE__
#define __IE_CREATURE__

#include "IEatom.h"
#include "creature/IEcreatureInfo.h"
#include "../action/IEactionMachine.h"

IE_BEGIN

class IECreaturesInfoManager;
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

	IECreatureInfo * GetCreatureInfo();
	IEUnitInfo * GetUnitInfo();
	IEActionMachine * GetActionMachine();

	//����creature��ָ��
	void Walk(float x, float y);
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
	void InitCreatureInfo(int creatureID);
	void InitUnitInfo(int creatureOrder);
	void InitCreatureScript();
	void InitCreatureTab();

	IEContainer * FindCreatureAround();				//��ȡ��Χ���е��˵ľ��
	void ArrangeInfo();								//����һЩ ��ֹ��Ϣ��ֵ����Ĳ���

protected:
	IECreatureInfo * m_creatureInfo;
	IEUnitInfo * m_unitInfo;
	IEActionMachine * m_actionMachine;

	IEText * m_nameDisplay;
	IEProcessBar * m_healthDisplay;
};

IE_END

#endif