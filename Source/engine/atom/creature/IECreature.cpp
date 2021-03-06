#define __IE_DLL_EXPORTS__
#include "IECreature.h"

#include "../../../interface/cmd/IEapplication.h"

#include "../../../core/element/IEtext.h"
#include "../../../core/element/IEprocessBar.h"

#include "goal/IEGoalAwait.h"
#include "goal/IEGoalWatch.h"
#include "goal/IEGoalUser.h"
#include "goal/IEGoalGo.h"

#include "action/IEActionRest.h"
#include "action/IEActionWalk.h"

#include "../../script/creature/IELUACreature.h"

IE_BEGIN

IECreature::IECreature()
{
	_Entry = NULL;
	_Unit = NULL;

	m_goalMachine = NULL;
	m_actionMachine = NULL;
	m_stateMachine = NULL;

	m_nameDisplay = NULL;
	m_healthDisplay = NULL;
}

IECreature::~IECreature()
{
	__IE_DELETE__(_Unit);

	__IE_RELEASE_DIF__(m_goalMachine);
	__IE_RELEASE_DIF__(m_actionMachine);
	__IE_RELEASE_DIF__(m_stateMachine);
}

void IECreature::Initialization(unsigned int creatureID, unsigned int creatureOrder)
{
	IEAtom::Initialization();
	IENode::SetDrawMode(false);

	InitUnit(creatureID, creatureOrder);
	//InitLeg(creatureID, creatureOrder);
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
	IENode::SetTranslate(x, y);

	if (m_physicNode)
	{
		m_physicNode->SetPhysicPosition(x, y);
	}
}

IECreatureEntry * IECreature::GetCreatureEntry()
{
	return _Entry;
}

IECreatureUnit * IECreature::GetCreatureUnit()
{
	return _Unit;
}

IEGoalMachine * IECreature::GetGoalMachine()
{
	return m_goalMachine;
}

IEActionMachine * IECreature::GetActionMachine()
{
	return m_actionMachine;
}

IEStateMachine * IECreature::GetStateMachine()
{
	return m_stateMachine;
}

void IECreature::InitUnit(unsigned int creatureID, int creatureOrder)
{
	//获取creature的基本信息
	_Entry = &(IECreatureList::Share()->m_entrys[creatureID]);

	//获取XML信息表
	m_XML = _Entry->_XML;

	//新建个体信息
	_Unit = new IECreatureUnit();

	//填入必要信息
	_Unit->_CreatrueID = creatureID;
	_Unit->_Order = creatureOrder;

	//需要从map中读取的信息
	strcpy(_Unit->_UnitName, "steven");
	_Unit->_Party = __creature_party_friend__;
	_Unit->_Level = 10;

	//需要从save中读取的信息 目前总是自行假设
	_Unit->_Alive = true;
	
	//需要通过计算的数据
	_Unit->_MaxHealth = _Entry->_BaseHealth + _Unit->_Level * _Entry->_GrowHealth;
	_Unit->_CurHealth = _Unit->_MaxHealth;
	_Unit->_MaxPower = _Entry->_BaseMagic + _Unit->_Level * _Entry->_GrowMagic;
	_Unit->_CurPower = _Unit->_MaxPower;
	_Unit->_Speed = _Entry->_BaseSpeed + _Unit->_Level * _Entry->_GrowSpeed;
	_Unit->_Damage = _Entry->_BaseDamage + _Unit->_Level * _Entry->_GrowDamage;
	
	//贴图
	IEPackerTexture * texture = IEPackerTexture::Create(_Entry->_XML->FindChild("texture"));
	ChangeTexture(texture);

	//根据XML生成PhysicNode
	IEXml * physicXML = _Entry->_XML->FindChild("physic");
	IEPhysicNode * physicNode = IEPhysicNode::Create(physicXML);
	BindPhysicNode(physicNode);

	//脚本
	m_LUA = _Entry->_LUA;
	if (!m_LUA)
	{
		m_LUA = luaL_newstate();
		luaL_openlibs(m_LUA);

		char scriptName[64];
		sprintf(scriptName, "%s%s%s", "../Debug/data/script/creature/", _Entry->_CreatureName, ".LUA");

		luaL_Reg lua_reg_libs[] =
		{
			{ "IECreature", LUAInitCreature },
			{ NULL, NULL }
		};

		for (luaL_Reg * lua_reg = lua_reg_libs; lua_reg->func; ++lua_reg)
		{
			luaL_requiref(m_LUA, lua_reg->name, lua_reg->func, 1);
			lua_pop(m_LUA, 1);
		}
		
		if (luaL_dofile(m_LUA, scriptName) != 0)
		{
			__IE_WARNING__("IECreature : can not find LUA file.\n");
		}
		_Entry->_LUA = m_LUA;
	}
}

void IECreature::InitMachine()
{
	m_goalMachine = IEGoalMachine::Create(this);
	m_actionMachine = IEActionMachine::Create(this);
	m_stateMachine = IEStateMachine::Create(this);
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

void IECreature::Update()
{
	IEAtom::Update();

	Live();
}

void IECreature::Born()
{
	if (LUAFunctionAllocateFunction(_Entry->_LUA, "Born"))
	{
		LUASetUserdate(m_LUA, "self", "IECreature.IECreature", this);
		lua_call(_Entry->_LUA, 0, 0);
	}
	else
	{

	}
}

void IECreature::Live()
{
	RunState();
	RunGoal();
	RunAction();
}

void IECreature::Die()
{
	if (LUAFunctionAllocateFunction(_Entry->_LUA, "Die"))
	{
		LUASetUserdate(m_LUA, "self", "IECreature.IECreature", this);
		lua_call(_Entry->_LUA, 0, 0);
	}
	else
	{

	}
}

void IECreature::ChangeGroup(const char * groupName, IECreaturePart partAction)
{
	//仅仅修改sprite元素的贴图组
	bool isCombination = false;

	if (isCombination)
	{
		if (partAction == __creature_part_leg__)
		{
			m_leg->ChangeGroup(groupName, 1);
		}
	}
	else
	{
		IEAtom::ChangeGroup(groupName, 1);
	}


	//if (partGroup == __creature_part_leg__)
	//{
	//	m_leg->ChangeGroup(groupName, partGroup);
	//}
	//else
	//{
	//	IECreature::ChangeGroup(groupName, partGroup);
	//}

	////这里仅仅是改变人物当前的移动行为
	////并不是改变人物的其它行为动作

	//bool isWalking = true;
	//bool isDroping = true;

	//if (isWalking == true)
	//{
	//	m_leg->ChangeGroup("walk");
	//}
	//else if (isDroping == true)
	//{
	//	m_leg->ChangeGroup("drop");
	//}
	//else
	//{
	//	m_leg->ChangeGroup("silent");
	//}
}

void IECreature::ChangeGroup(const char * groupName, IECreaturePart partAction, unsigned int playTimes, IEObject * object, IEFunctionTexturePlayFinished playEndedFunction)
{
	//仅仅修改sprite元素的贴图组
	bool isCombination = false;

	if (isCombination)
	{
		if (partAction == __creature_part_leg__)
		{
			m_leg->ChangeGroup(groupName, 1);
		}
	}
	else
	{
		IESprite::ChangeGroup(groupName, 1, playTimes, object, playEndedFunction);
	}
}

void IECreature::Cured(int cureValue)
{
	printf("%d",cureValue);
	return;

	_Unit->_CurHealth = _Unit->_CurHealth + cureValue;
	ArrangeInfo();

	m_healthDisplay->SetProcess(_Unit->_CurHealth / _Unit->_MaxHealth);
}

void IECreature::Damaged(int damageValue)
{

}

void IECreature::User()
{
	IEGoalUser * goal = IEGoalUser::Create();
	m_goalMachine->ChangeGoal(goal);
}

void IECreature::Await()
{
	if (LUAFunctionAllocateFunction(_Entry->_LUA, "Await"))
	{
		LUASetUserdate(_Entry->_LUA, "self", "IECreature.IECreature", this);
		lua_call(_Entry->_LUA, 0, 0);
	}
	else
	{
		IEGoalWatch * goal = IEGoalWatch::Create();
		m_goalMachine->ChangeGoal(goal);
	}
}

void IECreature::Warning(IECreature * creature)
{
	if (LUAFunctionAllocateFunction(_Entry->_LUA, "Warning"))
	{
		LUASetUserdate(_Entry->_LUA, "self", "IECreature.IECreature", this);
		lua_call(_Entry->_LUA, 0, 0);
	}
	else
	{
		IEGoalGo * goal = IEGoalGo::Create(creature->GetTranslate()[0], creature->GetTranslate()[1]);
		m_goalMachine->ChangeGoal(goal);
	}
}

void IECreature::Rest()
{
	IERest * rest = IERest::Create();
	m_actionMachine->ChangeAction(rest);
}

void IECreature::Displacement(float x, float y)
{
	IEActionWalk * action = IEActionWalk::Create(x, y);
	m_actionMachine->ChangeAction(action);
}

void IECreature::ArrangeInfo()
{
	if (_Unit->_CurHealth < 0)
	{
		_Unit->_CurHealth = 0;
	}
	if (_Unit->_CurHealth>_Unit->_MaxHealth)
	{
		_Unit->_CurHealth = _Unit->_MaxHealth;
	}
}

void IECreature::RunState()
{
	m_stateMachine->Run();
}

void IECreature::RunGoal()
{
	m_goalMachine->Run();
}

void IECreature::RunAction()
{
	m_actionMachine->Run();
}

//通用部分
bool __CreatureOpposite(IECreature * creatureA, IECreature * creatureB)
{
	IECreatureParty creatureAparty = creatureA->GetCreatureUnit()->_Party;
	IECreatureParty creatureBparty = creatureB->GetCreatureUnit()->_Party;

	if (creatureAparty == __creature_party_mine__)
	{
		if (creatureBparty == __creature_party_friend__) return false;
		else if (creatureBparty == __creature_party_neutral__) return false;
		else return true;
	}
	else if (creatureAparty == __creature_party_friend__)
	{
		if (creatureBparty == __creature_party_mine__ || creatureBparty == __creature_party_friend__) return false;
		else if (creatureBparty == __creature_party_neutral__) return false;
		else return true;
	}
	else if (creatureAparty == __creature_party_neutral__)
	{
		return false;
	}
	else if (creatureAparty == __creature_party_enemy__)
	{
		if (creatureBparty == __creature_party_enemy__) return false;
		else if (creatureBparty == __creature_party_neutral__) return false;
		else return true;
	}

	return false;
}

IEContainer * FindCreatureAround(IECreature * creature)
{
	IEContainer * arrays = IEApplication::Share()->GetCurrentActiveScene()->GetCreatures();
	IECreature ** childs = (IECreature **)(arrays->GetContainer());
	IEContainer * findedCreatures = IEContainer::CreateAndRetain();

	for (int index = 0; index < arrays->Count(); index++)
	{
		if (childs[index] != creature)
		{
			findedCreatures->Push(childs[index]);
		}
	}

	return findedCreatures;
}

IEContainer * FindAllCreatures(IECreature * creature)
{
	IEContainer * arrays = IEApplication::Share()->GetCurrentActiveScene()->GetCreatures();
	IECreature ** childs = (IECreature **)(arrays->GetContainer());
	IEContainer * findedCreatures = IEContainer::CreateAndRetain();

	for (int index = 0; index < arrays->Count(); index++)
	{
		findedCreatures->Push(childs[index]);
	}
	
	return findedCreatures;
}

void IECreature::InitLeg(unsigned int creatureID, unsigned int creatureOrder)
{
	//默认状态下为静止状态
	m_leg = IESprite::Create();
	m_leg->SetTranslate(0.0f, 0.0f);
	m_leg->ChangeTexture(m_texture);
	m_leg->ChangeGroup("static");
}

IE_END