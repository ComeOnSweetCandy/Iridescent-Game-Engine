///***********************************
//* name     : IEwalk.h
//* creater  : cosc
//* info     : action walk
//* date     : 2017/2/16
//* version  : 1.0
//* remark   : none
//************************************/
//
//#ifndef __IE_WALK__
//#define __IE_WALK__
//
//#include "IEaction.h"
//
//IE_BEGIN
//
//class IEDisplacement;
//
//class __IE_DLL__ IEWalk :public IEAction
//{
//public:
//	IEWalk();
//	virtual ~IEWalk();
//	virtual void Initialization(float x, float y);
//	static IEWalk * Create(float x, float y);
//
//public:
//	virtual void Begin();
//	virtual void Excute();
//	virtual void End();
//
//private:
//	void GetNextStep();
//	void SetDestination(float x, float y);
//	void FindPath();
//
//private:
//	IEVector m_destination;
//	IEArray * m_path;
//	int m_stepIndex;
//};
//
//IE_END
//
//#endif