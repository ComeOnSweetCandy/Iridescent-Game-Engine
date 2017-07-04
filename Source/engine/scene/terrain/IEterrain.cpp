#define __IE_DLL_EXPORTS__
#include "IETerrain.h"

#include "IEterrainsInfoManager.h"

#include "../../../tools/IEscript.h"
#include "../../script/IEluaNode.h"
#include "../../script/IEluaPhysicPolygon.h"
#include "../../script/IEluaPhysicCircle.h"
#include "../../script/IEluaPhysicNode.h"

IE_BEGIN

IETerrain::IETerrain()
{
	m_terrainID = 0;
	m_unitPixels = 32;
	m_terrainMODE = __terrain_none_mode__;
	m_terrainBorder = NULL;
	m_terrainPiece = NULL;
}

IETerrain::~IETerrain()
{
	SetBorderTexture(NULL);
	SetPieceSprite(NULL);

	__IE_RELEASE_DIF__(m_terrainBorder);
	__IE_RELEASE_DIF__(m_terrainPiece);
}

void IETerrain::Initialization(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder)
{
	IESprite::Initialization(NULL);

	IETerrain::SetTerrainID(terrainID);
	IETerrain::SetTerrainMODE(terrainMODE);
	IETerrain::SetOrder(createdOrder);
	IETerrain::LoadScript();

	m_terrainBorder = IESprite::Create();
}

IETerrain * IETerrain::Create(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder)
{
	IETerrain * terrainGrid = new IETerrain();
	terrainGrid->Initialization(terrainID, terrainMODE, createdOrder);
	return terrainGrid;
}

void IETerrain::Reload(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder)
{
	//首先清理旧的数据


	IETerrain::SetTerrainID(terrainID);
	IETerrain::SetTerrainMODE(terrainMODE);
	IETerrain::SetOrder(createdOrder);
	IETerrain::LoadScript();
}

void IETerrain::LoadScript()
{
	if (m_terrainID == 0)
	{
		return;
	}

	IETerrainInfo * terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList(); 
	lua_State * luaScript = terrainsInfo[m_terrainID]._LuaScript;

	if (!luaScript)
	{
		luaScript = luaL_newstate();
		luaL_openlibs(luaScript);

		char scriptName[64];
		sprintf(scriptName, "%s%s%s", "../Debug/data/script/terrain/", terrainsInfo[m_terrainID]._TerrainName, ".lua");

		luaL_Reg lua_reg_libs[] =
		{
			{ "base", luaopen_base },
			{ "IEPhysicPolygon", luaopen_physicPolygon },
			{ "IEPhysicCircle", luaopen_physicCircle },
			{ "IEPhysicNode", luaopen_physicNode },
			{ NULL, NULL }
		};

		for (luaL_Reg * lua_reg = lua_reg_libs; lua_reg->func; ++lua_reg)
		{
			luaL_requiref(luaScript, lua_reg->name, lua_reg->func, 1);
			lua_pop(luaScript, 1);
		}

		if (luaL_dofile(luaScript, scriptName) != 0)
		{
			__IE_WARNING__("IEAttack : can not find luaScript file.\n");
		}

		terrainsInfo[m_terrainID]._LuaScript = luaScript;
	}

	if (lua_getglobal(luaScript, "CreatePhysic"))
	{
		lua_call(luaScript, 0, 0);

		//绑定物理节点
		IEPhysicNode * physicNode = (IEPhysicNode *)GetLuaUserdataElement(luaScript, "terrainPhysicNode");
		if (physicNode)
		{
			BindPhysicNode(physicNode);
		}
	}
	else
	{
		lua_pop(luaScript, 1);

		BindPhysicNode(NULL);
	}
}

void IETerrain::SetTerrainMODE(IETerrainMode mode)
{
	m_terrainMODE = mode;
}

IETerrainMode IETerrain::GetTerrainMODE()
{
	return m_terrainMODE;
}

void IETerrain::SetTerrainID(unsigned int terrainID)
{
	m_terrainID = terrainID;

	if (m_terrainID == 0)
	{
		IENode::SetDisplay(false);
	}
	else
	{
		IENode::SetDisplay(true);
	}
}

unsigned int IETerrain::GetTerrainID()
{
	return m_terrainID;
}

void IETerrain::DrawNode()
{
	IESprite::DrawNode();

	if (IsDisplayBorder())
	{
		DrawBorder();
	}
	if (m_terrainPiece)
	{
		DrawCenterPiece();
	}
}

void IETerrain::AddNewCalBorder(IETerrain ** grids)
{
	m_displayExtraTerrain[0] = m_displayExtraTerrain[1] = m_displayExtraTerrain[2] = m_displayExtraTerrain[3] = false;

	for (int index = 0; index < 4; index++)
	{
		if (grids[index] == NULL)
		{
			SetDisplayTerrainBorder(index, true);
		}
		else
		{
			if (grids[index]->GetTerrainID() == m_terrainID)
			{
				grids[index]->SetDisplayTerrainBorder((index + 2) % 4, false);
			}
			else if (grids[index]->GetTerrainID() == 0)
			{
				//或者隔壁的terrainID为0
				SetDisplayTerrainBorder(index, true);
				grids[index]->SetDisplayTerrainBorder((index + 2) % 4, false);
			}
			else
			{
				//必须创建的顺序大于隔壁(主要针对于map存储状况下的解决办法)
				if (m_order > grids[index]->GetOrder())
				{
					SetDisplayTerrainBorder(index, true);
					grids[index]->SetDisplayTerrainBorder((index + 2) % 4, false);
				}
			}
		}
	}
}

void IETerrain::DelOldCalBorder(IETerrain ** grids)
{
	for (int index = 0; index < 4; index++)
	{
		if (grids[index])
		{
			if (grids[index]->GetTerrainMODE() == __terrain_body_mode__)
			{
				grids[index]->SetDisplayTerrainBorder((index + 2) % 4, true);
			}
		}
	}
}

bool IETerrain::IsDisplayBorder()
{
	return m_displayExtraTerrain[0] || m_displayExtraTerrain[1] || m_displayExtraTerrain[2] || m_displayExtraTerrain[3];
}

void IETerrain::SetDisplayTerrainBorder(int index, bool display)
{
	m_displayExtraTerrain[index] = display;
}

void IETerrain::SetBorderTextureFile(const char * textureFile)
{
	m_terrainBorder->ChangeTexture(textureFile);
}

void IETerrain::SetBorderTexture(IETexture * texture)
{
	m_terrainBorder->ChangeTexture(texture);
}

IESprite * IETerrain::GetBorderSprite()
{
	return m_terrainBorder;
}

void IETerrain::SetPieceSprite(const char * textureFile)
{
	if (m_terrainPiece)
	{
		m_terrainPiece->AutoRelease();
		m_terrainPiece = NULL;
	}
	if (textureFile == NULL)
	{
		m_terrainPiece = NULL;
		m_displayExtraTerrain[4] = false;
	}
	else
	{
		m_terrainPiece = IESprite::Create(textureFile);
		m_displayExtraTerrain[4] = true;
	}
}

void IETerrain::DrawBorder()
{
	glMatrixMode(GL_MODELVIEW);

	DrawDownBorder();
	DrawRightBorder();
	DrawTopBorder();
	DrawLeftBorder();
}

void IETerrain::DrawCenterPiece()
{
	if (m_displayExtraTerrain[4])
	{
		m_terrainPiece->Visit();
	}
}

void IETerrain::DrawTopBorder()
{
	if (m_displayExtraTerrain[2])
	{
		glPushMatrix();
		glTranslatef(0.0f, m_size[1], 0.0f);
		m_terrainBorder->Visit();
		glPopMatrix();
	}
}

void IETerrain::DrawDownBorder()
{
	if (m_displayExtraTerrain[0])
	{
		glPushMatrix();
		glRotatef(180, 1.0f, 0.0f, 0.0f);
		m_terrainBorder->Visit();
		glPopMatrix();
	}
}

void IETerrain::DrawLeftBorder()
{
	if (m_displayExtraTerrain[3])
	{
		glPushMatrix();
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		m_terrainBorder->Visit();
		glPopMatrix();
	}
}

void IETerrain::DrawRightBorder()
{
	if (m_displayExtraTerrain[1])
	{
		glPushMatrix();
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, m_size[1], 0.0f);
		glTranslatef(-m_size[0], 0.0f, 0.0f);
		m_terrainBorder->Visit();
		glPopMatrix();
	}
}

IE_END