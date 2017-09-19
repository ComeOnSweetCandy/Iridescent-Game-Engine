/***********************************
* name     : IEnodeProtocol.h
* creater  : cosc
* info     : node protocol
* date     : 2016/12/4
* version  : 1.0
* remark   : node protocol according display and space protocol
************************************/

#ifndef __IE_NODE_PROCOTOL__
#define __IE_NODE_PROCOTOL__

#include "../global/IEstdafx.h"
#include "../core/shader/IEshader.h"
#include "../type/IEvector.h"
#include "../type/IEcolor.h"

IE_BEGIN

class __IE_DLL__ IENodeProtocol
{
public:
	IENodeProtocol();
	~IENodeProtocol();

public:
	//space
	void SetRotate(const float &rotate);
	void SetScale(const float &scale);
	void SetAnchor(const float &x, const float &y);
	void SetTranslate(const float &x, const float &y);
	void SetDirection(const int &direction);									//��������
	void SetSize(const float &x, const float &y);
	void SetZIndex(const float &zIndex);

	float * GetTranslate();
	float * GetSize();
	int& GetDirection();
	float& GetZIndex();

	//display
	void AttachShader(IEShader * shader);
	void RemoveShader();

	void SetDisplay(bool display);												//�����Ƿ���ʾ
	void SetDrawReverse(bool reverse);											//���û��Ʒ���
	void SetBackColor(float r, float g, float b, float a);						//���ñ�����ɫ
	bool& GetDisplay();

protected:
	virtual void ChangeModelMatrix();
	virtual void RevertModelMatrix();

protected:
	float m_rotate;
	float m_scale;
	float m_anchor[2];
	float m_translate[2];
	float m_size[2];
	int m_direction;			//һ����Ϊ�˸����� ��0-7�ֱ���ʱ�����Ʒ���

	float m_matrix[16];
	float m_zIndex;

	IEShader * m_shader;		//shader
	bool m_display;				//�Ƿ���ʾ
	bool m_drawReverse;			//���Ʒ���
	float m_backColor[4];		//������ɫ
};

IE_END

#endif