#define __IE_DLL_EXPORTS__
#include "IEsituation.h"

IESituation * IESituation::m_StaticSituation = NULL;

IESituation::IESituation()
{
	_FieldAltitude = 8.0f;
}

IESituation::~IESituation()
{

}

IESituation * IESituation::Share()
{
	if (m_StaticSituation == NULL)
	{
		m_StaticSituation = new IESituation();
	}
	return m_StaticSituation;
}

void IESituation::Release()
{
	delete this;
}