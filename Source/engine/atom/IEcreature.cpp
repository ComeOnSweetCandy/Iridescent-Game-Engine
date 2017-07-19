#define __IE_DLL_EXPORTS__
#include "IECreature.h"

#include "../../interface/cmd/IEapplication.h"

#include "creature/IEcreaturesInfoManager.h"
#include "../../core/element/IEtext.h"
#include "../../core/element/IEprocessBar.h"

#include "../action/IEinjured.h"
#include "../action/IEdead.h"
#include "../action/IEwalk.h"

#include "../script/IEluaNode.h"
#include "../script/IEluaCreature.h"
#include "../script/IEluaPhysicCircle.h"
#include "../script/IEluaPhysicPolygon.h"
#include "../script/IEluaPhysicNode.h"

IE_BEGIN

IECreature::IECreature()
{
	m_luaScript = NULL;
	m_creatureInfo = NULL;
	m_unitInfo = NULL;
	m_actionMachine = NULL;

	m_nameDisplay = NULL;
	m_healthDisplay = NULL;
}

IECreature::~IECreature()
{
	__IE_DELETE__(m_unitInfo);
	__IE_RELEASE_DIF__(m_actionMachine);
}

void IECreature::Initialization(unsigned int creatureID, unsigned int creatureOrder)
{
	IEAtom::Initialization();
	IEElement::SetRegularization(true);
	IENode::SetDrawMode(false);

	InitCreatureInfo(creatureID);
	InitUnitInfo(creatureOrder);
	InitCreatureScript();
	InitCreatureTab();

	m_actionMachine = IEActionMachine::Create(this);
}

IECreature * IECreature::Create(unsigned int creatureID, unsigned int creatureOrder)
{
	IECreature * creature = new IECreature();
	creature->Initialization(creatureID, creatureOrder);
	return creature;
}

void IECreature::SetTranslate(const float &x, const float &y)
{
	IENode::SetTranslate(x, y);
	m_physicNode->SetPhysicPosition(x, y);
}

void IECreature::Born()
{
	
}

void IECreature::Live()
{
	RunState();
	RunGoal();
	RunAction();
}

void IECreature::Die()
{

}

void IECreature::TemporaryTextureEnd()
{
	m_actionMachine->DeleteAllActions();
	m_actionMachine->CheckActions();
}

IECreatureInfo * IECreature::GetCreatureInfo()
{
	return m_creatureInfo;
}

IEUnitInfo * IECreature::GetUnitInfo()
{
	return m_unitInfo;
}

IEActionMachine * IECreature::GetActionMachine()
{
	return m_actionMachine;
}

void IECreature::InitCreatureInfo(int creatureID)
{
	m_creatureInfo = IECreaturesInfoManager::Share()->m_creaturesInfoList[creatureID];

	IEAtom::SetTextureGroupName(m_creatureInfo->_CreatureName);
	IENode::SetAnchor(0.5f, 0.5f);
}

void IECreature::InitUnitInfo(int creatureOrder)
{
	if (creatureOrder == 0)
	{

	}
	else
	{

	}

	m_unitInfo = new IEUnitInfo();

	//从这里开始 从map中加载unit的所有信息

	//进行一些剩余的计算
	m_unitInfo->_MaxHealth = m_creatureInfo->_BaseHealth + m_unitInfo->_Level * m_creatureInfo->_GrowHealth;
	m_unitInfo->_CurHealth = m_unitInfo->_MaxHealth;
	m_unitInfo->_MaxPower = m_creatureInfo->_BasePower + m_unitInfo->_Level * m_creatureInfo->_GrowPower;
	m_unitInfo->_CurPower = m_unitInfo->_MaxPower;
	m_unitInfo->_Speed = m_creatureInfo->_BaseSpeed + m_unitInfo->_Level * m_creatureInfo->_GrowSpeed;
	m_unitInfo->_Damage = m_creatureInfo->_BaseDamage + m_unitInfo->_Level * m_creatureInfo->_GrowDamage;

	//if (m_unitInfo->_UnitGroup == __creature_group_enemy__)
	//{
	//	m_healthDisplay->SetBackgroundColor(IEColor(1.0f, 0.0f, 0.0));
	//}
	//else if (m_unitInfo->_UnitGroup == __creature_group_neutral__)
	//{
	//	m_healthDisplay->SetBackgroundColor(IEColor(1.0f, 1.0f, 0.0));
	//}
	//else
	//{
	//	m_healthDisplay->SetBackgroundColor(IEColor(0.0f, 1.0f, 0.0));
	//}
}

void IECreature::InitCreatureScript()
{
	IEString scriptName = pOBJECT_TO_cSTRING(SETTING["ScriptDir"]) + "creature/" + m_creatureInfo->_CreatureName + ".lua";
	m_luaScript = luaL_newstate();
	luaL_openlibs(m_luaScript);

	luaL_Reg lua_reg_libs[] =
	{
		{ "base", luaopen_base },
		{ "IEPhysicCircle", luaopen_physicCircle },
		{ "IEPhysicPolygon", luaopen_physicPolygon },
		{ "IEPhysicNode", luaopen_physicNode },
		{ "IECreature", luaopen_creature },
		{ "IENode", luaopen_node },
		{ NULL, NULL }
	};

	for (luaL_Reg * lua_reg = lua_reg_libs; lua_reg->func; ++lua_reg)
	{
		luaL_requiref(m_luaScript, lua_reg->name, lua_reg->func, 1);
		lua_pop(m_luaScript, 1);
	}

	if (luaL_dofile(m_luaScript, scriptName.GetString()) != 0)
	{
		__IE_WARNING__("IECreature : can not find m_luaScript file.\n");
	}

	SetLuaUserdataElement(m_luaScript, "self", "IECreature.IECreature", this);

	lua_getglobal(m_luaScript, "CreatePhysicNode");
	lua_call(m_luaScript, 0, 0);

	//绑定物理节点
	IEPhysicNode * physicNode = (IEPhysicNode *)GetLuaUserdataElement(m_luaScript, "creaturePhysicNode");
	physicNode->SetPhysicPosition(m_translate[0], m_translate[1]);
	BindPhysicNode(physicNode);
}

void IECreature::InitCreatureTab()
{
	//m_healthDisplay = IEProcessBar::Create(1.0f);
	//m_healthDisplay->SetTranslate(0.0f, -0.2f);
	//m_healthDisplay->SetSize(1.0f, 0.05f);
	//IENode::AddChild(m_healthDisplay);

	//m_nameDisplay = IEText::Create("default");
	//m_nameDisplay->SetTranslate(0.0f, 1.2f);
	//IENode::AddChild(m_nameDisplay);
}

void IECreature::Cured(int cureValue)
{
	m_unitInfo->_CurHealth = m_unitInfo->_CurHealth + cureValue;
	ArrangeInfo();

	m_healthDisplay->SetProcess(m_unitInfo->_CurHealth / m_unitInfo->_MaxHealth);
}

void IECreature::Damaged(int damageValue)
{
	m_unitInfo->_CurHealth = m_unitInfo->_CurHealth - damageValue;
	ArrangeInfo();

	if (m_unitInfo->_CurHealth <= 0)
	{
		IEDead * deadAction = IEDead::Create();
		GetActionMachine()->ChangeAction(__action_dead__, deadAction);
	}
	else
	{
		IEInjured * injuredAction = IEInjured::Create();
		GetActionMachine()->ChangeAction(__action_injured__, injuredAction);
	}

	m_healthDisplay->SetProcess(m_unitInfo->_CurHealth / m_unitInfo->_MaxHealth);
}

void IECreature::Walk(float x, float y)
{
	IEWalk * wal = IEWalk::Create(x, y);
	GetActionMachine()->ChangeAction(__action_walk__, wal);
}

void IECreature::FollowEnemy()
{
	IEContainer * creatures = FindCreatureAround();
	int randomNumber = rand() % (creatures->Count());
	IECreature * creature = (IECreature *)(creatures->Find(randomNumber));
	creatures->Release();

	FollowCreature(creature);
}

void IECreature::FollowCreature(IECreature * creature)
{
	const float * translate = creature->GetTranslate();
	Walk(translate[0], translate[1]);
}

IEContainer * IECreature::FindCreatureAround()
{
	IEContainer * arrays = IEApplication::Share()->GetCurrentActiveScene()->GetCreatures();
	IECreature ** childs = (IECreature **)(arrays->GetContainer());
	IEContainer * findedCreatures = IEContainer::CreateAndRetain();

	for (int index = 0; index < arrays->Count(); index++)
	{
		if (childs[index] != this)
		{
			findedCreatures->Push(childs[index]);
		}
	}

	return findedCreatures;
}

void IECreature::ArrangeInfo()
{
	if (m_unitInfo->_CurHealth < 0)
	{
		m_unitInfo->_CurHealth = 0;
	}
	if (m_unitInfo->_CurHealth>m_unitInfo->_MaxHealth)
	{
		m_unitInfo->_CurHealth = m_unitInfo->_MaxHealth;
	}
}

void IECreature::RunState()
{
	//检测当前应当有的状态信息


}

void IECreature::RunGoal()
{

}

void IECreature::RunAction()
{
	//m_actionMachine->ExcuteAction();
}

IE_END