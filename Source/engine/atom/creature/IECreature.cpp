#define __IE_DLL_EXPORTS__
#include "IECreature.h"

#include "../../../interface/cmd/IEapplication.h"

#include "IEcreaturesInfoManager.h"
#include "../../../core/element/IEtext.h"
#include "../../../core/element/IEprocessBar.h"

#include "goal/IEGoalAwait.h"
#include "goal/IEGoalWatch.h"

#include "../../script/IEluaNode.h"
#include "../../script/IEluaCreature.h"

IE_BEGIN

IECreature::IECreature()
{
	m_luaScript = NULL;
	m_unit = NULL;
	m_actionMachine = NULL;

	m_nameDisplay = NULL;
	m_healthDisplay = NULL;
}

IECreature::~IECreature()
{
	__IE_DELETE__(m_unit);
	__IE_RELEASE_DIF__(m_actionMachine);
}

void IECreature::Initialization(unsigned int creatureID, unsigned int creatureOrder)
{
	IEAtom::Initialization();
	IEElement::SetRegularization(true);
	IENode::SetDrawMode(false);

	InitUnit(creatureID, creatureOrder);
	InitMachine();
	InitCreatureTab();
}

IECreature * IECreature::Create(unsigned int creatureID, unsigned int creatureOrder)
{
	IECreature * creature = new IECreature();
	creature->Initialization(creatureID, creatureOrder);
	return creature;
}

void IECreature::SetTranslate(const float &x, const float &y)
{
	printf("IECreature : settranslate error.\n");
}

void IECreature::SetPosition(const float &x, const float &y)
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
	//m_actionMachine->DeleteAllActions();
	//m_actionMachine->CheckActions();
}

IECreatureUnit * IECreature::GetCreatureUnit()
{
	return m_unit;
}

IEActionMachine * IECreature::GetActionMachine()
{
	return m_actionMachine;
}

void IECreature::InitUnit(unsigned int creatureID, int creatureOrder)
{
	//获取creature的基本信息
	IECreatureInfo& __creatureInfo = IECreaturesInfoManager::Share()->m_creaturesInfoList[creatureID];

	//新建个体信息
	m_unit = new IECreatureUnit();

	//填入必要信息
	m_unit->_CreatrueID = creatureID;
	m_unit->_Order = creatureOrder;

	//需要从map中读取的信息
	m_unit->_Party = __creature_group_friend__;
	m_unit->_Level = 10;
	strcpy(m_unit->_Name, "steven");

	//需要从save中读取的信息 目前总是自行假设
	m_unit->_Alive = true;

	//需要通过计算的数据
	m_unit->_MaxHealth = __creatureInfo._BaseHealth + m_unit->_Level * __creatureInfo._GrowHealth;
	m_unit->_CurHealth = m_unit->_MaxHealth;
	m_unit->_MaxPower = __creatureInfo._BaseMagic + m_unit->_Level * __creatureInfo._GrowMagic;
	m_unit->_CurPower = m_unit->_MaxPower;
	m_unit->_Speed = __creatureInfo._BaseSpeed + m_unit->_Level * __creatureInfo._GrowSpeed;
	m_unit->_Damage = __creatureInfo._BaseDamage + m_unit->_Level * __creatureInfo._GrowDamage;
	
	//贴图
	IEPackerTexture * texture = IEPackerTexture::Create(__creatureInfo._XML->FindChild("texture"));
	ChangeTexture(texture);

	//物理
	IEPhysicNode * physicNode = NULL;
	BindPhysicNode(physicNode);

	//脚本
	lua_State * luaScript = __creatureInfo._LuaScript;
	if (!luaScript)
	{
		luaScript = luaL_newstate();
		luaL_openlibs(luaScript);

		char scriptName[64];
		sprintf(scriptName, "%s%s%s", "../Debug/data/script/creature/", __creatureInfo._CreatureName, ".lua");

		luaL_Reg lua_reg_libs[] =
		{
			{ "IECreature", luaopen_creature },
			{ "IENode", luaopen_node },
			{ NULL, NULL }
		};

		for (luaL_Reg * lua_reg = lua_reg_libs; lua_reg->func; ++lua_reg)
		{
			luaL_requiref(luaScript, lua_reg->name, lua_reg->func, 1);
			lua_pop(luaScript, 1);
		}

		if (luaL_dofile(luaScript, scriptName) != 0)
		{
			__IE_WARNING__("IECreature : can not find luaScript file.\n");
		}

		__creatureInfo._LuaScript = luaScript;
	}
}

void IECreature::InitMachine()
{
	m_goalMachine = IEGoalMachine::Create(this);
	m_actionMachine = IEActionMachine::Create(this);
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

void IECreature::AnalyseCommand(char * command)
{

}

void IECreature::Cured(int cureValue)
{
	printf("%d",cureValue);
	return;

	m_unit->_CurHealth = m_unit->_CurHealth + cureValue;
	ArrangeInfo();

	m_healthDisplay->SetProcess(m_unit->_CurHealth / m_unit->_MaxHealth);
}

void IECreature::Damaged(int damageValue)
{
	//m_unit->_CurHealth = m_unit->_CurHealth - damageValue;
	//ArrangeInfo();

	//if (m_unit->_CurHealth <= 0)
	//{
	//	IEDead * deadAction = IEDead::Create();
	//	GetActionMachine()->ChangeAction(__action_dead__, deadAction);
	//}
	//else
	//{
	//	IEInjured * injuredAction = IEInjured::Create();
	//	GetActionMachine()->ChangeAction(__action_injured__, injuredAction);
	//}

	//m_healthDisplay->SetProcess(m_unit->_CurHealth / m_unit->_MaxHealth);
}

void IECreature::Await()
{
	//从script读取脚本信息
	//char * command[256];

	//解析命令
	IECreatureInfo& __creatureInfo = IECreaturesInfoManager::Share()->m_creaturesInfoList[m_unit->_CreatrueID];

	if (AllocateLuaFunction(__creatureInfo._LuaScript, "Await"))
	{
		SetLuaUserdataElement(__creatureInfo._LuaScript, "self", "IECreature.IECreature", this);
		lua_call(__creatureInfo._LuaScript, 0, 0);
	}
	else
	{
		IEGoalWatch * goal = IEGoalWatch::Create();
		m_goalMachine->AddGoal(goal);
	}
}

void IECreature::Walk(float x, float y)
{
	//IEWalk * wal = IEWalk::Create(x, y);
	//GetActionMachine()->ChangeAction(__action_walk__, wal);
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
	if (m_unit->_CurHealth < 0)
	{
		m_unit->_CurHealth = 0;
	}
	if (m_unit->_CurHealth>m_unit->_MaxHealth)
	{
		m_unit->_CurHealth = m_unit->_MaxHealth;
	}
}

void IECreature::RunState()
{
	//检测当前应当有的状态信息

}

void IECreature::RunGoal()
{
	m_goalMachine->Run();
}

void IECreature::RunAction()
{
	m_actionMachine->Run();
}

IE_END