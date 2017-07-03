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
	m_pointsContainer = IEContainer::CreateAndRetain();
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

	for (unsigned int gridIndex = gridsCount - 1; gridIndex >= 0; gridIndex--)
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

			int offset = (int)&(((IEGrid *)0)->m_y);
			m_pointsContainer->Sorting(offset);

			SortTexture(index + 1);

			return;
		}
	}

	//������ ��û���ҵ����ʵ�point ��Ҫ�������Ŀռ�
	AutoEnlarge();
	SortTexture(index);
}

IEContainer * IETexturePacker::Run()
{
	//���Ȱ���size��С�����
	int offset = (int)&(((IETexturePackerElement *)0)->_Size);
	m_textureContainer->Sorting(offset);

	//�����Ƚ�0 0��������
	IEGrid * grid = new IEGrid(0);
	m_pointsContainer->Push(grid);

	SortTexture(0);

	return m_textureContainer;
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