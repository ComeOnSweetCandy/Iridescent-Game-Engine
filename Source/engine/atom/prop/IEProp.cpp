#define __IE_DLL_EXPORTS__
#include "IEProp.h"

#include "../creature/IEArmer.h"
#include "IEPropList.h"

#include "../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEProp::IEProp()
{
	m_propState = __prop_state_max__;
	m_propType = __prop_type_max__;
	m_owner = NULL;

	m_propID = 0;
	m_pileMax = 1;
	m_propCount = 0;
}

IEProp::~IEProp()
{
	RemoveFromParent();
}

void IEProp::Initialization(unsigned int propID, IEPropState propState)
{
	IEAtom::Initialization();

	IEProp::SetPropID(propID);
	IEProp::SetPropState(propState);
	IEProp::InitUnit();
}

IEProp * IEProp::Create(unsigned int propIndex, IEPropState propState)
{
	//IEProp * prop = new IEProp();
	//prop->Initialization(propIndex, propState);
	//return prop;

	return NULL;
}

void IEProp::UseProp()
{
	//使用该prop 针对不同类型的prop会产生不同的效果 由子类去处理
}

void IEProp::PickProp(IEArmer * creature)
{
	//拾取该prop 针对不同类型的prop会产生不同的效果 由子类去处理
	IEPropPack * bag = NULL;

	bag->AddProp(this);
}

void IEProp::SetPropType(IEPropType propType)
{
	m_propType = propType;
}

void IEProp::SetPropState(IEPropState propState)
{
	m_propState = propState;
}

void IEProp::SetOwner(IEArmer * creature)
{
	m_owner = creature;
}

void IEProp::SetPropID(unsigned int propID)
{
	m_propID = propID;
}

unsigned int IEProp::AddPropCount(unsigned int propCount)
{
	m_propCount = m_propCount + propCount;

	if (m_propCount > m_pileMax)
	{
		int leftCount = m_propCount - m_pileMax;
		m_propCount = m_pileMax;

		return leftCount;
	}

	ArrangeInfo();
	return 0;
}

unsigned int IEProp::AddPropCount(IEProp * prop)
{
	unsigned int propCount = prop->GetPropCount();

	if (m_propCount > m_pileMax)
	{
		m_propCount = m_pileMax;

		return m_propCount - m_pileMax;
	}

	//删除传递过来的prop
	prop->DelSelf();

	//处理后续
	ArrangeInfo();
	return 0;
}

unsigned int IEProp::ReducePropCount(unsigned int propCount)
{
	if (m_propCount < propCount)
	{
		return propCount - m_propCount;
	}
	else
	{
		m_propCount = m_propCount - propCount;
	}

	ArrangeInfo();
	return 0;
}

int IEProp::GetPropID()
{
	return m_propID;
}

IEArmer * IEProp::GetOwner()
{
	return m_owner;
}

IEPropType IEProp::GetPropType()
{
	return m_propType;
}

unsigned int IEProp::GetPropCount()
{
	return m_propCount;
}

void IEProp::InteractiveNode(IENode * node)
{
	if (m_propState == __prop_state_pick__)
	{
		//要求目标为
		IEArmer * creature = (IEArmer *)node;

		IEPropPack * bag = creature->GetPlayersPack();
		bag->AddProp(this);

		RemoveFromParent();
	}
	else if (m_propState == __prop_state_fly__)
	{
		//要求目标对立
	}
	else
	{

	}
}

void IEProp::ArrangeInfo()
{
	if (m_propCount == 0)
	{
		DelSelf();
	}
}

void IEProp::InitUnit()
{
	//获取信息表
	IEPropEntry * _Entry = &(IEPropList::Share()->m_entrys[m_propID]);

	//获取XML信息表
	m_XML = _Entry->_XML;

	//贴图
	IEPackerTexture * texture = IEPackerTexture::Create(_Entry->_XML->FindChild("texture"));
	ChangeTexture(texture);

	//脚本
	if (!(m_LUA = _Entry->_LUA))
	{
		m_LUA = luaL_newstate();
		luaL_openlibs(m_LUA);

		char scriptName[64];
		sprintf(scriptName, "%s%s%s", "../Debug/data/script/prop/", _Entry->_PropName, ".LUA");

		luaL_Reg lua_reg_libs[] =
		{
			{ "base", luaopen_base },
			{ NULL, NULL }
		};

		for (luaL_Reg * lua_reg = lua_reg_libs; lua_reg->func; ++lua_reg)
		{
			luaL_requiref(m_LUA, lua_reg->name, lua_reg->func, 1);
			lua_pop(m_LUA, 1);
		}

		if (luaL_dofile(m_LUA, scriptName) != 0)
		{
			__IE_WARNING__("IEAttack : can not find LUA file.\n");
		}
		_Entry->_LUA = m_LUA;
	}

	//最后检测进行一些处理 检测在哪个范围内
	if (m_propState == __prop_state_pack__)
	{
		//背包中
		SetUnitPiexls(32);
		ChangeGroup("pack");
	}
	else if (m_propState == __prop_state_pick__)
	{
		//场景中
		SetUnitPiexls(32);
		ChangeGroup("pick");

		//根据XML生成PhysicNode
		IEPhysicCircle * physicEdge = IEPhysicCircle::Create(__edge_circle__, 0.5f, 0.5f, 0.5f);
		IEPhysicNode * physicNode = IEPhysicNode::Create(physicEdge, __physic_suspend_node__);
		BindPhysicNode(physicNode);

		//添加到场景中
		AddSelf();
	}
}

void IEProp::AddSelf()
{
	//添加入prop层
	IEApplication::Share()->GetCurrentActiveScene()->GetPropLayer()->AddChild(this);
}

void IEProp::DelSelf()
{
	//删除自身
	IEApplication::Share()->GetCurrentActiveScene()->GetPropLayer()->RemoveChild(this);
}

IE_END