#define __IE_DLL_EXPORTS__
#include "IETexturePacker.h"

#include "../core/container/IEcontianer.h"

IE_BEGIN

IETexturePacker::IETexturePacker()
{
	m_textureContainer = NULL;
	m_width = m_height = 512;
}

IETexturePacker::~IETexturePacker()
{
	__IE_RELEASE__(m_textureContainer);
}

void IETexturePacker::Initialization(const char * textureName)
{
	m_textureName = textureName;

	m_textureContainer = IEContainer::CreateAndRetain();
	m_textureContainer->SetCompareOffset((int)&(((IETexturePackerElement *)0)->_Size));

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

void IETexturePacker::SortTexture(unsigned int index)
{
	//首先提取当前顶部的最大的块
	IETexturePackerElement * element = (IETexturePackerElement *)(m_textureContainer->Find(index));
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
		if ((grid->m_x + element->_Width) >= m_width || (grid->m_y + element->_Height) >= m_height)
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
			IETexturePackerElement * ele = (IETexturePackerElement *)(elements[elementIndex]);

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

			//IEGrid ** gridss = (IEGrid **)(m_pointsContainer->GetContainer());
			//unsigned int gridssCount = m_pointsContainer->Count();
			//for (unsigned ii = 0; ii < gridssCount; ii++)
			//{
			//	printf("%d %d\t", gridss[ii]->m_x, gridss[ii]->m_y);
			//}
			//printf("\n");

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

IEContainer * IETexturePacker::Run()
{
	//首先按照size大小排序好
	m_textureContainer->Sorting();

	//最首先将0 0这个点放入
	IEGrid * grid = new IEGrid(0);
	m_pointsContainer->Push(grid);

	SortTexture(0);

	return m_textureContainer;
}

void IETexturePacker::Save()
{
	//首先对每张贴图 读取image数据 这个需要重新读取
	IETexturePackerElement ** textures = (IETexturePackerElement **)(m_textureContainer->GetContainer());
	unsigned int count = m_textureContainer->Count();

	//首先申请一片新的空间出来 用于存放贴图数据
	int pass = 4;
	unsigned char * data = new unsigned char[m_width * m_height * pass];
	memset(data, 0, m_width*m_height*pass);

	//一行的空间大小
	unsigned hrSize = m_width * pass;

	for (unsigned int index = 0; index < count; index++)
	{
		IETexturePackerElement * texture = textures[index];
		IEImage * image = texture->_Image;
		unsigned char * imageData = image->m_imgData;
		unsigned int textureHrSize = image->m_imgWidth * pass;

		if (texture->_Image->m_imgComponents != 4)
		{
			continue;
		}

		//这张图的高度有多高 就得进行多少次循环
		for (unsigned int curHeight = 0; curHeight < texture->_Height; curHeight++)
		{
			memcpy(data + curHeight * hrSize + texture->_X * pass, imageData + curHeight * textureHrSize, texture->_Width * pass);
		}
	}

	//for (unsigned int index = 0; index < m_height; index++)
	//{
	//	*(data + index) = 0;
	//}

	IEImage * newImage = new IEImage();
	newImage->m_imgData = data;
	newImage->m_imgWidth = m_width;
	newImage->m_imgHeight = m_height;
	newImage->SavePNG("../Debug/data/test/test_0.png");
}

void IETexturePacker::AddImage(IEImage * image)
{
	IETexturePackerElement * element = new IETexturePackerElement();

	element->_Width = image->m_imgWidth;
	element->_Height = image->m_imgHeight;
	element->_Image = image;
	element->_Size = element->_Width * element->_Height;
	element->_X = -1;
	element->_Y = -1;

	m_textureContainer->Push(element);
}

void IETexturePacker::AddTexture(IETexture * texture)
{
	IETexturePackerElement * element = new IETexturePackerElement();

	element->_Width = texture->m_textureSize->m_x;
	element->_Height = texture->m_textureSize->m_y;
	element->_Texture = texture;
	element->_Size = element->_Width * element->_Height;
	element->_X = -1;
	element->_Y = -1;

	m_textureContainer->Push(element);
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