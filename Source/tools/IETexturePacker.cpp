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
			delete deletedSameGroup;
		}

		delete[]deletedGroup->_GroupName;
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

void IETexturePacker::AddImage(IEImage * image, const char * groupName, float endTime, unsigned char sameIndex)
{
	IEPackedImage * element = new IEPackedImage();

	element->_Width = image->m_imgWidth;
	element->_Height = image->m_imgHeight;
	element->_Image = image;
	element->_Size = element->_Width * element->_Height;
	element->_X = -1;
	element->_Y = -1;

	m_textureContainer->Push(element);

	//����group�Ĵ���
	//���ȼ�� ��groupName�Ƿ����

	bool result = false;
	IEPackedGroup * group = m_textureGroupHead;
	IEPackedGroup * lastGroup = NULL;
	IEPackedGroup * lastSameGroup = NULL;
	while (group)
	{
		if (strcmp(group->_GroupName, groupName) == 0)
		{
			//����same
			IEPackedGroup * sameGroup = group;
			lastSameGroup = group;
			while (sameGroup)
			{
				if (sameGroup->_SameIndex == sameIndex)
				{
					//������ͼ�����group��
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
	//���û���ҵ�
	if (result == false)
	{
		int strLen = strlen(groupName) + 1;

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

		newGroup->_GroupName = new char[strLen];
		strcpy(newGroup->_GroupName, groupName);
		newGroup->_Next = NULL;
		newGroup->_Same = NULL;

		element->_GroupIndex = newGroup->_GroupIndex;
		newGroup->_SameIndex = sameIndex;
		element->_FrapIndex = newGroup->_FrapsCount++;
		element->_EndTime = 0.0f;						//α��
	}
}

void IETexturePacker::SaveTexture()
{
	//����xml��Ϣ�����
	Recombine();

	//���ȶ�ÿ����ͼ ��ȡimage���� �����Ҫ���¶�ȡ
	IEPackedImage ** textures = (IEPackedImage **)(m_textureContainer->GetContainer());
	unsigned int count = m_textureContainer->Count();

	//��������һƬ�µĿռ���� ���ڴ����ͼ����
	int pass = 4;
	unsigned char * data = new unsigned char[m_width * m_height * pass];
	memset(data, 0, m_width*m_height*pass);

	//һ�еĿռ��С
	unsigned hrSize = m_width * pass;

	//��һ���µ�xml�ļ�
	IEString * baseXmlDirection = (IEString *)(SETTING["xmlDir"]);
	IEString xmlFileDirection = *baseXmlDirection + m_textureName.GetString() + ".tex.xml";

	FILE * p = fopen(xmlFileDirection.GetString(), "w+");
	WriteToXml(p, "<texture>");
	//д����ͼ����
	IEString textrueName = IEString("<tex>") + m_textureName.GetString() + ".png" + "</tex>";
	WriteToXml(p, textrueName.GetString());
	//д���С
	IEString textureWidth = IEString("<width>") + (int)m_width + "</width>";
	WriteToXml(p, textureWidth.GetString());
	IEString textureHeight = IEString("<height>") + (int)m_height + "</height>";
	WriteToXml(p, textureHeight.GetString());

	//�������е�group�� �������
	IEPackedGroup * group = m_textureGroupHead;
	while (group)
	{
		//д��xml�ļ�
		WriteToXml(p, "<group>");
		//д������
		IEString groupIndex = IEString("<name>") + group->_GroupName + "</name>";
		WriteToXml(p, groupIndex.GetString());
		//д��same count
		IEString sameCount = IEString("<sameCount>") + group->_SameCount + "</sameCount>";
		WriteToXml(p, sameCount.GetString());

		IEPackedGroup * sameGroup = group;
		while (sameGroup)
		{
			//same��ͷ
			WriteToXml(p, "<same>");
			//д��frapsCount
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

					//����ͼ�ĸ߶��ж�� �͵ý��ж��ٴ�ѭ��
					for (unsigned int curHeight = 0; curHeight < texture->_Height; curHeight++)
					{
						memcpy(data + (curHeight + texture->_Y)* hrSize + texture->_X * pass, imageData + (texture->_Height - 1 - curHeight) * textureHrSize, texture->_Width * pass);
					}

					//д��frap��ͷ
					WriteToXml(p, "<frap>");
					//д��index
					IEString index = IEString("<index>") + (int)texture->_FrapIndex + "</index>";
					WriteToXml(p, index.GetString());
					//д��֡��һЩ��Ϣ
					IEString x = IEString("<x>") + (int)texture->_X + "</x>";
					WriteToXml(p, x.GetString());
					IEString y = IEString("<y>") + (int)texture->_Y + "</y>";
					WriteToXml(p, y.GetString());
					//д���Ⱥ͸߶�
					int newW = (int)(texture->_Width);
					int newH = (int)(texture->_Height);
					IEString wwidth = IEString("<width>") + newW + "</width>";
					WriteToXml(p, wwidth.GetString());
					IEString hheight = IEString("<height>") + newH + "</height>";
					WriteToXml(p, hheight.GetString());
					//д��frap�Ľ���ʱ��
					IEString end = IEString("<end>") + texture->_EndTime + "</end>";
					WriteToXml(p, end.GetString());
					//д��frap��β
					WriteToXml(p, "</frap>");
				}
			}

			//����һ��same
			WriteToXml(p, "</same>");
			sameGroup = sameGroup->_Same;
		}

		//����һ��group
		WriteToXml(p, "</group>");
		group = group->_Next;
	}

	WriteToXml(p, "</texture>");
	fclose(p);

	//�����ַ
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
	//���Ȱ���size��С�����
	m_textureContainer->Sorting();

	//�����Ƚ�0 0��������
	IEGrid * grid = new IEGrid(0);
	m_pointsContainer->Push(grid);

	//�ݹ�ķ���ȥ����
	SortTexture(0);

	return m_textureContainer;
}

void IETexturePacker::SortTexture(unsigned int index)
{
	//������ȡ��ǰ���������Ŀ�
	IEPackedImage * element = (IEPackedImage *)(m_textureContainer->Find(index));
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
		if ((grid->m_x + element->_Width) > m_width || (grid->m_y + element->_Height) > m_height)
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
			IEPackedImage * ele = (IEPackedImage *)(elements[elementIndex]);

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