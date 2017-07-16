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

/*
** 需要一个IETerrainMode来表示当前terrain的状态，但是piece不是一种状态
*/
typedef enum
{
	__terrain_none_mode__,
	__terrain_body_mode__,
	__terrain_bevel_mode__,
	__terrain_piece_mode__,
}IETerrainMode;

/*
** 需要一个信息序列化 以用来保存数据 重载数据来生成terrain
*/

class __IE_DLL__ IETerrain :public IEBlock
{
public:
	IETerrain();
	virtual ~IETerrain();
	virtual void Initialization(unsigned int terrainID, unsigned int createdOrder);
	static IETerrain * Create(unsigned int terrainID, unsigned int createdOrder);

public:
	void Reload(unsigned int terrainID, unsigned int createdOrder);
	void SetBlockPostion(int x, int y);		//进行全局定位

	IETerrainMode GetTerrainMODE();
	void SetTerrainID(unsigned int terrainID);
	unsigned int GetTerrainID();

	void Serialize();				//序列化所有的信息
	void determinant();				//解析化所有的信息

	void ChangeBodyIndex(unsigned int terrainID, unsigned char bodyIndex = 0);
	void ChangePieceIndex(unsigned int terrainID, unsigned char pieceIndex = 0);
	void ChangeBevelIndex(unsigned int terrainID, unsigned char bevelIndex);
	void ChangeBorderIndex(unsigned int terrainID, unsigned char * bordersIndex = NULL);

protected:
	virtual void DrawNode();
	void DrawBorder();
	void DrawPiece();

	void ChangeBorderDisplay();
	void SetBorderDisplay(int index, bool display);

private:
	void LoadXML();			//从XML中读取个人信息
	void LoadScript();		//加载脚本文件

private:

	struct IETerrainSerialization
	{
		unsigned int _terrainID;
		unsigned char _BodyIndex;
		unsigned char _BevelIndex;
		unsigned int _PieceID;
		unsigned char _PieceIndex;
		unsigned char _BorderIndex[4];
	};

	//index=>body,bevel,piece,border1,border2,border3,border4
	unsigned int m_partsIndex[8];

	int m_blockPositionX;
	int m_blockPositionY;
	unsigned int m_terrainID;
	IETerrainMode m_terrainMODE;

	IESprite * m_bevel;
	IESprite * m_piece;
	IESprite * m_border[4];
};

IE_END

#endif