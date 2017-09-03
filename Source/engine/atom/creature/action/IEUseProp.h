///***********************************
//* name     : IEuseProp.h
//* creater  : cosc
//* info     : action use prop
//* date     : 2017/3/31
//* version  : 1.0
//* remark   : none
//************************************/
//
//#ifndef __IE_USE_PROP__
//#define __IE_USE_PROP__
//
//#include "IEaction.h"
//
//IE_BEGIN
//
//class IECreature;
//
//class __IE_DLL__ IEUseProp :public IEAction
//{
//public:
//	IEUseProp();
//	virtual ~IEUseProp();
//	virtual void Initialization(int packIndex);
//	static IEUseProp * Create();
//	static IEUseProp * Create(int packIndex);
//
//public:
//	virtual bool Begin();
//	virtual bool Excute();
//	virtual bool End();
//
//	void UseProp();
//
//private:
//	bool m_haveUsed;
//	int m_packIndex;
//	float m_lastedTime;
//};
//
//IE_END
//
//#endif