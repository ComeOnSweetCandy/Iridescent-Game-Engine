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
	//������ȡ��ǰ���������Ŀ�
	IETexturePackerElement * element = (IETexturePackerElement *)(m_textureContainer->Find(index));
	if (element == NULL)
	{
		return;
	}

	//��⵱ǰλ��ջ���ĵ��Ƿ��ܹ�����
	IEGrid ** grids = (IEGrid **)(m_pointsContainer->GetContainer());
	unsigned int gridsCount = m_pointsContainer->Count();

	for (unsigned int gridIndex = 0; gridIndex < gridsCount; gridIndex++)
	{
		IEGrid * grid = grids[gridIndex];

		//�����Ѿ���ȡ���õ� ��Ҫ�б� �����б��Ƿ��пռ����ȥ
		if ((grid->m_x + element->_Width) >= m_width || (grid->m_y + element->_Height) >= m_height)
		{
			//˵���Ų���ȥ�� �Ǿ͵�Ѱ����һ��λ�õ�
			continue;
		}

		//�����ǰimage���������ʼ�� �Ƿ��������image�ཻ ���û���ཻ �����
		IEObject ** elements = (IEObject **)(m_textureContainer->GetContainer());
		unsigned int elementsCount = m_textureContainer->Count();
		bool result = true;

		for (unsigned int elementIndex = 0; elementIndex < elementsCount; elementIndex++)
		{
			IETexturePackerElement * ele = (IETexturePackerElement *)(elements[elementIndex]);

			if (ele->_X != -1 && ele->_Y != -1)
			{
				//˵���Ѿ���������
				//���� �õ����������ǰ�� λ�õĺ�������Ĳ�ֵ
				IEGrid positionOffset = IEGrid(ele->_X, ele->_Y) - IEGrid(grid->m_x, grid->m_y);

				//���Ϊ��ֵ ˵�����ұ߻����±�
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
					//����λ�õ�ͼƬ�������ͻ ��һ����
					result = false;
					break;
				}
			}
		}

		//��� ͨ����
		if (result)
		{
			//������λ��
			element->_X = grid->m_x;
			element->_Y = grid->m_y;

			//���������µ�point
			IEGrid * newGrid1 = new IEGrid(element->_X + element->_Width, element->_Y);
			IEGrid * newGrid2 = new IEGrid(element->_X, element->_Y + element->_Height);
			m_pointsContainer->Push(newGrid1);
			m_pointsContainer->Push(newGrid2);

			//ɾ���õ���point ���������
			m_pointsContainer->PopWithClean(grid);

			//��������
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

	//������ ��û���ҵ����ʵ�point ��Ҫ�������Ŀռ�
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
				//���߽���λ��
				cache.m_x = gridss[xx]->m_x;
				cache.m_y = gridss[xx]->m_y;

				gridss[xx]->m_x = gridss[yy]->m_x;
				gridss[xx]->m_y = gridss[yy]->m_y;

				gridss[yy]->m_x = cache.m_x;
				gridss[yy]->m_y = cache.m_y;
			}
			else if (gridss[xx]->m_y == gridss[yy]->m_y)
			{
				//���������� ��ô�Ƚϵڶ����� X��
				if (gridss[yy]->m_x < gridss[xx]->m_x)
				{
					//X��ֵԽ�͵Ļ�
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
				//��ôʲôҲ����
			}
		}
	}
}

IEContainer * IETexturePacker::Run()
{
	//���Ȱ���size��С�����
	m_textureContainer->Sorting();

	//�����Ƚ�0 0��������
	IEGrid * grid = new IEGrid(0);
	m_pointsContainer->Push(grid);

	SortTexture(0);

	return m_textureContainer;
}

void IETexturePacker::Save()
{
	//���ȶ�ÿ����ͼ ��ȡimage���� �����Ҫ���¶�ȡ
	IETexturePackerElement ** textures = (IETexturePackerElement **)(m_textureContainer->GetContainer());
	unsigned int count = m_textureContainer->Count();

	//��������һƬ�µĿռ���� ���ڴ����ͼ����
	int pass = 4;
	unsigned char * data = new unsigned char[m_width * m_height * pass];
	memset(data, 0, m_width*m_height*pass);

	//һ�еĿռ��С
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

		//����ͼ�ĸ߶��ж�� �͵ý��ж��ٴ�ѭ��
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