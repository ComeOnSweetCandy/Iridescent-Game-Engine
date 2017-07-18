#define __IE_DLL_EXPORTS__
#include "IEcmdAnalyse.h"

#include "../core/container/IEcontianer.h"

#include "../interface/cmd/IEapplication.h"
#include "../engine/scene/terrain/IETerrainArea.h"

IE_BEGIN

IECmdAnalyse * IECmdAnalyse::m_StaticCmdAnalyse = NULL;

IECmdAnalyse::IECmdAnalyse()
{

}

IECmdAnalyse::~IECmdAnalyse()
{

}

void IECmdAnalyse::Initialization()
{

}

IECmdAnalyse * IECmdAnalyse::Share()
{
	if (m_StaticCmdAnalyse == NULL)
	{
		m_StaticCmdAnalyse = new IECmdAnalyse();
		m_StaticCmdAnalyse->Initialization();
	}
	return m_StaticCmdAnalyse;
}

void IECmdAnalyse::Release()
{
	delete this;
}

void IECmdAnalyse::InjuectCommand(char * command)
{
	if (m_command.Length() == 0)
	{
		m_command = command;
	}
}

void IECmdAnalyse::Run()
{
	if (m_command.Length() != 0)
	{
		//分离所有的空格
		IEContainer * arrays = m_command.SplitBy(' ');
		m_commandSectionCount = arrays->Count();
		m_commandArrays = (IEString **)arrays->GetContainer();

		FieldAnalyse();

		m_command = "";
	}
}

void IECmdAnalyse::FieldAnalyse()
{
	if (m_commandSectionCount == 1)
	{
		//单命令
		NormalCommand();
	}
	else
	{
		IEString field = *(m_commandArrays[0]);

		if (field == "set")
		{
			if (SetCommand())
			{
				printf("set complete\n\n>");
			}
			else
			{
				printf("command set parameter error\n\n>");
			}
		}
		else if (field == "add")
		{
			if (AddCommand())
			{
				printf("add completed\n\n>");
			}
			else
			{
				printf("error with add command.\n\n>");
			}
		}
		else
		{
			printf("unkown command.\n\n>");
		}
	}
}

void IECmdAnalyse::NormalCommand()
{
	IEString field = *(m_commandArrays[0]);

	if (field == "cls")
	{
		system("cls");
		printf(">");
	}
	else if (field == "exit")
	{
		exit(0);
	}
	else
	{
		printf("unkown command.\n\n>");
	}
}

bool IECmdAnalyse::SetCommand()
{
	//2 set type
	if (m_commandSectionCount <= 1)return false;

	IEString field = *(m_commandArrays[1]);

	if (field == "ready_terrain")
	{
		//3 terrainID 4 terrainMODE
		if (m_commandSectionCount <= 2)return false;
		if (m_commandSectionCount <= 3)return false;

		IEString strTerrainID = *(m_commandArrays[2]);
		IEString strTerrainMode = *(m_commandArrays[3]);

		int terrainID = strTerrainID.transToInt();
		int terrainMode = strTerrainMode.transToInt();

		IEApplication::Share()->GetCurrentActiveScene()->GetBindedMap()->GetTerrain()->SetReadyTerrain(terrainID, (IETerrainMode)terrainMode);

		return true;
	}
	else
	{
		return false;
	}
}

bool IECmdAnalyse::AddCommand()
{
	IEString field = *(m_commandArrays[1]);

	if (field == "sprite")
	{

		return true;
	}
	else
	{
		return false;
	}
}

IE_END