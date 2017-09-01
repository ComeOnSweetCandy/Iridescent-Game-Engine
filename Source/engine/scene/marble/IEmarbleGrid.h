/***********************************
* name     : IEmarbleGrid.h
* creater  : cosc
* info     : marble grid
* date     : 2017/5/4
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_MARBLE_GRID__
#define __IE_MARBLE_GRID__

#include "../IEBlock.h"

IE_BEGIN

class __IE_DLL__ IEMarbleGrid :public IEBlock
{
public:
	IEMarbleGrid();
	virtual ~IEMarbleGrid();
	virtual void Initialization(unsigned int marbleID);
	static IEMarbleGrid * Create(unsigned int marbleID);

public:
	void Reload(unsigned int marbleID);

	void SetMarbleID(unsigned int marbleID);
	unsigned int GetMarbleID();
	bool ValidateMarbleID(unsigned int marbleID);

	void SetDisplayBorder(int index, bool display);
	bool * GetDisplayBorder();
	void SetBorderTexture(const char * textureFile);

	void AnalyseCorner();
	void SetDisplayCorner(int index, bool display);
	bool * GetDisplayCorner();
	void SetCornerSprite(const char * textureFile);

	void SetDisplayTurner(int index, bool display);
	bool * GetDisplayTurner();
	void SetTurnerSprite(const char * textureFile);

public:
	void SetMarbleSize();
	IEGrid GetMarbleSize();

protected:
	virtual void DrawNode();
	virtual void LoadLUA();

	void DrawBorder();
	void DrawCorner();
	void DrawTurner();

private:
	unsigned int m_marbleID;

public:
	IESprite * m_marbleBorder;
	IESprite * m_marbleCorner;
	IESprite * m_marbleTurner;
	bool m_displayMarbleBorder[4];
	bool m_displayMarbleCorner[4];
	bool m_displayMarbleTurner[4];

	int m_marbleSizeX;
	int m_marbleSizeY;
};

IE_END

#endif