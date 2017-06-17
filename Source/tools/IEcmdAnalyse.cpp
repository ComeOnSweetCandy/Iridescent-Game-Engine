#define __IE_DLL_EXPORTS__
#include "IEcmdAnalyse.h"

#include "../core/container/IEcontianer.h"

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

void IECmdAnalyse::CommandAnalyse(char * command)
{
	IEString strCommand = command;
	int splitCount = 0;
	IEContainer * arrays = strCommand.SplitBy(' ', splitCount);
	m_commandArrays = (IEString **)arrays->GetContainer();

	FieldAnalyse();
}

void IECmdAnalyse::FieldAnalyse()
{
	IEString * field = m_commandArrays[0];

	if (strcmp(field->GetString(), "cls")==0)
	{
		system("cls");
	}
	else if (strcmp(field->GetString(), "add") == 0)
	{
		if (!AddCommand())
		{
			printf("error with add command.\n\n");
		}
	}
	else if (strcmp(field->GetString(), "set") == 0)
	{
		if (!SetCommand())
		{
			printf("error with add command.\n\n");
		}
	}
	else
	{
		printf("unkown command.\n\n");
	}
}

bool IECmdAnalyse::AddCommand()
{
	IEString * field = m_commandArrays[1];

	if (strcmp(field->GetString(), "sprite"))
	{

		return true;
	}
	else
	{
		return false;
	}
}

bool IECmdAnalyse::SetCommand()
{
	IEString * field = m_commandArrays[1];

	if (strcmp(field->GetString(), "field"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

IE_END