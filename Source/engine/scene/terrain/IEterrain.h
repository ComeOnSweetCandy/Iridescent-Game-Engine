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
** ��Ҫһ��IETerrainMode����ʾ��ǰterrain��״̬������piece����һ��״̬
*/
typedef enum
{
	__terrain_none_mode__,
	__terrain_body_mode__,
	__terrain_bevel_mode__,
	__terrain_piece_mode__,
}IETerrainMode;

/*
** ��Ҫһ����Ϣ���л� �������������� ��������������terrain
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
	void SetBlockPostion(int x, int y);		//����ȫ�ֶ�λ

	IETerrainMode GetTerrainMODE();
	void SetTerrainID(unsigned int terrainID);
	unsigned int GetTerrainID();

	void Serialize();				//���л����е���Ϣ
	void determinant();				//���������е���Ϣ

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
	void LoadXML();			//��XML�ж�ȡ������Ϣ
	void LoadScript();		//���ؽű��ļ�

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