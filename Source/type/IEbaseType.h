/***********************************
* name     : IEbaseType.h
* creater  : cosc
* info     : class base type
* c_date   : 2017/1/3
* l_date   : 2017/1/3
* version  : 1.0
* remark   : base types(with template) based on IEObject
************************************/

#ifndef __IE_BASE_TYPE__
#define __IE_BASE_TYPE__

#include "../core/IEobject.h"

IE_BEGIN

template<class T>
class IEBaseType :public IEObject
{
public:
	IEBaseType();
	IEBaseType(T data);
	~IEBaseType();
	virtual void Initialization();
	static IEBaseType * Create(T data);
	static IEBaseType * Create();

public:
	T& GetData();

private:
	T m_data;
};

template<class T>
IEBaseType<T>::IEBaseType()
{

}

template<class T>
IEBaseType<T>::IEBaseType(T data)
{
	m_data = data;
}

template<class T>
IEBaseType<T>::~IEBaseType()
{

}

template<class T>
void IEBaseType<T>::Initialization()
{

}

template<class T>
IEBaseType<T> * IEBaseType<T>::Create()
{
	IEBaseType<T> * object = new IEBaseType<T>();
	object->Initialization();
	return object;
}

template<class T>
IEBaseType<T> * IEBaseType<T>::Create(T data)
{
	IEBaseType<T> * object = new IEBaseType<T>(data);
	object->Initialization();
	return object;
}

template<class T>
T& IEBaseType<T>::GetData()
{
	return m_data;
}

IE_END

#endif