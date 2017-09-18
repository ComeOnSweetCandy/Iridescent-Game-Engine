#define __IE_DLL_EXPORTS__
#include "IEMap.h"

#include "terrain/IEterrainArea.h"
#include "thing/IEThingArea.h"
#include "marble/IEmarble.h"
#include "path/IEPathArea.h"
#include "../../ai/IEPathFinder.h"

#include "../../core/IEcamera.h"
#include "../../control/IEmouse.h"
#include "../../control/IEkeyboard.h"

IE_BEGIN

IEMap::IEMap()
{
	m_chunkSideLength = 16;
	m_visibleRadius = 1;
	m_unitChunkBlockCount = m_chunkSideLength * m_chunkSideLength;

	m_activeSceneType = __ie_scene_terrain__;
	m_sceneEditMode = __ie_sceneEdit_choose__;
	m_curTerrain = NULL;
	m_curMarble = NULL;
	m_curThing = NULL;
	m_curPath = NULL;
	m_pathFinder = NULL;

	m_terrainBlockSize = sizeof(IETerrainSerialization);
	m_marbleBlockSize = sizeof(IEMarbleBlockFormat);
	m_thingBlockSize = sizeof(IEThingBlockFormat);
}

IEMap::~IEMap()
{
	__IE_RELEASE_DIF__(m_pathFinder);

	__IE_DELETES__(m_terrainChunksIndex);
	__IE_DELETES__(m_marbleChunksIndex);
	__IE_DELETES__(m_thingChunksIndex);

	__IE_DELETES__(m_terrainsSerialization);
	__IE_DELETES__(m_marbleBlocksList);
	__IE_DELETES__(m_thingBlocksList);

	__IE_FCLOSE__(m_terrainFile);
	__IE_FCLOSE__(m_marbleFile);
	__IE_FCLOSE__(m_thingFile);

	__IE_FCLOSE__(m_terrainIndexFile);
	__IE_FCLOSE__(m_marbleIndexFile);
	__IE_FCLOSE__(m_thingIndexFile);
}

void IEMap::Initialization(char * sceneName)
{
	IELayer::Initialization();

	m_sceneName = sceneName;

	//��ͼ
	m_curPath = IEPathArea::Create(this, m_visibleRadius, m_chunkSideLength);
	m_curTerrain = IETerrainArea::Create(this, m_visibleRadius, m_chunkSideLength);
	m_curThing = IEThingArea::Create(this, m_visibleRadius, m_chunkSideLength);
	//m_curMarble = IEMarble::Create(this, m_visibleRadius, m_chunkSideLength);

	//m_activeArea = m_curThing;

	//Ѱ·�㷨
	m_pathFinder = IEPathFinder::Create(m_curPath);
	m_pathFinder->SetPath(m_curPath);

	IENode::AddChild(m_curPath);
	IENode::AddChild(m_curTerrain);
	IENode::AddChild(m_curThing);
	//IENode::AddChild(m_curMarble);

	PreloadMap();
	LoadMap();
}

IEMap * IEMap::Create(char * sceneName)
{
	IEMap * map = new IEMap();
	map->Initialization(sceneName);
	return map;
}

void IEMap::PreloadMap()
{
	//�ַ������� �����ļ�·��
	IEString * base = (IEString *)SETTING["BASEDIR"];
	IEString sceneFileName = *base + "map/" + m_sceneName;
	m_sceneTerrainName = sceneFileName + "_terrain";
	m_sceneMarbleName = sceneFileName + "_marble";
	m_sceneThingName = sceneFileName + "_thing";

	//����������ļ� ��ʼ��
	InitAreaFile(m_sceneTerrainName);
	InitAreaFile(m_sceneMarbleName);
	InitAreaFile(m_sceneThingName);

	//��ȡarea������
	LoadTerrainChunkIndex();
	LoadMarbleChunkIndex();
	LoadThingChunkIndex();

	//���뻺��ռ�
	m_terrainsSerialization = new IETerrainSerialization[m_unitChunkBlockCount];
	m_marbleBlocksList = new IEMarbleBlockFormat[m_unitChunkBlockCount];
	m_thingBlocksList = new IEThingBlockFormat[m_unitChunkBlockCount];

	//���ļ�
	m_terrainFile = fopen(m_sceneTerrainName.GetString(), "rb+");
	m_marbleFile = fopen(m_sceneMarbleName.GetString(), "rb+");
	m_thingFile = fopen(m_sceneThingName.GetString(), "rb+");
}

void IEMap::InitAreaFile(IEString &fileName)
{
	unsigned int order = 1;
	unsigned int indexCount = 0;

	//terrain
	int exits = _access(fileName.GetString(), 0);
	if (exits != 0)
	{
		FILE * fp = fopen(fileName.GetString(), "wb");
		fclose(fp);
	}
	exits = _access((fileName + "_index").GetString(), 0);
	if (exits != 0)
	{
		FILE * fp = fopen((fileName + "_index").GetString(), "wb");

		fwrite(&order, sizeof(int), 1, fp);
		fwrite(&indexCount, sizeof(int), 1, fp);
		fclose(fp);
	}
}

void IEMap::SaveMap()
{
	SaveTerrain();
	SaveThing();
	//SaveMarble();
}

void IEMap::LoadMap()
{
	m_curTerrain->LoadChunks();
	//m_curMarble->LoadChunks();
	m_curThing->LoadChunks();
	m_curPath->LoadChunks();
}

void IEMap::Update()
{
	IEVector cameraPosition = IECamera::Share()->GetGameraPosition();
	IEGrid cameraGrid = cameraPosition;

	m_curTerrain->SetCenterBlockLocation(cameraGrid.m_x, cameraGrid.m_y);
	//m_curMarble->SetCenterBlockLocation(cameraGrid);
	m_curThing->SetCenterBlockLocation(cameraGrid.m_x, cameraGrid.m_y);

	InputHandle();
}

void IEMap::InputHandle()
{
	if (m_activeArea)
	{
		static bool isMouseFree = true;		//����Ƿ��ͷ�

		m_activeArea->MouseMove(IEMouse::Share()->_MousePositionX, IEMouse::Share()->_MousePositionY);

		//����������ʱ��
		if (IEMouse::Share()->IsMouseIn())
		{
			if (IEKeyboard::Share()->IsKeyDown(DIK_LSHIFT) && IEMouse::Share()->IsButtonDown(0))
			{
				//���ˢ λ��ֹˢ���ظ�ˢͬһ���ط�
				static int lastKeydownLocationX, lastKeydownLocationY;

				if (isMouseFree == true)
				{
					isMouseFree = false;

					m_activeArea->MouseBrush();
				}
				else if (lastKeydownLocationX != IEMouse::Share()->_MouseLocationX || lastKeydownLocationY != IEMouse::Share()->_MouseLocationY)
				{
					m_activeArea->MouseBrush();
				}
				lastKeydownLocationX = IEMouse::Share()->_MouseLocationX;
				lastKeydownLocationY = IEMouse::Share()->_MouseLocationY;
			}
			else if (IEMouse::Share()->IsButtonTouch(0))
			{
				//������һ�ε����ĵ��
				m_activeArea->MouseClick();
			}
			else if (IEMouse::Share()->IsButtonTouch(1))
			{
				//ȡ��ѡ�е����� ����ReadyID��ѡ�е���Ʒ����������
				m_activeArea->MouseCancel();
			}
			else
			{
				isMouseFree = true;
			}
		}

		//�����º��˼���ʱ��
		if (IEKeyboard::Share()->KeyTouch(DIK_BACK))
		{
			m_activeArea->RollbackAlter();
		}
		if (IEKeyboard::Share()->IsKeyDown(DIK_LSHIFT) && IEKeyboard::Share()->IsKeyDown(DIK_BACK))
		{
			m_activeArea->RollbackAlter();
		}
	}
}

IEPathArea * IEMap::GetPath()
{
	return m_curPath;
}

IETerrainArea * IEMap::GetTerrain()
{ 
	return m_curTerrain;
}

IEMarble * IEMap::GetMarble()
{
	return m_curMarble;
}

IEThingArea * IEMap::GetThing()
{ 
	return m_curThing; 
}

void IEMap::SetEditArea(int __map_edit_type__)
{
	if (__map_edit_type__ == __MAP_EDIT_TERRAIN__)
	{
		m_activeArea = m_curTerrain;
	}
	else if (__map_edit_type__ == __MAP_EDIT_THING__)
	{
		m_activeArea = m_curThing;
	}
	else if (__map_edit_type__ == __MAP_EDIT_MARBLE__)
	{
		m_activeArea = m_curMarble;
	}
}

void IEMap::BuildPath(IEPhysicNode * physicNode)
{
	m_curPath->ReckonAddPath(physicNode);
}

IEArray * IEMap::FindPath(IEPhysicNode * physicNode, IEVector staPosition, IEVector endPosition)
{
	return m_pathFinder->FindPath(physicNode, staPosition, endPosition);
}

void IEMap::SaveTerrain()
{
	//��ȡ��Ŀǰ�Ĵ���˳��
	m_terrainOrder = m_curTerrain->GetCurOrder();

	//��terrain�Ĳ���
	IEContainer * terrainAlters = m_curTerrain->GetAlters();
	terrainAlters->ReverseSpace();

	//Ȼ��д��ı�Ķ���
	while (IETerrainAlter * controll = (IETerrainAlter *)(terrainAlters->PopTop()))
	{
		static int chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY;
		m_curTerrain->LocationTranslate(controll->_X, controll->_Y, chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY);

		int existTerrainChunkIndex = -1;
		for (unsigned int terrainIndex = 0; terrainIndex < m_terrainIndexCount; terrainIndex++)
		{
			if (m_terrainChunksIndex[terrainIndex]._X == chunkLocationX && m_terrainChunksIndex[terrainIndex]._Y == chunkLocationY)
			{
				existTerrainChunkIndex = terrainIndex;
				break;
			}
		}

		if (existTerrainChunkIndex >= 0)
		{
			//����Ѿ�����index �Ͷ�Ӧ�� chunk�� �޸ļ���
			fseek(m_terrainFile, 0, SEEK_SET);
			fseek(m_terrainFile, m_unitChunkBlockCount * m_terrainBlockSize * existTerrainChunkIndex, SEEK_SET);
			fseek(m_terrainFile, (explicitBlockLocationX * m_chunkSideLength + explicitBlockLocationY) * m_terrainBlockSize, SEEK_CUR);

			//ֱ�Ӹ���
			fwrite(controll->_CurtTerrainInfoSerialization, m_terrainBlockSize, 1, m_terrainFile);
			fseek(m_terrainFile, 0, SEEK_SET);
		}
		else
		{
			//�����µ�
			fseek(m_terrainIndexFile, 0, SEEK_END);

			IEChunkIndex newChunkIndex;
			newChunkIndex._X = chunkLocationX;
			newChunkIndex._Y = chunkLocationY;
			newChunkIndex._BlockOffset = m_terrainIndexCount++;
			fwrite(&newChunkIndex, sizeof(IEChunkIndex), 1, m_terrainIndexFile);
			fseek(m_terrainIndexFile, 0, SEEK_SET);

			//�½���chunk��Ҫȫ���������
			IETerrainSerialization zero;
			memset(&zero, 0, m_terrainBlockSize);

			fseek(m_terrainFile, 0, SEEK_END);

			for (int index = 0; index < m_unitChunkBlockCount; index++)
			{
				fwrite(&zero, m_terrainBlockSize, 1, m_terrainFile);
			}
			fseek(m_terrainFile, 0, SEEK_SET); 

			//�ع�ͷ�����޸�
			fseek(m_terrainFile, m_unitChunkBlockCount * m_terrainBlockSize * existTerrainChunkIndex, SEEK_END);
			fseek(m_terrainFile, (explicitBlockLocationX * m_chunkSideLength + explicitBlockLocationY) * m_terrainBlockSize, SEEK_CUR);

			//ֱ�Ӹ���
			fwrite(controll->_CurtTerrainInfoSerialization, m_terrainBlockSize, 1, m_terrainFile);
			fseek(m_terrainFile, 0, SEEK_SET);

			//��ȡ�µ� ������
			fwrite(&m_terrainOrder, sizeof(int), 1, m_terrainIndexFile);
			fwrite(&m_terrainIndexCount, sizeof(int), 1, m_terrainIndexFile);
			fseek(m_terrainIndexFile, sizeof(int)* 2, SEEK_SET);

			if (m_terrainChunksIndex != NULL)
			{
				delete[]m_terrainChunksIndex;
			}

			m_terrainChunksIndex = new IEChunkIndex[m_terrainIndexCount];
			fread(m_terrainChunksIndex, sizeof(IEChunkIndex), m_terrainIndexCount, m_terrainIndexFile);
		}
	}
}

void IEMap::LoadTerrainChunkIndex()
{
	//���ȶ������е���������
	m_terrainIndexFile = fopen((m_sceneTerrainName + "_index").GetString(), "rb+");

	fread(&m_terrainOrder, sizeof(int), 1, m_terrainIndexFile);
	fread(&m_terrainIndexCount, sizeof(int), 1, m_terrainIndexFile);
	m_curTerrain->SetCurOrder(m_terrainOrder);

	//��ֹ����Ϊ��
	if (m_terrainIndexCount == 0)
	{
		return;
	}
	else
	{
		m_terrainChunksIndex = new IEChunkIndex[m_terrainIndexCount];
		fread(m_terrainChunksIndex, sizeof(IEChunkIndex), m_terrainIndexCount, m_terrainIndexFile);
	}
}

void IEMap::LoadTerrainChunk(int blockX, int blockY)
{
	if (!m_curTerrain)
	{
		return;
	}

	int existTerrainChunkIndex = -1;
	for (unsigned int terrainIndex = 0; terrainIndex < m_terrainIndexCount; terrainIndex++)
	{
		if (m_terrainChunksIndex[terrainIndex]._X == blockX && m_terrainChunksIndex[terrainIndex]._Y == blockY)
		{
			existTerrainChunkIndex = terrainIndex;
			break;
		}
	}

	if (existTerrainChunkIndex >= 0)
	{
		fseek(m_terrainFile, m_unitChunkBlockCount * m_terrainBlockSize * existTerrainChunkIndex, SEEK_SET);
		fread(m_terrainsSerialization, m_terrainBlockSize, m_unitChunkBlockCount, m_terrainFile);
		
		m_curTerrain->LoadChilds(m_terrainsSerialization, blockX, blockY);
	}
	else
	{
		m_curTerrain->LoadChilds(NULL, blockX, blockY);
	}
}

void IEMap::SaveMarble()
{
	//IEString marbleDirection = m_sceneMarbleName;

	////���ȶ������е���������
	//FILE * marbleIndexFile = fopen((marbleDirection + "_index").GetString(), "rb+");
	//IEChunkIndex * blockIndexs = NULL;
	//int blockIndexCount = 0;

	//fread(&blockIndexCount, sizeof(int), 1, marbleIndexFile);

	//if (blockIndexCount != 0)
	//{
	//	blockIndexs = new IEChunkIndex[blockIndexCount];
	//	fread(blockIndexs, sizeof(IEChunkIndex), blockIndexCount, marbleIndexFile);
	//}

	////��terrain�Ĳ���
	//FILE * marbleFile = fopen(marbleDirection.GetString(), "rb+");
	//IEContainer * terrainControlls = m_curTerrain->m_terrainAlters;
	//int controllsCount = terrainControlls->Count();

	////Ȼ��д��ı�Ķ���
	//while (IEObject * obj = terrainControlls->PopTop())
	//{
	//	IEMarbleAlterCache * controll = (IEMarbleAlterCache *)obj;
	//	IEGrid worldPosition = IEGrid(controll->_X, controll->_Y);
	//	IEGrid blockPosition = IEGrid(0, 0);
	//	IEGrid gridPosition = IEGrid(0, 0);
	//	m_curTerrain->LocationTranslate(worldPosition, gridPosition, blockPosition);

	//	//��Ϊ�����еĸ�����
	//	controll->_X = gridPosition.m_x;
	//	controll->_Y = gridPosition.m_y;

	//	int existMarbleBlockIndex = -1;
	//	for (int marbleIndex = 0; marbleIndex < blockIndexCount; marbleIndex++)
	//	{
	//		if (blockIndexs[marbleIndex]._X == blockPosition.m_x && blockIndexs[marbleIndex]._Y == blockPosition.m_y)
	//		{
	//			existMarbleBlockIndex = marbleIndex;
	//			break;
	//		}
	//	}

	//	if (existMarbleBlockIndex >= 0)
	//	{
	//		//�޸ļ���
	//		fseek(marbleFile, m_chunkSideLength * m_chunkSideLength * s_terrainGridSize * existMarbleBlockIndex, SEEK_SET);
	//		fseek(marbleFile, (gridPosition.m_x * m_chunkSideLength + gridPosition.m_y) * s_marbleGridSize, SEEK_CUR);

	//		IEMarbleAlterCache info;
	//		fwrite(&(controll->_MarbleInfo), s_marbleGridSize, 1, marbleFile);
	//		fseek(marbleFile, 0, SEEK_SET);
	//	}
	//	else
	//	{
	//		//�����µ�
	//		fseek(marbleIndexFile, 0, SEEK_END);

	//		IEChunkIndex newMarbleIndex;
	//		newMarbleIndex._X = blockPosition.m_x;
	//		newMarbleIndex._Y = blockPosition.m_y;
	//		newMarbleIndex._BlockOffset = blockIndexCount++;
	//		fwrite(&newMarbleIndex, sizeof(IEChunkIndex), 1, marbleIndexFile);
	//		fseek(marbleIndexFile, 0, SEEK_SET);

	//		IEMarbleAlterCache cache;
	//		cache._MarbleInfo._MarbleID = 0;
	//		fseek(marbleFile, 0, SEEK_END);
	//		for (int index = 0; index < m_chunkSideLength * m_chunkSideLength; index++)
	//		{
	//			fwrite(&(cache._MarbleInfo), s_marbleGridSize, 1, marbleFile);
	//		}
	//		fseek(marbleFile, 0, SEEK_SET);

	//		fseek(marbleFile, m_chunkSideLength * m_chunkSideLength * s_marbleGridSize * existMarbleBlockIndex, SEEK_END);
	//		fseek(marbleFile, (gridPosition.m_x * m_chunkSideLength + gridPosition.m_y) * s_marbleGridSize, SEEK_CUR);

	//		fwrite(&(controll->_MarbleInfo), s_marbleGridSize, 1, marbleFile);
	//		fseek(marbleFile, 0, SEEK_SET);

	//		//��ȡ�µ� ������
	//		fseek(marbleIndexFile, sizeof(int), SEEK_SET);
	//		if (blockIndexs)
	//		{
	//			delete[]blockIndexs;
	//		}
	//		blockIndexs = new IEChunkIndex[blockIndexCount];
	//		fread(blockIndexs, sizeof(IEChunkIndex), blockIndexCount, marbleIndexFile);
	//	}
	//}

	//fseek(marbleIndexFile, 0, SEEK_SET);
	//fwrite(&blockIndexCount, sizeof(int), 1, marbleIndexFile);

	//fclose(marbleIndexFile);
	//fclose(marbleFile);
}

void IEMap::LoadMarbleChunkIndex()
{
	////���ȶ������е���������
	//IEString marbleDirection = m_sceneMarbleFileDirection;
	//FILE * marbleIndexFile = fopen((marbleDirection + "_index").GetString(), "rb");

	//fread(&m_marbleIndexCount, sizeof(unsigned int), 1, marbleIndexFile);

	////��ֹ����Ϊ��
	//if (m_marbleIndexCount == 0)
	//{
	//	return;
	//}
	//else
	//{
	//	m_marbleChunksIndex = new IEChunkIndex[m_marbleIndexCount];
	//	fread(m_marbleChunksIndex, sizeof(IEChunkIndex), m_marbleIndexCount, marbleIndexFile);
	//}
}

void IEMap::LoadMarbleChunk(int blockX, int blockY)
{
	//if (!m_curMarble)
	//{
	//	return;
	//}

	//int existMarbleBlockIndex = -1;
	//for (unsigned int marbleIndex = 0; marbleIndex < m_terrainIndexCount; marbleIndex++)
	//{
	//	if (m_terrainChunksIndex[marbleIndex]._X == blockX && m_terrainChunksIndex[marbleIndex]._Y == blockY)
	//	{
	//		existMarbleBlockIndex = marbleIndex;
	//		break;
	//	}
	//}

	//if (existMarbleBlockIndex >= 0)
	//{
	//	fseek(m_marbleFile, m_unitChunkBlockCount * s_marbleGridSize * existMarbleBlockIndex, SEEK_SET);
	//	fread(m_marbleAlterInfos, sizeof(IETerrainAlterInfo), m_unitChunkBlockCount, m_marbleFile);

	//	m_curMarble->LoadChild(blockX, blockY, m_marbleAlterInfos);
	//}
	//else
	//{
	//	m_curMarble->LoadChild(blockX, blockY, NULL);
	//}
}

#include "../../core/container/IEdictionary.h"

void IEMap::SaveThing()
{
	//��ȡ��Ŀǰ�Ĵ���˳��
	m_thingOrder = m_curThing->GetCurOrder();

	//��adorning�Ĳ���
	IEContainer * thingAlters = m_curThing->GetAlters();

	//Ҫ�õ����ַ���
	char str[16];
	IEThingBlockFormat blockFormat;

	//Ȼ��д��ı�Ķ���
	while (IEThingAlter * controll = (IEThingAlter *)(thingAlters->PopTop()))
	{
		IEGrid blockLocation = IEGrid(controll->_X, controll->_Y);

		static int chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY;
		IEGrid chunkLocation = IEGrid(chunkLocationX, chunkLocationY);
		IEGrid explicitBlockLocation = IEGrid(explicitBlockLocationX, explicitBlockLocationY);

		m_curThing->LocationTranslate(controll->_X, controll->_Y, chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY);
		//m_curThing->LocationTranslate(blockLocation, chunkLocation, explicitBlockLocation);

		sprintf(str, "%d_%d", chunkLocation.m_x, chunkLocation.m_y);
		IEThingChunkIndex * chunkIndex = (IEThingChunkIndex *)RESOURCE[str];
		IEThingChunkIndex * cacheIndex = NULL;
		int cacheNumber;

		//һ���µ�block
		IEThingBlockFormat newBlockFormat;
		newBlockFormat._X = controll->_X;
		newBlockFormat._Y = controll->_Y;
		newBlockFormat._TinyX = controll->_TinyX;
		newBlockFormat._TinyY = controll->_TinyY;
		newBlockFormat._ThingID = controll->_ThingID;
		newBlockFormat._Order = controll->_Order;
		newBlockFormat._ExtraOrder = controll->_ExtraOrder;
		newBlockFormat._OperaType = controll->_OperaType;

		if (chunkIndex)
		{
			while (chunkIndex)
			{
				fseek(m_thingFile, m_unitChunkBlockCount * m_thingBlockSize * chunkIndex->_BlockOffset, SEEK_SET);

				for (int index = 0; index < m_unitChunkBlockCount; index++)
				{
					fread(&blockFormat, sizeof(IEThingBlockFormat), 1, m_thingFile);

					if (blockFormat._X == controll->_X && blockFormat._Y == controll->_Y && blockFormat._TinyX == controll->_TinyX && blockFormat._TinyY == controll->_TinyY)
					{
						//�ҵ��Ѿ����ڵĵ�
						fseek(m_thingFile, -(int)sizeof(IEThingBlockFormat), SEEK_CUR);
						fwrite(controll, sizeof(IEThingBlockFormat), 1, m_thingFile);
						fseek(m_thingFile, 0, SEEK_SET);
					}
					if (cacheIndex == NULL && blockFormat._ThingID == 0)
					{
						//��¼��ǰ��λ
						cacheIndex = chunkIndex;
						cacheNumber = index;
					}
				}

				if (chunkIndex->_Next == NULL && cacheIndex == NULL && blockFormat._ThingID == 0)
				{
					//��chunk ����û�п�λ ��Ҫ�½�
					IEThingChunkIndex newChunkIndex;
					newChunkIndex._X = chunkLocation.m_x;
					newChunkIndex._Y = chunkLocation.m_y;
					newChunkIndex._BlockOffset = m_thingIndexCount++;
					newChunkIndex._Next = (IEThingChunkIndex *)chunkIndex->_BlockOffset;

					fseek(m_thingIndexFile, 0, SEEK_END);
					fwrite(&newChunkIndex, sizeof(IEThingChunkIndex), 1, m_thingIndexFile);
					fseek(m_thingIndexFile, 0, SEEK_SET);

					//�ӵ�һblock��λ��д��block
					fseek(m_thingFile, -m_thingBlockSize * m_unitChunkBlockCount, SEEK_CUR);
					fwrite(&newBlockFormat, sizeof(IEThingBlockFormat), 1, m_thingFile);
					fseek(m_thingFile, 0, SEEK_SET);

					newChunkIndex._Next = NULL;
					chunkIndex->_Next = &newChunkIndex;
				}

				chunkIndex = chunkIndex->_Next;
			}

			//���������block ��Ҫ�½�
			if (cacheIndex)
			{
				//�п�λ д��block
				fseek(m_thingFile, m_unitChunkBlockCount * m_thingBlockSize * cacheIndex->_BlockOffset, SEEK_SET);
				fseek(m_thingFile, m_thingBlockSize * cacheNumber, SEEK_CUR);
				fwrite(&newBlockFormat, m_thingBlockSize, 1, m_thingFile);
				fseek(m_thingFile, 0, SEEK_SET);
			}
		}
		else
		{
			//û�и�chunk ��Ҫ�½�
			IEThingChunkIndex newChunkIndex;
			newChunkIndex._X = chunkLocation.m_x;
			newChunkIndex._Y = chunkLocation.m_y;
			newChunkIndex._BlockOffset = m_thingIndexCount++;
			newChunkIndex._Next = NULL;

			fseek(m_thingIndexFile, 0, SEEK_END);
			fwrite(&newChunkIndex, sizeof(IEThingChunkIndex), 1, m_thingIndexFile);
			fseek(m_thingIndexFile, 0, SEEK_SET);

			//���ȿ���һ���µ�chunk ȫ��ֵΪ��
			fseek(m_thingFile, 0, SEEK_END);
			unsigned char * zero = new unsigned char[m_thingBlockSize];
			for (int index = 0; index < m_thingBlockSize; index++)
			{
				zero[index] = 0;
			}
			for (int index = 0; index < m_unitChunkBlockCount; index++)
			{
				fwrite(zero, 1, m_thingBlockSize, m_thingFile);
			}
			delete[]zero;
			fseek(m_thingFile, 0, SEEK_SET);

			//�ӵ�һblock��λ��д��block
			fseek(m_thingFile, -m_thingBlockSize * m_unitChunkBlockCount, SEEK_CUR);
			fwrite(&newBlockFormat, sizeof(IEThingBlockFormat), 1, m_thingFile);
			fseek(m_thingFile, 0, SEEK_SET);

			newChunkIndex._Next = NULL;
			RESOURCE[str] = (IEObject *)(&newChunkIndex);
		}
	}

	fseek(m_thingIndexFile, 0, SEEK_SET);
	fwrite(&m_thingOrder, sizeof(int), 1, m_thingIndexFile);
	fwrite(&m_thingIndexCount, sizeof(int), 1, m_thingIndexFile);
	fseek(m_thingIndexFile, 0, SEEK_SET);
}

void IEMap::LoadThingChunkIndex()
{
	//���ȶ������е���������
	m_thingIndexFile = fopen((m_sceneThingName + "_index").GetString(), "rb+");

	fread(&m_thingOrder, sizeof(unsigned int), 1, m_thingIndexFile);
	fread(&m_thingIndexCount, sizeof(unsigned int), 1, m_thingIndexFile);

	//��ֹ����Ϊ��
	if (m_thingIndexCount == 0)
	{
		return;
	}
	else
	{
		m_thingChunksIndex = new IEThingChunkIndex[m_thingIndexCount];
		fread(m_thingChunksIndex, sizeof(IEThingChunkIndex), m_thingIndexCount, m_thingIndexFile);

		char str[16];

		for (unsigned int index = 0; index < m_thingIndexCount; index++)
		{
			if (m_thingChunksIndex[index]._Next == 0)
			{
				sprintf(str, "%d_%d", m_thingChunksIndex[index]._X, m_thingChunksIndex[index]._Y);
				RESOURCE[str] = (IEObject *)(&m_thingChunksIndex[index]);
			}
			else
			{
				m_thingChunksIndex[unsigned int(m_thingChunksIndex[index]._Next)]._Next = &(m_thingChunksIndex[index]);
			}
		}
	}
}

void IEMap::LoadThingChunk(int blockX, int blockY)
{
	if (!m_curThing)
	{
		return;
	}

	IEThingAlter * thingAlterInfos = (IEThingAlter *)malloc(0);

	int existAdorningBlockIndex = -1;
	for (unsigned int adorningIndex = 0; adorningIndex < m_thingIndexCount; adorningIndex++)
	{
		if (m_thingChunksIndex[adorningIndex]._X == blockX && m_thingChunksIndex[adorningIndex]._Y == blockY)
		{
			existAdorningBlockIndex = adorningIndex;
			break;
		}
	}
	
	if (existAdorningBlockIndex >= 0)
	{
		char str[16];
		sprintf(str, "%d_%d", blockX, blockY);
		IEThingChunkIndex * thingChunkIndex = (IEThingChunkIndex *)(RESOURCE[str]);

		while (thingChunkIndex)
		{
			int offset = thingChunkIndex->_BlockOffset;

			fseek(m_thingFile, offset * m_unitChunkBlockCount * m_thingBlockSize, SEEK_SET);
			fread(m_thingBlocksList, sizeof(IEThingBlockFormat), m_unitChunkBlockCount, m_thingFile);
			thingChunkIndex = thingChunkIndex->_Next;

			for (int index = 0; index < m_unitChunkBlockCount; index++)
			{
				IEThingBlockFormat &data = m_thingBlocksList[index];
				
				continue;

				m_curThing->SetReadyThing(data._ThingID);
				m_curThing->AddChild(data._X, data._Y, data._TinyX, data._TinyY);
			}
		}
	}
}

IE_END