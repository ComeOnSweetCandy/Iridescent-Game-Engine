#define __IE_DLL_EXPORTS__
#include "IECreatureInfo.h"

#include "IECreature.h"

IE_BEGIN

bool __CreatureOpposite(IECreature * creatureA, IECreature * creatureB)
{
	IECreatureParty creatureAparty = creatureA->GetCreatureUnit()->_Party;
	IECreatureParty creatureBparty = creatureB->GetCreatureUnit()->_Party;

	if (creatureAparty == __creature_group_mine__)
	{
		if (creatureBparty == __creature_group_friend__) return false;
		else if (creatureBparty == __creature_group_neutral__) return false;
		else return true;
	}
	else if (creatureAparty == __creature_group_friend__)
	{
		if (creatureBparty == __creature_group_mine__ || creatureBparty == __creature_group_friend__) return false;
		else if (creatureBparty == __creature_group_neutral__) return false;
		else return true;
	}
	else if (creatureAparty == __creature_group_neutral__)
	{
		return false;
	}
	else if (creatureAparty == __creature_group_enemy__)
	{
		if (creatureBparty == __creature_group_enemy__) return false;
		else return true;
	}

	return false;
}

IE_END