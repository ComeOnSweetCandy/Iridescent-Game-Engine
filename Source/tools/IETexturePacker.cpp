#define __IE_DLL_EXPORTS__
#include "IETexturePacker.h"

#include "../core/container/IEcontianer.h"
#include "../core/container/IEdictionary.h"

#include "IEXml.h"

IE_BEGIN

IETexturePacker::IETexturePacker()
{
	m_textureContainer = NULL;
	m_width = m_height = 128;
	m_groupMaxIndex = 0;
}

IETexturePacker::~IETexturePacker()
{
	__IE_RELEASE__(m_textureContainer);
	__IE_RELEASE__(m_pointsContainer);

	IEPackedGroup * group = m_textureGroupHead;
	while (group)
	{
		IEPackedGroup * deletedGroup = group;
		group = group->_Next;

		IEPackedGroup * nextSameGroup = deletedGroup->_Same;
		while (nextSameGroup)
		{
			IEPackedGroup * deletedSameGroup = nextSameGroup;
			nextSameGroup = nextSameGroup->_Next;

			delete[]deletedSameGroup->_GroupName;
			delete[]deletedSameGroup->_AssortName;
			delete deletedSameGroup;
		}

		delete[]deletedGroup->_GroupName;
		delete[]deletedGroup->_AssortName;
		delete deletedGroup;
	}
}

void IETexturePacker::Initialization(const char * textureName)
{
	m_textureName = textureName;

	m_textureContainer = IEContainer::CreateAndRetain();
	m_textureContainer->SetCompareOffset((int)&(((IEPackedImage *)0)->_Size));

	m_pointsContainer = IEContainer::CreateAndRetain();
	m_pointsContainer->SetAsc(false);
	m_pointsContainer->SetCompareOffset((int)&(((IEGrid *)0)->m_y));
}

IETexturePacker * IETexturePacker::Create(const char * textureName)
{
	IETexturePacker * texturePacker = new IETexturePacker();
	texturePacker->Initialization(textureName);
	return texturePacker;
}

void IETexturePacker::AddImage(char * imageName, const char * groupName, const char * assortName, float endTime, unsigned char sameIndex)
{
	IEImage * image = IEImage::Create();
	image->LoadImageData(imageName);

	//防止为空
	if (assortName == NULL || assortName[0] == '\0')
	{
		DealImage(image, groupName, "normal", endTime, sameIndex);
	}
	else
	{
		DealImage(image, groupName, assortName, endTime, sameIndex);
	}
}

void IETexturePacker::DealImage(IEImage * image, const char * groupName, const char * assortName, float endTime, unsigned char sameIndex)
{
	IEPackedImage * element = new IEPackedImage();

	element->_Width = image->m_imgWidth;
	element->_Height = image->m_imgHeight;
	element->_Image = image;
	element->_Size = element->_Width * element->_Height;
	element->_X = -1;
	element->_Y = -1;

	m_textureContainer->Push(element);

	//进行group的处理
	//首先检测 该groupName是否存在

	bool result = false;
	IEPackedGroup * group = m_textureGroupHead;
	IEPackedGroup * lastGroup = NULL;
	IEPackedGroup * lastSameGroup = NULL;
	while (group)
	{
		if (strcmp(group->_GroupName, groupName) == 0 && strcmp(group->_AssortName,assortName) == 0)
		{
			//遍历same
			IEPackedGroup * sameGroup = group;
			lastSameGroup = group;
			while (sameGroup)
			{
				if (sameGroup->_SameIndex == sameIndex)
				{
					//将此贴图放入该group内
					element->_GroupIndex = sameGroup->_GroupIndex;
					element->_FrapIndex = sameGroup->_FrapsCount++;
					element->_EndTime = endTime;
					element->_SameIndex = sameIndex;

					result = true;
					goto __G0_LOOP__;
				}
				lastSameGroup = sameGroup;
				sameGroup = sameGroup->_Same;
			}

			result = false;
			goto __G0_LOOP__;
		}

		lastGroup = group;
		group = group->_Next;
	}

__G0_LOOP__:
	//如果没有找到
	if (result == false)
	{
		IEPackedGroup * newGroup = new IEPackedGroup();
		newGroup->_FrapsCount = 0;

		if (lastSameGroup)
		{
			newGroup->_GroupIndex = m_groupMaxIndex++;
			group->_SameCount++;
			lastSameGroup->_Same = newGroup;
		}
		else
		{
			if (lastGroup)
			{
				newGroup->_GroupIndex = m_groupMaxIndex++;
				newGroup->_SameCount = 1;
				lastGroup->_Next = newGroup;
			}
			else
			{
				newGroup->_GroupIndex = m_groupMaxIndex++;
				newGroup->_SameCount = 1;
				m_textureGroupHead = newGroup;
			}
		}

		int strLenGroup = strlen(groupName) + 1;
		int strLenAssort = strlen(assortName) + 1;

		newGroup->_GroupName = new char[strLenGroup];
		strcpy(newGroup->_GroupName, groupName);
		newGroup->_AssortName = new char[strLenAssort];
		strcpy(newGroup->_AssortName, assortName);
		newGroup->_Next = NULL;
		newGroup->_Same = NULL;

		element->_GroupIndex = newGroup->_GroupIndex;
		newGroup->_SameIndex = sameIndex;
		element->_FrapIndex = newGroup->_FrapsCount++;
		element->_EndTime = 0.0f;						//伪造
	}
}

void IETexturePacker::SaveTexture()
{
	//进行xml信息的填充
	Recombine();

	//首先对每张贴图 读取image数据 这个需要重新读取
	IEPackedImage ** textures = (IEPackedImage **)(m_textureContainer->GetContainer());
	unsigned int count = m_textureContainer->Count();

	//首先申请一片新的空间出来 用于存放贴图数据
	int pass = 4;
	unsigned char * data = new unsigned char[m_width * m_height * pass];
	memset(data, 0, m_width*m_height*pass);

	//一行的空间大小
	unsigned hrSize = m_width * pass;

	//打开一个新的xml文件
	IEString * baseXmlDirection = (IEString *)(SETTING["xmlDir"]);
	IEString xmlFileDirection = *baseXmlDirection + m_textureName.GetString() + ".tex.xml";

	FILE * p = fopen(xmlFileDirection.GetString(), "w+");
	WriteToXml(p, "<texture>");
	//写入贴图名字
	IEString textrueName = IEString("<tex>") + m_textureName.GetString() + ".png" + "</tex>";
	WriteToXml(p, textrueName.GetString());
	//写入大小
	IEString textureWidth = IEString("<width>") + (int)m_width + "</width>";
	WriteToXml(p, textureWidth.GetString());
	IEString textureHeight = IEString("<height>") + (int)m_height + "</height>";
	WriteToXml(p, textureHeight.GetString());

	//遍历所有的group组 慢慢填充
	IEPackedGroup * group = m_textureGroupHead;
	while (group)
	{
		//写入xml文件
		WriteToXml(p, "<group>");
		//写入名字
		IEString groupName = IEString("<name>") + group->_GroupName + "</name>";
		WriteToXml(p, groupName.GetString());
		//写入组别
		IEString assortName = IEString("<assort>") + group->_AssortName + "</assort>";
		WriteToXml(p, assortName.GetString());
		//写入same count
		IEString sameCount = IEString("<sameCount>") + group->_SameCount + "</sameCount>";
		WriteToXml(p, sameCount.GetString());

		IEPackedGroup * sameGroup = group;
		while (sameGroup)
		{
			//same开头
			WriteToXml(p, "<same>");
			//写入frapsCount
			IEString frapCount = IEString("<frapsCount>") + (int)group->_FrapsCount + "</frapsCount>";
			WriteToXml(p, frapCount.GetString());

			for (unsigned int index = 0; index < count; index++)
			{
				if (sameGroup->_GroupIndex == textures[index]->_GroupIndex)
				{
					IEPackedImage * texture = textures[index];
					IEImage * image = texture->_Image;
					unsigned char * imageData = image->m_imgData;
					unsigned int textureHrSize = image->m_imgWidth * pass;

					//这张图的高度有多高 就得进行多少次循环
					for (unsigned int curHeight = 0; curHeight < texture->_Height; curHeight++)
					{
						memcpy(data + (curHeight + texture->_Y)* hrSize + texture->_X * pass, imageData + (texture->_Height - 1 - curHeight) * textureHrSize, texture->_Width * pass);
					}

					//写入frap开头
					WriteToXml(p, "<frap>");
					//写入index
					IEString index = IEString("<index>") + (int)texture->_FrapIndex + "</index>";
					WriteToXml(p, index.GetString());
					//写入帧的一些信息
					IEString x = IEString("<x>") + (int)texture->_X + "</x>";
					WriteToXml(p, x.GetString());
					IEString y = IEString("<y>") + (int)texture->_Y + "</y>";
					WriteToXml(p, y.GetString());
					//写入宽度和高度
					int newW = (int)(texture->_Width);
					int newH = (int)(texture->_Height);
					IEString wwidth = IEString("<width>") + newW + "</width>";
					WriteToXml(p, wwidth.GetString());
					IEString hheight = IEString("<height>") + newH + "</height>";
					WriteToXml(p, hheight.GetString());
					//写入frap的结束时间
					IEString end = IEString("<end>") + texture->_EndTime + "</end>";
					WriteToXml(p, end.GetString());
					//写入frap结尾
					WriteToXml(p, "</frap>");
				}
			}

			//结束一个same
			WriteToXml(p, "</same>");
			sameGroup = sameGroup->_Same;
		}

		//结束一个group
		WriteToXml(p, "</group>");
		group = group->_Next;
	}

	WriteToXml(p, "</texture>");
	fclose(p);

	//构造地址
	IEString * baseImgDirection = (IEString *)(SETTING["TexDir"]);
	IEString imgFileDirection = *baseImgDirection + m_textureName.GetString() + ".png";

	IEImage * newImage = new IEImage();
	newImage->m_imgData = data;
	newImage->m_imgWidth = m_width;
	newImage->m_imgHeight = m_height;
	newImage->SavePNG(imgFileDirection.GetString());
	newImage->ReleaseDisreference();
}

IEContainer * IETexturePacker::Recombine()
{
	//首先按照size大小排序好
	m_textureContainer->Sorting();

	//最首先将0 0这个点放入
	IEGrid * grid = new IEGrid(0);
	m_pointsContainer->Push(grid);

	//递归的方法去处理
	SortTexture(0);

	return m_textureContainer;
}

void IETexturePacker::SortTexture(unsigned int index)
{
	//首先提取当前顶部的最大的块
	IEPackedImage * element = (IEPackedImage *)(m_textureContainer->Find(index));
	if (element == NULL)
	{
		return;
	}

	//检测当前位于栈顶的点是否能够放下
	IEGrid ** grids = (IEGrid **)(m_pointsContainer->GetContainer());
	unsigned int gridsCount = m_pointsContainer->Count();

	for (unsigned int gridIndex = 0; gridIndex < gridsCount; gridIndex++)
	{
		IEGrid * grid = grids[gridIndex];

		//假设已经提取到该点 就要判别 首先判别是否有空间放下去
		if ((grid->m_x + element->_Width) > m_width || (grid->m_y + element->_Height) > m_height)
		{
			//说明放不下去了 那就得寻找下一个位置点
			continue;
		}

		//如果当前image放在这个起始点 是否会与其他image相交 如果没有相交 则放下
		IEObject ** elements = (IEObject **)(m_textureContainer->GetContainer());
		unsigned int elementsCount = m_textureContainer->Count();
		bool result = true;

		for (unsigned int elementIndex = 0; elementIndex < elementsCount; elementIndex++)
		{
			IEPackedImage * ele = (IEPackedImage *)(elements[elementIndex]);

			if (ele->_X != -1 && ele->_Y != -1)
			{
				//说明已经被放置下
				//首先 得到后者相对于前者 位置的横纵坐标的差值
				IEGrid positionOffset = IEGrid(ele->_X, ele->_Y) - IEGrid(grid->m_x, grid->m_y);

				//如果为正值 说明在右边或者下边
				int compareValueX, compareValueY;
				if (positionOffset.m_x > 0)
				{
					compareValueX = element->_Width;
				}
				else
				{
					compareValueX = ele->_Width;
				}

				if (positionOffset.m_y > 0)
				{
					compareValueY = element->_Height;
				}
				else
				{
					compareValueY = ele->_Height;
				}

				positionOffset.Abs();

				if (positionOffset.m_x < compareValueX && positionOffset.m_y < compareValueY)
				{
					//与别的位置的图片会产生冲突 下一个点
					result = false;
					break;
				}
			}
		}

		//如果 通过了
		if (result)
		{
			//赋予其位置
			element->_X = grid->m_x;
			element->_Y = grid->m_y;

			//产生两个新的point
			IEGrid * newGrid1 = new IEGrid(element->_X + element->_Width, element->_Y);
			IEGrid * newGrid2 = new IEGrid(element->_X, element->_Y + element->_Height);
			m_pointsContainer->Push(newGrid1);
			m_pointsContainer->Push(newGrid2);

			//删除用掉的point 并且清理掉
			m_pointsContainer->PopWithClean(grid);

			//进行排序
			//m_pointsContainer->Sorting();
			SortPoints();

			SortTexture(index + 1);

			return;
		}
	}

	//找完了 都没有找到合适的point 就要申请更多的空间
	AutoEnlarge();
	SortTexture(index);
}

void IETexturePacker::SortPoints()
{
	IEGrid ** gridss = (IEGrid **)(m_pointsContainer->GetContainer());
	unsigned int gridssCount = m_pointsContainer->Count();
	IEGrid cache;

	for (unsigned int xx = 0; xx < gridssCount; xx++)
	{
		for (unsigned int yy = xx + 1; yy < gridssCount; yy++)
		{
			if (gridss[xx]->m_y > gridss[yy]->m_y)
			{
				//两者交换位置
				cache.m_x = gridss[xx]->m_x;
				cache.m_y = gridss[xx]->m_y;

				gridss[xx]->m_x = gridss[yy]->m_x;
				gridss[xx]->m_y = gridss[yy]->m_y;

				gridss[yy]->m_x = cache.m_x;
				gridss[yy]->m_y = cache.m_y;
			}
			else if (gridss[xx]->m_y == gridss[yy]->m_y)
			{
				//如果两者相等 那么比较第二个数 X数
				if (gridss[yy]->m_x < gridss[xx]->m_x)
				{
					//X的值越低的话
					cache.m_x = gridss[xx]->m_x;
					cache.m_y = gridss[xx]->m_y;

					gridss[xx]->m_x = gridss[yy]->m_x;
					gridss[xx]->m_y = gridss[yy]->m_y;

					gridss[yy]->m_x = cache.m_x;
					gridss[yy]->m_y = cache.m_y;
				}
			}
			else
			{
				//那么什么也不做
			}
		}
	}
}

void IETexturePacker::AutoEnlarge()
{
	if (m_width == m_height)
	{
		m_height = m_height * 2;
	}
	else
	{
		m_width = m_width * 2;
	}
}

 IE_END