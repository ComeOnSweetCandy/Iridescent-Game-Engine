#define __IE_DLL_EXPORTS__
#include "IEuiScene.h"

#include "../../engine/ui/IEslotButton.h"

IE_BEGIN

IEUiScene::IEUiScene()
{

}

IEUiScene::~IEUiScene()
{

}

void IEUiScene::Initialization()
{
	IEUiLayer::Initialization();

	//LoadHTML();
}

IEUiScene * IEUiScene::CreateAndRetain()
{
	IEUiScene * uiLayer = new IEUiScene();
	uiLayer->Initialization();
	uiLayer->IEWidget::Retain();
	return uiLayer;
}

void IEUiScene::LoadHTML()
{
	FILE * p = fopen(pOBJECT_TO_pSTRING(SETTING["UiDir"])->GetString(), "r");
	char setting[256];
	m_htmlStack = IEStack::CreateAndRetain();
	while (fgets(setting, 256, p) != NULL)
	{
		AnalyzeHTML(setting);
	}
	m_htmlStack->Release();
	fclose(p);
}

void IEUiScene::AnalyzeHTML(char * html)
{
	IEString htmlString = html;
	htmlString.DeleteChar('\t');
	htmlString.DeleteChar('\n');
	int splitCount = 0;
	IEArray * labelsArray = htmlString.SplitBy('<', '>', splitCount);
	IEString ** label = (IEString **)(labelsArray->GetContainer());

	for (int index = 0; index < labelsArray->Count(); index++)
	{
		int findedIndex = label[index]->FindString("div", 1);
		if (findedIndex != 0)
		{
			//开头不是div
			findedIndex = label[index]->FindString("/div", 1);
			if (findedIndex == 0)
			{
				//为div结束点
				label[index]->DeleteChar(' ');
				if (label[index]->Length() == 4)
				{
					m_htmlStack->PopFromEnding();
				}
				else
				{
					//除了 /div 还有其它内容 不正确格式
					__IE_WARNING__("IEUiScene : error.\n");
					return;
				}
			}
			else
			{
				__IE_WARNING__("IEUiScene : error.\n");
				return;
			}
		}
		else
		{
			//开头为div
			IEHtmlLabel * htmlLabel = new IEHtmlLabel();
			IEHtmlLabel * fatherLabel = (IEHtmlLabel *)(m_htmlStack->GetFromEnding());
			m_htmlStack->PushFromEnding(htmlLabel);

			label[index]->SubString(0, 3);
			int pushLength = label[index]->PushSeveralChar(' ');
			if (label[index]->Length() != 0)
			{
				if (pushLength == 0)
				{
					//div与后面的元素没有空格 非法
					__IE_WARNING__("IEUiScene : error.\n");
					return;
				}
			}

			while (label[index]->Length())
			{
				findedIndex = label[index]->FindCharFromIndex('\"', 0, 2);
				IEString * subString = label[index]->SubString(0, findedIndex + 1);

				IEArray * splitStringsArray = subString->SplitBy('=', splitCount);
				IEString ** splitStrings = (IEString **)(splitStringsArray->GetContainer());
				if (splitCount != 2)
				{
					//等号无为1 非法
					return;
				}

				if (*(splitStrings[0]) == "class")
				{
					AnalyzeClassValue(splitStrings[1]);
				}
				else if (*(splitStrings[0]) == "style")
				{
					AnalyzeStyleValue(splitStrings[1]);
				}
				else
				{
					//非法属性
					__IE_WARNING__("IEUiScene : error.\n");
				}

				label[index]->PushSeveralChar(' ');
			}

			//挂树上 添加样式
			if (fatherLabel)
			{
				fatherLabel->h_widget->AddWidgetChild(htmlLabel->h_widget);
			}
			else
			{
				this->AddWidgetChild(htmlLabel->h_widget);
			}
			htmlLabel->h_widget->SetWidgetSize(htmlLabel->h_width, htmlLabel->h_height);
			htmlLabel->h_widget->SetWidgetColor(((float)(htmlLabel->h_color[0])) / 256.0f, ((float)(htmlLabel->h_color[1])) / 256.0f, ((float)(htmlLabel->h_color[2])) / 256.0f);
			htmlLabel->h_widget->SetWidgetMargin(htmlLabel->h_margin[0], htmlLabel->h_margin[1], htmlLabel->h_margin[2], htmlLabel->h_margin[3]);
			htmlLabel->h_widget->SetWidgetOffset(htmlLabel->h_offset[0], htmlLabel->h_offset[1], htmlLabel->h_offset[2], htmlLabel->h_offset[3]);
			htmlLabel->h_widget->SetWidgetOffsetSet(htmlLabel->h_offset_set[0], htmlLabel->h_offset_set[1], htmlLabel->h_offset_set[2], htmlLabel->h_offset_set[3]);
			htmlLabel->h_widget->SetWidgetRelativeOrAbsolute(htmlLabel->h_relative);
		}
	}
}

void IEUiScene::AnalyzeClassValue(IEString * classString)
{
	IEHtmlLabel * htmlLabel = (IEHtmlLabel *)(m_htmlStack->GetFromEnding());
	IEString value = *classString;
	value.DeleteChar('\"');
	value.DeleteChar(' ');

	if (value == "slot")
	{
		m_slot = IESlot::Create();
		htmlLabel->h_widget = m_slot;
	}
	else if (value == "slotButton")
	{
		htmlLabel->h_widget = IESlotButton::Create();
	}
	else
	{
		htmlLabel->h_widget = IEWidget::Create();
	}
}

void IEUiScene::AnalyzeStyleValue(IEString * styleString)
{
	IEHtmlLabel * htmlLabel = (IEHtmlLabel *)(m_htmlStack->GetFromEnding());
	IEWidget * widget = htmlLabel->h_widget;
	int splitCount = 0;
	IEString style = *styleString;
	style.DeleteChar('\"');
	IEArray * splitsArray = style.SplitBy(';', splitCount);
	IEString ** strings = (IEString **)(splitsArray->GetContainer());

	if (splitCount == 0)
	{
		//style里面没有内容
		__IE_WARNING__("IEUiScene : error.\n");
	}

	for (int index = 0; index < splitsArray->Count(); index++)
	{
		IEArray * entrys = strings[index]->SplitBy(':', splitCount);
		IEString ** entry = (IEString **)(entrys->GetContainer());
		entry[0]->DeleteChar(' ');

		if (*(entry[0]) == "width")
		{
			entry[1]->DeleteString("px", 0);
			entry[1]->DeleteChar(' ');
			int width = entry[1]->transToInt();
			htmlLabel->h_width = width;
		}
		else if (*(entry[0]) == "height")
		{
			entry[1]->DeleteString("px", 0);
			entry[1]->DeleteChar(' ');
			int height = entry[1]->transToInt();
			htmlLabel->h_height = height;
		}
		else if (*(entry[0]) == "background")
		{
			entry[1]->DeleteChar(' ');
			entry[1]->DeleteChar('(');
			entry[1]->DeleteChar(')');
			entry[1]->DeleteString("rgb", 0);
			IEArray * numbers = entry[1]->SplitBy(',', splitCount);
			IEString ** number = (IEString **)(numbers->GetContainer());
			htmlLabel->h_color[0] = number[0]->transToInt();
			htmlLabel->h_color[1] = number[1]->transToInt();
			htmlLabel->h_color[2] = number[2]->transToInt();
		}
		else if (*(entry[0]) == "margin")
		{
			IEArray * numbers = entry[1]->SplitBy(' ', splitCount);
			IEString ** number = (IEString **)(numbers->GetContainer());
			if (splitCount != 4)
			{
				//margin选项的格式错误
				return;
			}

			for (int numberIndex = 0; numberIndex < 4; numberIndex++)
			{
				htmlLabel->h_margin[numberIndex] = number[numberIndex]->transToInt();
			}
		}
		else if (*(entry[0]) == "position")
		{
			entry[1]->DeleteChar(' ');
			if (*(entry[1]) == "absolute")
			{
				htmlLabel->h_relative = false;
			}
			else
			{
				htmlLabel->h_relative = true;
			}
		}
		else if (*(entry[0]) == "top")
		{
			entry[1]->DeleteChar(' ');
			float top = entry[1]->transFromPercentToFloat();
			htmlLabel->h_offset[0] = top;
			htmlLabel->h_offset_set[0] = true;
		}
		else if (*(entry[0]) == "right")
		{
			entry[1]->DeleteChar(' ');
			float right = entry[1]->transFromPercentToFloat();
			htmlLabel->h_offset[1] = right;
			htmlLabel->h_offset_set[1] = true;
		}
		else if (*(entry[0]) == "bottom")
		{
			entry[1]->DeleteChar(' ');
			float bottom = entry[1]->transFromPercentToFloat();
			htmlLabel->h_offset[2] = bottom;
			htmlLabel->h_offset_set[2] = true;
		}
		else if (*(entry[0]) == "left")
		{
			entry[1]->DeleteChar(' ');
			float left = entry[1]->transFromPercentToFloat();
			htmlLabel->h_offset[3] = left;
			htmlLabel->h_offset_set[3] = true;
		}
	}
}

IE_END