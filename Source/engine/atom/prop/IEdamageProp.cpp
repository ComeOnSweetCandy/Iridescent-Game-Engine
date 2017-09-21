//#define __IE_DLL_EXPORTS__
//#include "IEdamageProp.h"
//#include "../creature/IECreature.h"
//
//IE_BEGIN
//
//IEDamageProp::IEDamageProp()
//{
//	m_propType = __prop_damage_type__;
//	m_damage = 0;
//}
//
//IEDamageProp::~IEDamageProp()
//{
//
//}
//
//void IEDamageProp::Initialization(int propIndex, IETrigger * trigger, IECreature * propOwner, int damage)
//{
//	IEProp::Initialization(propIndex, trigger);
//
//	SetPropOwner(propOwner);
//	SetDamage(damage);
//
//	ChangePropTexture("propBody");
//}
//
//IEDamageProp * IEDamageProp::Create(int propIndex, IETrigger * trigger, IECreature * propOwner, int damage)
//{
//	IEDamageProp * prop = new IEDamageProp();
//	prop->Initialization(propIndex, trigger, propOwner, damage);
//	return prop;
//}
//
//void IEDamageProp::InteractiveNode(IENode * strikeNode)
//{
//	IENode * ownerNode = GetPropOwner();
//	if (strikeNode != ownerNode)
//	{
//		IECreature * creature = (IECreature *)strikeNode;
//		creature->Damaged(m_damage);
//	}
//}
//
//void IEDamageProp::SetDamage(int damage)
//{
//	m_damage = damage;
//}
//
//IE_END