#define __IE_DLL_EXPORTS__
#include "IETerrain.h"

#include "IEterrainsInfoManager.h"
#include "IETerrainArea.h"

#include "../../../tools/IEscript.h"
#include "../../script/IEluaNode.h"

#include "../../../interface/cmd/IEapplication.h"

IE_BEGIN

IETerrain::IETerrain()
{
	m_terrainID = 0;
	m_unitPixels = 32;
	m_terrainMODE = __terrain_none_mode__;
	m_piece = NULL;
}

IETerrain::~IETerrain()
{
	__IE_RELEASE_DIF__(m_piece);
	__IE_RELEASE_DIF__(m_bevel);
	__IE_RELEASES_DIF__(m_border, 4);
}

void IETerrain::Initialization(unsigned int terrainID, unsigned int createdOrder)
{
	IESprite::Initialization(NULL);
	IETerrain::Load(terrainID, createdOrder);
}

IETerrain * IETerrain::Create(unsigned int terrainID, unsigned int createdOrder)
{
	IETerrain * terrainGrid = new IETerrain();
	terrainGrid->Initialization(terrainID, createdOrder);
	return terrainGrid;
}

void IETerrain::Load(unsigned int terrainID, unsigned int Order)
{
	IETerrain::SetTerrainID(terrainID);
	IETerrain::SetOrder(Order);

	IETerrain::LoadXML();
	IETerrain::LoadScript();
}

void IETerrain::Reload(unsigned int terrainID, unsigned int Order)
{
	IETerrain::SetTerrainID(terrainID);
	IETerrain::SetOrder(Order);

	IETerrain::LoadXML();
	IETerrain::LoadScript();

	//判定border的显示与否
	ChangeBorderDisplay();
}

void IETerrain::ResetSelf()
{
	IETerrain::SetTerrainID(0);
	IETerrain::SetOrder(0);

	BindPhysicNode(NULL);
}

IETerrainInfoSerialization * IETerrain::Serialize()
{
	IETerrainInfoSerialization * serialization = new IETerrainInfoSerialization();
	serialization->_TerrainID = m_terrainID;
	serialization->_Order = m_order;

	if (m_terrainID == 0)
	{
		serialization->_BodyIndex = 0;
		serialization->_BevelIndex = 0;
		serialization->_PieceID = 0;
		serialization->_PieceIndex = 0;
		serialization->_BorderIndex[0] = 0;
		serialization->_BorderIndex[1] = 0;
		serialization->_BorderIndex[2] = 0;
		serialization->_BorderIndex[3] = 0;
	}
	else
	{
		serialization->_BodyIndex = m_textureUnit->_SameIndex + 1;

		if (m_piece)
		{
			serialization->_PieceID = m_pieceID;
			serialization->_PieceIndex = m_piece->GetTextureUnitState()->_SameIndex + 1;
		}
		else
		{
			serialization->_PieceID = 0;
			serialization->_PieceIndex = 0;
		}

		if (m_bevel)
		{
			serialization->_BevelIndex = m_piece->GetTextureUnitState()->_SameIndex + 1;
		}
		else
		{
			serialization->_BevelIndex = 0;
		}

		for (int index = 0; index < 4; index++)
		{
			if (m_border[index])
			{
				serialization->_BorderIndex[index] = m_border[index]->GetTextureUnitState()->_SameIndex + 1;
			}
			else
			{
				serialization->_BorderIndex[index] = 0;
			}
		}
	}

	return serialization;
}

void IETerrain::determinant(IETerrainInfoSerialization * serialization)
{
	SetTerrainID(serialization->_TerrainID);
	SetOrder(serialization->_Order);

	IETerrain::LoadXML();
	IETerrain::LoadScript();

	__IE_RELEASE_DIF__(m_piece);
	__IE_RELEASE_DIF__(m_bevel);
	__IE_RELEASES_DIF__(m_border, 4);

	if (m_terrainID)
	{
		//获取贴图信息
		IETerrainInfo * infos = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
		ChangeGroup("body", serialization->_BodyIndex);

		if (serialization->_PieceID && serialization->_PieceIndex)
		{
			IEPackerTexture * pieceTexture = IEPackerTexture::Create(infos[m_pieceID]._Xml->FindChild("texture"));

			m_piece = IESprite::Create();
			m_piece->ChangeTexture(pieceTexture);
			m_piece->ChangeGroup("piece", serialization->_PieceIndex);
		}
		if (serialization->_BevelIndex)
		{
			m_bevel = IESprite::Create();
			m_bevel->ChangeTexture(m_texture);
			m_bevel->ChangeGroup("bevel", serialization->_BevelIndex);
		}
		for (int index = 0; index < 4; index++)
		{
			if (serialization->_BorderIndex[index])
			{
				m_border[index] = IESprite::Create();
				m_border[index]->ChangeTexture(m_texture);
				m_border[index]->ChangeGroup("border", serialization->_BorderIndex[index]);
			}
		}
	}
}

void IETerrain::SetBlockPostion(int x, int y)
{
	m_blockPositionX = x;
	m_blockPositionY = y;
}

void IETerrain::ChangeBodyIndex(unsigned char bodyIndex)
{
	if (m_terrainID != 0)
	{
		ChangeGroup("body", bodyIndex);
	}
}

void IETerrain::ChangeBevelIndex(unsigned char bevelIndex)
{
	
}

void IETerrain::ChangePieceIndex(unsigned int terrainID, unsigned char pieceIndex)
{
	if (m_terrainID != 0 && terrainID != 0)
	{
		//如果要添加piece 必须制定terrain的id非零
		__IE_RELEASE_DIF__(m_piece);

		if (m_terrainID != terrainID)
		{
			IETerrainInfo * infos = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
			IEPackerTexture * texture = IEPackerTexture::Create(infos[terrainID]._Xml);

			m_piece = IESprite::Create();
			m_piece->ChangeTexture(texture);
			m_piece->ChangeGroup("piece", pieceIndex);

			m_pieceID = terrainID;
		}
	}
	else
	{
		__IE_RELEASE_DIF__(m_piece);
	}
}

void IETerrain::ChangeBorderIndex(unsigned char * bordersIndex)
{
	if (m_terrainID)
	{
		if (bordersIndex == NULL)
		{
			unsigned char borders[4] = { 0, 0, 0, 0 };
			bordersIndex = borders;
		}

		for (unsigned char index = 0; index < 4; index++)
		{
			if (m_border[index])
			{
				m_border[index]->ChangeGroup("border", bordersIndex[index]);
			}
		}
	}
}

void IETerrain::ChangeBorderDisplay()
{
	IETerrain * grids[4];
	static IETerrainArea * area = IEApplication::Share()->GetCurrentActiveScene()->GetBindedMap()->GetTerrain();

	grids[0] = (IETerrain *)area->GetBlock(m_blockPositionX, m_blockPositionY - 1);
	grids[1] = (IETerrain *)area->GetBlock(m_blockPositionX + 1, m_blockPositionY);
	grids[2] = (IETerrain *)area->GetBlock(m_blockPositionX, m_blockPositionY + 1);
	grids[3] = (IETerrain *)area->GetBlock(m_blockPositionX - 1, m_blockPositionY);

	for (int index = 0; index < 4; index++)
	{
		if (grids[index] == NULL)
		{
			SetBorderDisplay(index, true);
		}
		else
		{
			if (grids[index]->GetTerrainMODE() == __terrain_none_mode__)
			{
				SetBorderDisplay(index, true);
			}
			else if (grids[index]->GetTerrainMODE() == __terrain_body_mode__)
			{
				if (grids[index]->GetTerrainID() == m_terrainID)
				{
					SetBorderDisplay(index, false);
					grids[index]->SetBorderDisplay((index + 2) % 4, false);
				}
				else
				{
					//必须创建的顺序大于隔壁(主要针对于map存储状况下的解决办法)
					if (GetOrder() > grids[index]->GetOrder())
					{
						SetBorderDisplay(index, true);
						grids[index]->SetBorderDisplay((index + 2) % 4, false);
					}
					else
					{
						SetBorderDisplay(index, false);
						grids[index]->SetBorderDisplay((index + 2) % 4, true);
					}
				}
			}
		}
	}
}

void IETerrain::SetBorderDisplay(int index, bool display)
{
	if (display)
	{
		if (m_border[index] == NULL)
		{
			m_border[index] = IESprite::Create();
			m_border[index]->ChangeTexture(GetTexture());
		}
	}
	else
	{
		__IE_RELEASE_DIF__(m_border[index]);
		m_border[index] = NULL;
	}
}

void IETerrain::LoadXML()
{
	if (m_terrainID == 0)
	{
		BindPhysicNode(NULL);
		return;
	}

	IETerrainInfo * terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
	IEXml * xml = terrainsInfo[m_terrainID]._Xml;

	//load physic
	IEPhysicNode * physicNode = NULL;
	IEXml * physicXML = xml->FindChild("physic");
	const char * physicType = physicXML->FindChild("type")->ValueString();
	if (strcmp(physicType, "none") == 0)
	{
		physicNode = NULL;
	}
	BindPhysicNode(physicNode);

	//load texture
	IEXml * textureXML = xml->FindChild("texture");
	IEPackerTexture * texture = IEPackerTexture::Create(textureXML);
	ChangeTexture(texture);
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
			{ NULL, NULL }
		};

		for (luaL_Reg * lua_reg = lua_reg_libs; lua_reg->func; ++lua_reg)
		{
			luaL_requiref(luaScript, lua_reg->name, lua_reg->func, 1);
			lua_pop(luaScript, 1);
		}

		if (luaL_dofile(luaScript, scriptName) != 0)
		{
			__IE_WARNING__("IETerrain : can not find luaScript file.\n");
		}

		terrainsInfo[m_terrainID]._LuaScript = luaScript;
	}
}

IETerrainMode IETerrain::GetTerrainMODE()
{
	return m_terrainMODE;
}

void IETerrain::SetTerrainID(unsigned int terrainID)
{
	m_terrainID = terrainID;

	//如果为零 采取以下动作
	if (m_terrainID == 0)
	{
		m_terrainMODE = __terrain_none_mode__;
		SetDisplay(false);

		__IE_RELEASE_DIF__(m_piece);
		__IE_RELEASE_DIF__(m_bevel);
		__IE_RELEASES_DIF__(m_border, 4);
	}
	else
	{
		m_terrainMODE = __terrain_body_mode__;
		SetDisplay(true);
	}
}

unsigned int IETerrain::GetTerrainID()
{
	return m_terrainID;
}

void IETerrain::DrawNode()
{
	IESprite::DrawNode();

	DrawBorder();
	DrawPiece();
}

void IETerrain::DrawBorder()
{
	glMatrixMode(GL_MODELVIEW);

	//up
	if (m_border[2])
	{
		glPushMatrix();
		glTranslatef(0.0f, m_size[1], 0.0f);
		m_border[2]->Visit();
		glPopMatrix();
	}

	//down
	if (m_border[0])
	{
		glPushMatrix();
		glRotatef(180, 1.0f, 0.0f, 0.0f);
		m_border[0]->Visit();
		glPopMatrix();
	}

	//left
	if (m_border[3])
	{
		glPushMatrix();
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		m_border[3]->Visit();
		glPopMatrix();
	}

	//right
	if (m_border[1])
	{
		glPushMatrix();
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, m_size[1], 0.0f);
		glTranslatef(-m_size[0], 0.0f, 0.0f);
		m_border[1]->Visit();
		glPopMatrix();
	}
}

void IETerrain::DrawPiece()
{
	if (m_piece)
	{
		m_piece->Visit();
	}
}

IE_END