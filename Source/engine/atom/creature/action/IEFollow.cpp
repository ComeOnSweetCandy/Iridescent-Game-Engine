//#define __IE_DLL_EXPORTS__
//#include "IEfollow.h"
//
//IE_BEGIN
//
//IEFollow::IEFollow()
//{
//	m_actionType = __action_walk__;
//	m_actionLevel = __actionlevel_0__;
//	m_followAtom = NULL;
//
//	m_controllDistance = 1.0f;
//}
//
//IEFollow::~IEFollow()
//{
//	IEAtom * atom = NULL;
//}
//
//void IEFollow::Initialization(IEAtom * atom)
//{
//	IEFollow::SetFollowAtom(atom);
//}
//
//IEFollow * IEFollow::Create(IEAtom * atom)
//{
//	IEFollow * action = new IEFollow();
//	action->Initialization(atom);
//	return action;
//}
//
//bool IEFollow::Begin()
//{
//	ChangeActionTexture("walk");
//	DeleteOtherActions();
//	return true;
//}
//
//bool IEFollow::Excute()
//{
//	IEAtom * m_actionAtom = (IEAtom *)GetActionNode();
//
//	const float * actionAtomTranslate = m_actionAtom->GetTranslate();
//	const float * followAtomTranslate = m_followAtom->GetTranslate();
//	IEVector p1 = IEVector(actionAtomTranslate[0], actionAtomTranslate[1]);
//	IEVector p2 = IEVector(followAtomTranslate[0], followAtomTranslate[1]);
//
//	if ((p1 - p2).Length() <= m_controllDistance)
//	{
//		DeleteAction(m_actionType);
//	}
//	return true;
//}
//
//bool IEFollow::End()
//{
//	DeleteAnimation(m_animation);
//	return true;
//}
//
//void IEFollow::SetFollowAtom(IEAtom * atom)
//{
//	m_followAtom = atom;
//}
//
//IE_END