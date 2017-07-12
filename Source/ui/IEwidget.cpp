#define __IE_DLL_EXPORTS__
#include "IEwidget.h"

IE_BEGIN

IEGrid IEWidget::g_wPosition = IEGrid(0, 0);

IEWidget::IEWidget()
{
	w_widgetCallback = NULL;
	w_node = NULL;
	w_parent = NULL;
	w_childs = NULL;

	w_isRelative = true;
	w_isBlock = false;
	w_isWorking = true;

	w_offset_set[0] = w_offset_set[1] = w_offset_set[2] = w_offset_set[3] = false;

	w_position = IEGrid(0, 0);
	w_Size = IEGrid(0, 0);
}

IEWidget::~IEWidget()
{
	w_widgetCallback = NULL;
	w_node = NULL;

	__IE_RELEASE__(w_childs);
}

void IEWidget::Initialization()
{
	w_childs = IEContainer::CreateAndRetain();
}

IEWidget * IEWidget::Create()
{
	IEWidget * object = new IEWidget();
	object->Initialization();
	return object;
}

void IEWidget::BindWidgetCallback(IEWidgetCallback callback, IENode * node)
{
	if (node)
	{
		w_node = node;
		w_widgetCallback = callback;
	}
	else
	{
		w_node = NULL;
		w_widgetCallback = NULL;
	}
}

void IEWidget::WidgetCallback()
{
	if (w_node && w_widgetCallback)
	{
		(w_node->*w_widgetCallback)(this);
	}
}

void IEWidget::AddWidgetChild(IEWidget * widget)
{
	w_childs->Push(widget);
	widget->SetWidgetParent(this);
}

void IEWidget::SetWidgetParent(IEWidget * widget)
{
	w_parent = widget;
}

IEWidget * IEWidget::GetWidgetLeftBrother(int offset)
{
	IEArray * parentsChilds = w_parent->GetWidgetsArray();
	int index = GetWidgetIndex();

	IEWidget * leftWidget = (IEWidget *)parentsChilds->Find(index - offset - 1);
	return leftWidget;
}

IEWidget * IEWidget::GetWidgetRightBrother(int offset)
{
	IEArray * parentsChilds = w_parent->GetWidgetsArray();
	int index = GetWidgetIndex();

	IEWidget * rightWidget = (IEWidget *)parentsChilds->Find(index + offset + 1);
	return rightWidget;
}

IEArray * IEWidget::GetWidgetsArray()
{
	return w_childs;
}

int IEWidget::GetWidgetIndex()
{
	IEArray * parentsChilds = w_parent->GetWidgetsArray();
	int index = parentsChilds->Index(this);
	return index;
}

void IEWidget::PreVisit()
{
	w_warningLine = 0.0f;

	//横向对齐
	if (w_align & WIDGET_ALIGN_LEFT)
	{

	}
	else if (w_align & WIDGET_ALIGN_CENTER)
	{
		/*w_margin[3] = (w_parent->GetWidgetSize() / 2 - GetWidgetSize() / 2).m_x;*/
	}
	else if (w_align & WIDGET_ALIGN_RIGHT)
	{

	}

	//纵向对齐
	if (w_align & WIDGET_VERALIGN_TOP)
	{

	}
	else if (w_align & WIDGET_VERALIGN_CENTER)
	{

	}
	else if (w_align & WIDGET_VERALIGN_BOTTOM)
	{
		//w_margin[0] = (w_parent->GetWidgetSize() - GetWidgetSize()).m_y;
	}
}

void IEWidget::ChangeModelMatrix()
{
	if (w_isRelative)
	{
		//如果是相对型
		IEWidget * leftWidget = GetWidgetLeftBrother();
		IEGrid move;
		IEGrid wPosition;

		if (leftWidget == NULL)
		{
			//父节点下的第一个子节点
			move = IEGrid(w_margin[3], w_margin[0]);
			wPosition = g_wPosition + IEGrid(w_margin[3], w_margin[0]);
		}
		else
		{
			if (leftWidget->GetWidgetRelativeOrAbsolute() == false)
			{
				int offset = 1;
				while ((leftWidget = GetWidgetLeftBrother(offset)) != NULL)
				{
					if (leftWidget->GetWidgetRelativeOrAbsolute() == true)
					{
						//如果为绝对型  一直获取到最左侧 相对型或者为NULL
						break;
					}
					offset++;
				}
				if (leftWidget == NULL)
				{
					//父节点下的第一个子节点
					move = IEGrid(w_margin[3], w_margin[0]);
					wPosition = g_wPosition + IEGrid(w_margin[3], w_margin[0]);

					goto NEXT;
				}
			}

			//根据左边一个元素进行计算
			move = IEGrid(leftWidget->GetWidgetSize().m_x, 0) + IEGrid(w_margin[3], w_margin[0]) - IEGrid(0, leftWidget->w_margin[0]);
			wPosition = g_wPosition + move;
		}

	NEXT:
		//是否超出父元素的框体大小
		float parentWarningLine = w_parent->GetWarningLine();
		if (wPosition.m_x + GetWidgetSize().m_x > w_parent->GetWidgetPosition().m_x + w_parent->GetWidgetSize().m_x)
		{
			move = IEGrid(-g_wPosition.m_x + w_parent->GetWidgetPosition().m_x, parentWarningLine - g_wPosition.m_y) + IEGrid(w_margin[3], w_margin[0]);
			wPosition = g_wPosition + move;
		}

		glTranslatef(move.m_x, move.m_y, 0.0f);
		this->SetWidgetPosition(wPosition.m_x, wPosition.m_y);
		g_wPosition = wPosition;

		float newWarningLine = (g_wPosition + GetWidgetSize()).m_y;
		if (newWarningLine > parentWarningLine)
		{
			w_parent->SetWarningLine(newWarningLine);
		}
	}
	else
	{
		//如果是绝对型
		IEGrid move = w_parent->GetWidgetPosition() - g_wPosition;
		glPushMatrix();

		glTranslatef(move.m_x, move.m_y, 0.0f);
		if (w_offset_set[0])
		{
			glTranslatef(0.0f, w_parent->GetWidgetSize().m_y * w_offset[0], 0.0f);
		}
		if (w_offset_set[1])
		{
			glTranslatef(w_parent->GetWidgetSize().m_x * (1 - w_offset[1]) - GetWidgetSize().m_x, 0.0f, 0.0f);
		}
		if (w_offset_set[2])
		{
			glTranslatef(0.0f, w_parent->GetWidgetSize().m_y * (1 - w_offset[2]) - GetWidgetSize().m_y, 0.0f);
		}
		if (w_offset_set[3])
		{
			glTranslatef(w_parent->GetWidgetSize().m_x * w_offset[3], 0.0f, 0.0f);
		}
		glTranslatef(w_margin[3] - w_margin[1], w_margin[0] - w_margin[2], 0.0f);
	}
}

void IEWidget::RevertModelMatrix()
{
	if (!w_isRelative)
	{
		//绝对型 回滚
		glPopMatrix();
	}
}

void IEWidget::VisitChilds()
{
	IEWidget ** widgets = (IEWidget **)w_childs->GetContainer();
	int widgetCount = w_childs->Count();
	for (int index = 0; index < widgetCount; index++)
	{
		if (widgets[index])
		{
			widgets[index]->Visit();
		}
	}
	if (widgetCount != 0)
	{
		IEGrid move = w_position - g_wPosition;
		g_wPosition = w_position;
		glTranslatef(move.m_x, move.m_y, 0.0f);
	}
}

void IEWidget::Update()
{

}

void IEWidget::DrawNode()
{
	if (w_isWorking)
	{
		glColor4f(w_color.m_r, w_color.m_g, w_color.m_b, 1.0f);

		glBegin(GL_QUADS);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f + w_Size.m_x, 1.0f);
		glVertex2f(1.0f + w_Size.m_x, 1.0f + w_Size.m_y);
		glVertex2f(1.0f, 1.0f + w_Size.m_y);
		glEnd();

		if (w_node)
		{
			RunTexture();

			if (m_shader)
			{
				glUseProgram(m_shader->GetShaderProgram());
			}
			if (m_texture)
			{
				GLuint * textureID = m_texture->GetTexture(m_textureUnit);
				glBindTexture(GL_TEXTURE_2D, *textureID);
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(1.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f + w_Size.m_x, 1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f + w_Size.m_x, 1.0f + w_Size.m_y);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(1.0f, 1.0f + w_Size.m_y);
			glEnd();
			glDisable(GL_BLEND);

			glBindTexture(GL_TEXTURE_2D, NULL);
			glUseProgram(NULL);
		}
	}
	else
	{
		glColor4f(1.0f, 0.2f, 0.2f, 1.0f);

		glBegin(GL_QUADS);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f + w_Size.m_x, 1.0f);
		glVertex2f(1.0f + w_Size.m_x, 1.0f + w_Size.m_y);
		glVertex2f(1.0f, 1.0f + w_Size.m_y);
		glEnd();
	}
}

void IEWidget::SetWidgetColor(float r, float g, float b)
{
	w_color = IEColor(r, g, b);
}

void IEWidget::SetWidgetMargin(int top, int right, int bottom, int left)
{
	w_margin[0] = top;
	w_margin[1] = right;
	w_margin[2] = bottom;
	w_margin[3] = left;
}

void IEWidget::SetWidgetOffset(float top, float right, float bottom, float left)
{
	w_offset[0] = top;
	w_offset[1] = right;
	w_offset[2] = bottom;
	w_offset[3] = left;
}

void IEWidget::SetWidgetOffsetSet(bool top, bool right, bool bottom, bool left)
{
	w_offset_set[0] = top;
	w_offset_set[1] = right;
	w_offset_set[2] = bottom;
	w_offset_set[3] = left;
}

void IEWidget::SetWidgetPosition(int x, int y)
{
	w_position = IEGrid(x, y);
}

IEGrid IEWidget::GetWidgetPosition()
{
	return w_position;
}

void IEWidget::SetWidgetSize(int w, int h)
{
	w_Size = IEGrid(w, h);
}

IEGrid IEWidget::GetWidgetSize()
{
	return w_Size;
}

void IEWidget::SetWarningLine(float warningLine)
{
	w_warningLine = warningLine;
}

float IEWidget::GetWarningLine()
{
	return w_warningLine;
}

void IEWidget::SetWidgetAlign(unsigned char alignType)
{
	w_align = alignType;
}

void IEWidget::SetWidgetWorking(bool isWorking)
{
	w_isWorking = isWorking;
}

void IEWidget::SetWidgetRelativeOrAbsolute(bool relative)
{
	w_isRelative = relative;
}

bool IEWidget::GetWidgetRelativeOrAbsolute()
{
	return w_isRelative;
}

IE_END