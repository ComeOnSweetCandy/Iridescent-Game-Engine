#define __IE_DLL_EXPORTS__
#include "IEmarbleGrid.h"

#include "IEmarblesInfoManager.h"

#include "../../script/IEluaNode.h"
#include "../../script/IEluaPhysicPolygon.h"
#include "../../script/IEluaPhysicCircle.h"
#include "../../script/IEluaPhysicNode.h"

IE_BEGIN

IEMarbleGrid::IEMarbleGrid()
{
	m_marbleID = 0;
	m_unitPixels = 32;

	m_marbleSizeX = 1;
	m_marbleSizeY = 1;
}

IEMarbleGrid::~IEMarbleGrid()
{

}

void IEMarbleGrid::Initialization(unsigned int marbleID)
{
	IESprite::Initialization(NULL);

	SetMarbleID(marbleID);
	LoadScript();
}

IEMarbleGrid * IEMarbleGrid::Create(unsigned int marbleID)
{
	IEMarbleGrid * terrainGrid = new IEMarbleGrid();
	terrainGrid->Initialization(marbleID);
	return terrainGrid;
}

void IEMarbleGrid::Reload(unsigned int marbleID)
{

}

void IEMarbleGrid::LoadScript()
{
	IEMarbleInfo * terrainsInfo = IEMarblesInfoManager::Share()->GetMarblesInfoList();
	IEString scriptName = pOBJECT_TO_cSTRING(SETTING["ScriptDir"]) + "marble/" + terrainsInfo[m_marbleID]._MarbleName + ".lua";

	m_luaScript = luaL_newstate();
	luaL_openlibs(m_luaScript);

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
		luaL_requiref(m_luaScript, lua_reg->name, lua_reg->func, 1);
		lua_pop(m_luaScript, 1);
	}

	if (luaL_dofile(m_luaScript, scriptName.GetString()) != 0)
	{
		__IE_WARNING__("IEAttack : can not find m_luaScript file.\n");
	}

	lua_getglobal(m_luaScript, "CreateSoilPhysicNode");
	lua_call(m_luaScript, 0, 0);

	//绑定物理节点
	IEPhysicNode * physicNode = (IEPhysicNode *)GetLuaUserdataElement(m_luaScript, "terrainPhysicNode");
	if (physicNode)
	{
		BindPhysicNode(physicNode);
	}
}

void IEMarbleGrid::SetMarbleID(unsigned int marbleID)
{
	m_marbleID = marbleID;
}

unsigned int IEMarbleGrid::GetMarbleID()
{
	return m_marbleID;
}

bool IEMarbleGrid::ValidateMarbleID(unsigned int marbleID)
{
	return m_marbleID == marbleID;
}
	
void IEMarbleGrid::DrawNode()
{
	IESprite::DrawNode();

	DrawBorder();
	DrawCorner();
	DrawTurner();
}

void IEMarbleGrid::SetDisplayBorder(int index, bool display)
{
	m_displayMarbleBorder[index] = display;

	if (!m_displayMarbleBorder[0] &&
		!m_displayMarbleBorder[1] &&
		!m_displayMarbleBorder[2] &&
		!m_displayMarbleBorder[3])
	{
		SetBorderTexture(NULL);
	}
}

bool * IEMarbleGrid::GetDisplayBorder()
{
	return m_displayMarbleBorder;
}

void IEMarbleGrid::SetBorderTexture(const char * textureFile)
{
	if (m_marbleBorder)
	{
		m_marbleBorder->AutoRelease();
		m_marbleBorder = NULL;
	}
	if (textureFile == NULL)
	{
		m_marbleBorder = NULL;
	}
	else
	{
		m_marbleBorder = IESprite::Create(textureFile);
	}
}

void IEMarbleGrid::AnalyseCorner()
{
	SetDisplayCorner(0, m_displayMarbleBorder[0] && m_displayMarbleBorder[1]);
	SetDisplayCorner(1, m_displayMarbleBorder[1] && m_displayMarbleBorder[2]);
	SetDisplayCorner(2, m_displayMarbleBorder[2] && m_displayMarbleBorder[3]);
	SetDisplayCorner(3, m_displayMarbleBorder[3] && m_displayMarbleBorder[0]);
}

void IEMarbleGrid::SetDisplayCorner(int index, bool display)
{
	m_displayMarbleCorner[index] = display;

	if (!m_displayMarbleCorner[0] &&
		!m_displayMarbleCorner[1] &&
		!m_displayMarbleCorner[2] &&
		!m_displayMarbleCorner[3])
	{
		SetCornerSprite(NULL);
	}
}

bool * IEMarbleGrid::GetDisplayCorner()
{
	return m_displayMarbleCorner;
}

void IEMarbleGrid::SetCornerSprite(const char * textureFile)
{
	if (m_marbleCorner)
	{
		m_marbleCorner->AutoRelease();
		m_marbleCorner = NULL;
	}
	if (textureFile == NULL)
	{
		m_marbleCorner = NULL;
	}
	else
	{
		m_marbleCorner = IESprite::Create(textureFile);
	}
}

void IEMarbleGrid::SetDisplayTurner(int index, bool display)
{
	m_displayMarbleTurner[index] = display;

	if (!m_displayMarbleTurner[0] &&
		!m_displayMarbleTurner[1] &&
		!m_displayMarbleTurner[2] &&
		!m_displayMarbleTurner[3])
	{
		SetTurnerSprite(NULL);
	}
}

bool * IEMarbleGrid::GetDisplayTurner()
{
	return m_displayMarbleTurner;
}

void IEMarbleGrid::SetTurnerSprite(const char * textureFile)
{
	if (m_marbleTurner)
	{
		m_marbleTurner->AutoRelease();
		m_marbleTurner = NULL;
	}
	if (textureFile == NULL)
	{
		m_marbleTurner = NULL;
	}
	else
	{
		m_marbleTurner = IESprite::Create(textureFile);
	}
}

void IEMarbleGrid::DrawBorder()
{
	if (m_displayMarbleBorder[0])
	{
		m_marbleBorder->Visit();
	}
	if (m_displayMarbleBorder[1])
	{
		glPushMatrix();
		glRotatef(90.0f, 0.0, 0.0f, 1.0f);
		glTranslatef(0.0f, -m_size[1], 0.0f);
		m_marbleBorder->Visit();
		glPopMatrix();
	}
	if (m_displayMarbleBorder[2])
	{
		glPushMatrix();
		glRotatef(180, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -m_size[1], 0.0f);
		m_marbleBorder->Visit();
		glPopMatrix();
	}
	if (m_displayMarbleBorder[3])
	{
		glPushMatrix();
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(-m_size[0], 0.0f, 0.0f);
		m_marbleBorder->Visit();
		glPopMatrix();
	}
}

void IEMarbleGrid::DrawCorner()
{
	if (!m_marbleCorner)
	{
		return;
	}

	if (m_displayMarbleCorner[0])
	{
		glPushMatrix();
		glRotatef(90.0f, 0.0, 0.0f, 1.0f);
		glTranslatef(0.0f, -m_size[1], 0.0f);
		m_marbleCorner->Visit();
		glPopMatrix();
	}
	if (m_displayMarbleCorner[1])
	{
		glPushMatrix();
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(-m_size[0], -m_size[1], 0.0f);
		m_marbleCorner->Visit();
		glPopMatrix();
	}
	if (m_displayMarbleCorner[2])
	{
		glPushMatrix();
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -m_size[1], 0.0f);
		m_marbleCorner->Visit();
		glPopMatrix();
	}
	if (m_displayMarbleCorner[3])
	{
		m_marbleCorner->Visit();
	}
}

void IEMarbleGrid::DrawTurner()
{
	if (m_displayMarbleTurner[0])
	{
		glPushMatrix();
		glRotatef(90.0f, 0.0, 0.0f, 1.0f);
		glTranslatef(0.0f, -m_size[1], 0.0f);
		m_marbleTurner->Visit();
		glPopMatrix();
	}
	if (m_displayMarbleTurner[1])
	{
		glPushMatrix();
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(-m_size[0], -m_size[1], 0.0f);
		m_marbleTurner->Visit();
		glPopMatrix();
	}
	if (m_displayMarbleTurner[2])
	{
		glPushMatrix();
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -m_size[1], 0.0f);
		m_marbleTurner->Visit();
		glPopMatrix();
	}
	if (m_displayMarbleTurner[3])
	{
		m_marbleTurner->Visit();
	}
}

void IEMarbleGrid::SetMarbleSize()
{
	//m_marbleSizeX = m_texture->m_textureSize[0].m_x / m_unitPixels;
	//m_marbleSizeY = m_texture->m_textureSize[0].m_y / m_unitPixels;
	m_marbleSizeX = m_tex->m_textureWidth / m_unitPixels;
	m_marbleSizeY = m_tex->m_textureHeight / m_unitPixels;
}

IEGrid IEMarbleGrid::GetMarbleSize()
{
	return IEGrid(m_marbleSizeX, m_marbleSizeY);
}

IE_END