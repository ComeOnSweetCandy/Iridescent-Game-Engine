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
	//ʹ�ø�prop ��Բ�ͬ���͵�prop�������ͬ��Ч�� ������ȥ����
}

void IEProp::PickProp(IEArmer * creature)
{
	//ʰȡ��prop ��Բ�ͬ���͵�prop�������ͬ��Ч�� ������ȥ����
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

	//ɾ�����ݹ�����prop
	prop->DelSelf();

	//�������
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
		//Ҫ��Ŀ��Ϊ
		IEArmer * creature = (IEArmer *)node;

		IEPropPack * bag = creature->GetPlayersPack();
		bag->AddProp(this);

		RemoveFromParent();
	}
	else if (m_propState == __prop_state_fly__)
	{
		//Ҫ��Ŀ�����
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
	//��ȡ��Ϣ��
	IEPropEntry * _Entry = &(IEPropList::Share()->m_entrys[m_propID]);

	//��ȡXML��Ϣ��
	m_XML = _Entry->_XML;

	//��ͼ
	IEPackerTexture * texture = IEPackerTexture::Create(_Entry->_XML->FindChild("texture"));
	ChangeTexture(texture);

	//�ű�
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

	//��������һЩ���� ������ĸ���Χ��
	if (m_propState == __prop_state_pack__)
	{
		//������
		SetUnitPiexls(32);
		ChangeGroup("pack");
	}
	else if (m_propState == __prop_state_pick__)
	{
		//������
		SetUnitPiexls(32);
		ChangeGroup("pick");

		//����XML����PhysicNode
		IEPhysicCircle * physicEdge = IEPhysicCircle::Create(__edge_circle__, 0.5f, 0.5f, 0.5f);
		IEPhysicNode * physicNode = IEPhysicNode::Create(physicEdge, __physic_suspend_node__);
		BindPhysicNode(physicNode);

		//��ӵ�������
		AddSelf();
	}
}

void IEProp::AddSelf()
{
	//�����prop��
	IEApplication::Share()->GetCurrentActiveScene()->GetPropLayer()->AddChild(this);
}

void IEProp::DelSelf()
{
	//ɾ������
	IEApplication::Share()->GetCurrentActiveScene()->GetPropLayer()->RemoveChild(this);
}

IE_END