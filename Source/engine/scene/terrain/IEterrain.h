/***********************************
* name     : IETerrain.h
* creater  : cosc
* info     : terrain
* date     : 2016/12/19
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TERRAIN__
#define __IE_TERRAIN__

#include "../IEBlock.h"

IE_BEGIN

typedef enum
{
	__terrain_none_mode__,
	__terrain_body_mode__,
	__terrain_bevel_mode__,
	__terrain_piece_mode__,
}IETerrainMode;

class __IE_DLL__ IETerrain :public IEBlock
{
public:
	IETerrain();
	virtual ~IETerrain();
	virtual void Initialization(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder);
	static IETerrain * Create(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder);

public:
	void Reload(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder);
	void Load(unsigned int terrainID, unsigned int order);

	void SetTerrainMODE(IETerrainMode mode);
	IETerrainMode GetTerrainMODE();
	void SetTerrainID(unsigned int terrainID);
	unsigned int GetTerrainID();

	void AddNewCalBorder(IETerrain ** grids);
	void DelOldCalBorder(IETerrain ** grids);

	bool IsDisplayBorder();
	void SetDisplayTerrainBorder(int index, bool display);
	void SetBorderTextureFile(const char * textureFile);
	void SetBorderTexture(IETexture * texture);
	void SetPieceSprite(const char * textureFile);
	IESprite * GetBorderSprite();

	void ChangeBodyIndex(unsigned int terrainID, unsigned char bodyIndex);
	void ChangePieceIndex(unsigned int terrainID, unsigned char pieceIndex);

	void ChangeBevelIndex(unsigned int terrainID, unsigned char bevelIndex);
	void ChangeBorderIndex(unsigned int terrainID, unsigned char borderIndex[4]);

protected:
	virtual void DrawNode();

private:
	void LoadScript();
	void LoadXML();
	void DrawBorder();
	void DrawTopBorder();
	void DrawDownBorder();
	void DrawLeftBorder();
	void DrawRightBorder();
	void DrawCenterPiece();

private:
	//index=>body,bevel,piece,border1,border2,border3,border4
	unsigned int m_partsIndex[7];

	unsigned int m_terrainID;
	IETerrainMode m_terrainMODE;

	IESprite * m_terrainBorder;
	IESprite * m_terrainPiece;
	IESprite * m_terrainBevel;
	bool m_displayExtraTerrain[5];
};

IE_END

#endif