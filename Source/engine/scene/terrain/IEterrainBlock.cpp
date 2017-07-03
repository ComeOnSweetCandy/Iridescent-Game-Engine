#define __IE_DLL_EXPORTS__
#include "IETerrainBlock.h"

#include "IEterrainsInfoManager.h"

#include "../../../tools/IEscript.h"
#include "../../script/IEluaNode.h"
#include "../../script/IEluaPhysicPolygon.h"
#include "../../script/IEluaPhysicCircle.h"
#include "../../script/IEluaPhysicNode.h"

IE_BEGIN

IETerrainBlock::IETerrainBlock()
{
	m_terrainID = 0;
	m_unitPixels = 32;
	m_terrainMODE = __terrain_none_mode__;
	m_terrainBorder = NULL;
	m_terrainPiece = NULL;
}

IETerrainBlock::~IETerrainBlock()
{
	SetBorderTexture(NULL);
	SetPieceSprite(NULL);

	__IE_RELEASE_DIF__(m_terrainBorder);
	__IE_RELEASE_DIF__(m_terrainPiece);
}

void IETerrainBlock::Initialization(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder)
{
	IESprite::Initialization(NULL);

	SetTerrainID(terrainID);
	SetTerrainMODE(terrainMODE);
	SetOrder(createdOrder);

	LoadScript();

	m_terrainBorder = IESprite::Create();
}

IETerrainBlock * IETerrainBlock::Create(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder)
{
	IETerrainBlock * terrainGrid = new IETerrainBlock();
	terrainGrid->Initialization(terrainID, terrainMODE, createdOrder);
	return terrainGrid;
}

void IETerrainBlock::Reload(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder)
{
	SetDisplay(true);

	SetTerrainID(terrainID);
	SetTerrainMODE(terrainMODE);
	SetOrder(createdOrder);

	LoadScript();
}

void IETerrainBlock::LoadScript()
{
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

void IETerrainBlock::SetTerrainMODE(IETerrainMode mode)
{
	m_terrainMODE = mode;
}

IETerrainMode IETerrainBlock::GetTerrainMODE()
{
	return m_terrainMODE;
}

bool IETerrainBlock::ValidateTerrainGridMode(IETerrainMode mode)
{
	return m_terrainMODE == mode;
}

void IETerrainBlock::SetTerrainID(unsigned int terrainID)
{
	m_terrainID = terrainID;
}

unsigned int IETerrainBlock::GetTerrainID()
{
	return m_terrainID;
}

bool IETerrainBlock::ValidateTerrainID(unsigned int terrainID)
{
	return m_terrainID == terrainID;
}

void IETerrainBlock::DrawNode()
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

void IETerrainBlock::AddNewCalBorder(IETerrainBlock ** grids)
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
			if (grids[index]->ValidateTerrainID(m_terrainID))
			{
				grids[index]->SetDisplayTerrainBorder((index + 2) % 4, false);
			}
			else if (grids[index]->ValidateTerrainID(0))
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

void IETerrainBlock::DelOldCalBorder(IETerrainBlock ** grids)
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

bool IETerrainBlock::IsDisplayBorder()
{
	return m_displayExtraTerrain[0] || m_displayExtraTerrain[1] || m_displayExtraTerrain[2] || m_displayExtraTerrain[3];
}

void IETerrainBlock::SetDisplayTerrainBorder(int index, bool display)
{
	m_displayExtraTerrain[index] = display;
}

void IETerrainBlock::SetBorderTextureFile(const char * textureFile)
{
	m_terrainBorder->ChangeTexture(textureFile);
}

void IETerrainBlock::SetBorderTexture(IETexture * texture)
{
	m_terrainBorder->ChangeTexture(texture);
}

IESprite * IETerrainBlock::GetBorderSprite()
{
	return m_terrainBorder;
}

void IETerrainBlock::SetPieceSprite(const char * textureFile)
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

void IETerrainBlock::DrawBorder()
{
	glMatrixMode(GL_MODELVIEW);

	DrawDownBorder();
	DrawRightBorder();
	DrawTopBorder();
	DrawLeftBorder();
}

void IETerrainBlock::DrawCenterPiece()
{
	if (m_displayExtraTerrain[4])
	{
		m_terrainPiece->Visit();
	}
}

void IETerrainBlock::DrawTopBorder()
{
	if (m_displayExtraTerrain[2])
	{
		glPushMatrix();
		glTranslatef(0.0f, m_size[1], 0.0f);
		m_terrainBorder->Visit();
		glPopMatrix();
	}
}

void IETerrainBlock::DrawDownBorder()
{
	if (m_displayExtraTerrain[0])
	{
		glPushMatrix();
		glRotatef(180, 1.0f, 0.0f, 0.0f);
		m_terrainBorder->Visit();
		glPopMatrix();
	}
}

void IETerrainBlock::DrawLeftBorder()
{
	if (m_displayExtraTerrain[3])
	{
		glPushMatrix();
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		m_terrainBorder->Visit();
		glPopMatrix();
	}
}

void IETerrainBlock::DrawRightBorder()
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