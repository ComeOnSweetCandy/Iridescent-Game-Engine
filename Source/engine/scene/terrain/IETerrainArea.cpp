#define __IE_DLL_EXPORTS__
#include "IETerrainArea.h"

#include "../../../control/IEmouse.h"

IE_BEGIN

IETerrainArea::IETerrainArea()
{
	m_sceneType = __ie_scene_terrain__;
	m_map = NULL;
	m_alter = NULL;
	m_readyTerrainID = 0;
	m_readyTerrainMode = __terrain_none_mode__;
}

IETerrainArea::~IETerrainArea()
{

}

void IETerrainArea::Initialization(IEMap * map, int visibleRadius, int sideLength)
{
	IEArea::Initialization(map, visibleRadius, sideLength);

	m_terrainsInfo = IETerrainList::Share()->GetEntrys();
}

IETerrainArea * IETerrainArea::Create(IEMap * map, int visibleRadius, int sideLength)
{
	IETerrainArea * terrain = new IETerrainArea();
	terrain->Initialization(map, visibleRadius, sideLength);
	return terrain;
}

void IETerrainArea::RandomTerrain()
{
	//�������

}

void IETerrainArea::AddChild(int blockLocationX, int blockLocationY)
{
	if (IETerrain * pastTerrain = (IETerrain *)(GetBlock(blockLocationX, blockLocationY)))
	{
		//����ɵ���Ϣ
		m_alter = new IETerrainAlter();
		m_alters->Push(m_alter);

		//�ȼ������µ���Ϣ
		m_alter->_X = blockLocationX;
		m_alter->_Y = blockLocationY;
		int cacheX, cacheY;
		LocationTranslate(blockLocationX, blockLocationY, m_alter->_ChunkX, m_alter->_ChunkY, cacheX, cacheY);

		//�����֮ǰ����Ϣ
		m_alter->_PastTerrainInfoSerialization = pastTerrain->Serialize();

		switch (m_readyTerrainMode)
		{
		case __terrain_none_mode__:
			ChangeNone(blockLocationX, blockLocationY);
			break;
		case __terrain_body_mode__:
			ChangeBody(blockLocationX, blockLocationY);
			break;
		case __terrain_bevel_mode__:
			ChangeBevel(blockLocationX, blockLocationY);
			break;
		case __terrain_piece_mode__:
			ChangePiece(blockLocationX, blockLocationY);
			break;
		default:
			break;
		}

		//�����µ���Ϣ
		m_alter->_CurtTerrainInfoSerialization = pastTerrain->Serialize();

		//��ǰ������1
		m_curOrder++;
		m_alter->_AlterOrder = m_alterOrder++;
	}
}

void IETerrainArea::LoadChilds(IETerrainSerialization * blocksInfo, int chunkLocationX, int chunkLocationY)
{
	IETerrainChunk * chunk = (IETerrainChunk *)GetChunk(chunkLocationX, chunkLocationY);
	chunk->ResetCache();

	if (blocksInfo)
	{
		for (int x = 0; x < m_chunkLength; x++)
		{
			for (int y = 0; y < m_chunkLength; y++)
			{
				IETerrain * terrain = (IETerrain *)chunk->GetBlock(x, y);
				terrain->determinant(&(blocksInfo[x * m_chunkLength + y]));
			}
		}
	}

	//���һ���޸��б� �Ƿ��жԵ�ǰchunk���޸�
	//�ó�chunk�ı߽� �������Կ���ɸѡ�����ڸ�chunk�ڵĲ���
	unsigned int count = m_alters->Count();
	IETerrainAlter ** alters = (IETerrainAlter **)(m_alters->GetContainer());
	for (unsigned int index = 0; index < count; index++)
	{
		if (alters[index]->_ChunkX == chunkLocationX && alters[index]->_ChunkY == chunkLocationY)
		{
			IETerrain * terrain = (IETerrain *)GetBlock(alters[index]->_X, alters[index]->_Y);
			terrain->determinant(alters[index]->_CurtTerrainInfoSerialization);
			terrain->ChangeBorderDisplay();
		}
	}
}

IEChunk * IETerrainArea::CreateChunk()
{
	return IETerrainChunk::Create(m_chunkLength);
}

void IETerrainArea::LoadChunk(int blockX, int blockY)
{
	m_map->LoadTerrainChunk(blockX, blockY);
}

void IETerrainArea::ChangeNone(int blockLocationX, int blockLocationY)
{
	IETerrain * grid = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
	if (grid != NULL)
	{
		grid->Reload(0, 0);
		grid->ChangeBodyIndex(0);
	}
}

void IETerrainArea::ChangeBody(int blockLocationX, int blockLocationY)
{
	IETerrain * grid = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
	if (grid != NULL)
	{
		grid->SetBlockPostion(blockLocationX, blockLocationY);
		grid->Reload(m_readyTerrainID, m_curOrder);
		grid->ChangeBodyIndex();

		ReserializatioRound(blockLocationX, blockLocationY - 1);
		ReserializatioRound(blockLocationX + 1, blockLocationY);
		ReserializatioRound(blockLocationX, blockLocationY + 1);
		ReserializatioRound(blockLocationX - 1, blockLocationY);
	}
}

void IETerrainArea::ChangeBevel(int blockLocationX, int blockLocationY)
{

}

void IETerrainArea::ChangePiece(int blockLocationX, int blockLocationY)
{
	IETerrain * grid = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
	if (grid != NULL)
	{
		grid->ChangePieceIndex(m_readyTerrainID);
	}
}

void IETerrainArea::ReserializatioRound(int blockLocationX, int blockLocationY)
{
	//unsigned int count = m_alters->Count();
	//IETerrainAlter ** alters = (IETerrainAlter **)(m_alters->GetContainer());
	//for (unsigned int index = 0; index < count; index++)
	//{
	//	if (alters[index]->_X == blockLocationX && alters[index]->_Y == blockLocationY)
	//	{
	//		delete alters[index]->_CurtTerrainInfoSerialization;

	//		IETerrain * terrain = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
	//		alters[index]->_CurtTerrainInfoSerialization = terrain->Serialize();
	//		
	//		return;
	//	}
	//}

	//�������û���ҵ�����ô����Ҫ�����µĽ�ȥ
	if (IETerrain * terrain = (IETerrain *)GetBlock(blockLocationX, blockLocationY))
	{
		if (terrain->GetTerrainID() != 0)
		{
			IETerrainAlter * alter = new IETerrainAlter();
			m_alters->Push(alter);

			//�ȼ������µ���Ϣ
			alter->_X = blockLocationX;
			alter->_Y = blockLocationY;
			int cacheX, cacheY;
			LocationTranslate(blockLocationX, blockLocationY, alter->_ChunkX, alter->_ChunkY, cacheX, cacheY);

			//�����֮ǰ����Ϣ ����NULL����˼Ϊ ֮ǰ����ϢΪ�����޸� ������
			alter->_PastTerrainInfoSerialization = NULL;

			//�����µ���Ϣ
			alter->_CurtTerrainInfoSerialization = terrain->Serialize();

			//�����޸ļ���
			alter->_AlterOrder = m_alterOrder;
		}
	}
}

void IETerrainArea::RollbackAllAlters()
{
	while (IETerrainAlter * alter = (IETerrainAlter *)(m_alters->PopTop()))
	{

	}
}

void IETerrainArea::RollbackAlter()
{
	while (IETerrainAlter * alter = (IETerrainAlter *)(m_alters->PopTop()))
	{
		if (alter->_PastTerrainInfoSerialization)
		{
			//��ȡ�����޸ĵ�terrain
			IETerrain * pastTerrain = (IETerrain *)(GetBlock(alter->_X, alter->_Y));

			//���֮ǰ��pastΪ�� ˵�����ܵ�border�Ķ����ܵ�Ӱ�����Χ��terrain �������
			pastTerrain->determinant(alter->_PastTerrainInfoSerialization);
			pastTerrain->ChangeBorderDisplay();

			return;
		}
	}
}

void IETerrainArea::SetReadyTerrain(unsigned int terrainID, IETerrainMode terrainMode)
{
	m_readyTerrainID = terrainID;
	m_readyTerrainMode = terrainMode;

	if (m_readyTerrainID != 0 && m_readyTerrainMode != __terrain_none_mode__)
	{
		IEPackerTexture * texture = IEPackerTexture::Create(m_terrainsInfo[m_readyTerrainID]._Xml->FindChild("texture"));
		m_suspension->ChangeTexture(texture);
		m_suspension->ChangeGroup("body");
	}
}

void IETerrainArea::MouseMove(float x, float y)
{
	//��������������ָ���λ�� chunk block���ᱻ��¼����
	if (m_readyTerrainID != 0 && m_readyTerrainMode != __terrain_none_mode__)
	{
		//˵���Ѿ�ѡ����ReadyID
		m_suspension->SetTranslate(IEMouse::Share()->_MouseLocationX, IEMouse::Share()->_MouseLocationY);
		m_suspension->Visit();
	}
	else
	{
		//˵��û��ѡ��ReadyID ��ô���Ե�ǰ����Ϊ��ʾ��Ԫ��
		if (IETerrain * terrain = (IETerrain *)GetBlock(IEMouse::Share()->_MouseLocationX, IEMouse::Share()->_MouseLocationY))
		{
			if (terrain->GetTerrainID() != 0)
			{
				IEPackerTexture * texture = terrain->GetTexture();
				m_suspension->ChangeTexture(texture);
				m_suspension->ChangeGroup("body");
				m_suspension->SetTranslate(x, y);
			}
		}
		else
		{
			m_suspension->RemoveTexture();
		}
	}
}

void IETerrainArea::MouseCancel()
{
	m_readyTerrainID = 0;
	m_readyTerrainMode = __terrain_none_mode__;
}

void IETerrainArea::MouseClick()
{
	//���Ȳ鿴��ǰ��ģʽ
	if (m_readyTerrainID == 0)
	{
		//ѡ��ģʽ �Ե�ǰλ�ý���ѡ��
		m_choosen = GetBlock(IEMouse::Share()->_MouseLocationX, IEMouse::Share()->_MouseLocationY);

		//����һƬ������ʾchoosen�����е���Ϣ �༭���»���ʾ
	}
	else
	{
		AddChild(IEMouse::Share()->_MouseLocationX, IEMouse::Share()->_MouseLocationY);
	}
}

void IETerrainArea::MouseBrush()
{
	if (m_readyTerrainID != 0)
	{

		AddChild(IEMouse::Share()->_MouseLocationX, IEMouse::Share()->_MouseLocationY);
	}
}

IE_END