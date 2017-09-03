///***********************************
//* name     : IEcast.h
//* creater  : cosc
//* info     : action cast skill
//* date     : 2017/6/12
//* version  : 1.0
//* remark   : none
//************************************/
//
//#ifndef __IE_CAST__
//#define __IE_CAST__
//
//#include "IEaction.h"
//
//IE_BEGIN
//
//class IECreature;
//
//class __IE_DLL__ IECast :public IEAction
//{
//public:
//	IECast();
//	virtual ~IECast();
//	virtual void Initialization(unsigned int skillID);
//	static IECast * Create(unsigned int skillID = 0);
//
//public:
//	virtual bool Begin();
//	virtual bool Excute();
//	virtual bool End();
//
//	virtual void Cast();
//
//private:
//	bool m_haveCasted;
//	unsigned int m_skillID;
//	float m_lastedTime;
//};
//
//IE_END
//
//#endif