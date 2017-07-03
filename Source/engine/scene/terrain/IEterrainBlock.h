/***********************************
* name     : IEterrainGrid.h
* creater  : cosc
* info     : terrain grid
* date     : 2016/12/19
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TERRAIN_GRID__
#define __IE_TERRAIN_GRID__

#include "../IEBlock.h"

IE_BEGIN

typedef enum
{
	__terrain_none_mode__,
	__terrain_body_mode__,
	__terrain_bevel_mode__,
	__terrain_piece_mode__,
	__terrain_border_mode__,
}IETerrainMode;

class __IE_DLL__ IETerrainBlock :public IEBlock
{
public:
	IETerrainBlock();
	virtual ~IETerrainBlock();
	virtual void Initialization(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder);
	static IETerrainBlock * Create(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder);

public:
	void Reload(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder);

	void SetTerrainMODE(IETerrainMode mode);
	IETerrainMode GetTerrainMODE();
	bool ValidateTerrainGridMode(IETerrainMode mode);
	void SetTerrainID(unsigned int terrainID);
	unsigned int GetTerrainID();
	bool ValidateTerrainID(unsigned int terrainID);

	void AddNewCalBorder(IETerrainBlock ** grids);
	void DelOldCalBorder(IETerrainBlock ** grids);

	bool IsDisplayBorder();
	void SetDisplayTerrainBorder(int index, bool display);
	void SetBorderTextureFile(const char * textureFile);
	void SetBorderTexture(IETexture * texture);
	void SetPieceSprite(const char * textureFile);
	IESprite * GetBorderSprite();

protected:
	virtual void DrawNode();

private:
	void LoadScript();
	void DrawBorder();
	void DrawTopBorder();
	void DrawDownBorder();
	void DrawLeftBorder();
	void DrawRightBorder();
	void DrawCenterPiece();

private:
	unsigned int m_terrainID;
	IETerrainMode m_terrainMODE;

	IESprite * m_terrainBorder;
	IESprite * m_terrainPiece;
	bool m_displayExtraTerrain[5];
	bool m_displayExtraMask;
};

IE_END

#endif