#define __IE_DLL_EXPORTS__
#include "IEPropCreator.h"

#include "IEPropList.h"
#include "IEPropEquipment.h"
#include "IEPropConsumable.h"

IE_BEGIN

IEPropEntry * entrys = IEPropList::Share()->GetEntrys();

IEProp * CreateProp(unsigned int propID, IEPropState propState)
{
	IEPropType propType = (IEPropType)(entrys[propID]._XML->FindChild("property")->FindChild("propType")->ValueInt());
	
	switch (propType)
	{
	case IridescentEngine::__prop_type_equipment__:
		return IEPropEquipment::Create(propID, propState);
	case IridescentEngine::__prop_type_task__:
		return NULL;
	case IridescentEngine::__prop_type_material__:
		return NULL;
	case IridescentEngine::__prop_type_consumable__:
		return IEPropConsumable::Create(propID, propState);
	case IridescentEngine::__prop_type_max__:
		return NULL;
	default:
		return NULL;
	}
}

IE_END