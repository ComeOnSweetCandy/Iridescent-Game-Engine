/***********************************
* name     : IEprocessBar.h
* creater  : cosc
* info     : process bar
* date     : 2016/12/3
* version  : 1.0
* remark   : pure single color process bar
************************************/

#ifndef __IE_PROCESS_BAR__
#define __IE_PROCESS_BAR__

#include "IEelement.h"

IE_BEGIN

class IEProcessBar :public IEElement
{
public:
	IEProcessBar();
	~IEProcessBar();
	virtual void Initialization(float process);
	static IEProcessBar * Create(float process);

public:
	virtual void DrawNode();

	void SetProcess(float process);
	float & GetProcess();

	void DrawBorder();
	void DrawProcess();

private:
	float m_process;
	float m_borderWidth;

	void SetBorderWidth();
	void SetBorderWidth_P();
};

IE_END

#endif