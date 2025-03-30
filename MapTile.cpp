#include "PreCompile.h"

#include "Object.h"
#include "MapTile.h"

#include "CameraMGR.h"

MapTile::MapTile()
	: Component(COMPONENT_TYPE::MAPTILE)
	, m_Col(1)
	, m_Row(1)
	, m_ATLAS(nullptr)
	, m_ATLASTileCol(0)
	, m_ATLASTileRow(0)
{
}

MapTile::~MapTile()
{
}

void MapTile::FinalTick()
{
	FloatPoint OwnerPos = GetOwner()->GetCameraViewPosition();

	for (int row = 0; row < m_Row + 1; ++row)
	{
		DrawDebugLine(PEN_COLOR::GREEN
			, OwnerPos + FloatPoint(0, TILE_SIZE * row)
			, OwnerPos + FloatPoint(m_Col * TILE_SIZE, TILE_SIZE * row), 0.f);
	}

	for (int col = 0; col < m_Col + 1; ++col)
	{
		DrawDebugLine(PEN_COLOR::GREEN
			, OwnerPos + FloatPoint(TILE_SIZE * col, 0)
			, OwnerPos + FloatPoint(TILE_SIZE * col, m_Row * TILE_SIZE), 0.f);
	}

}

void MapTile::Render()
{
	if (nullptr == m_ATLAS)
		return;

	FloatPoint OwnerRenderPos = GetOwner()->GetCameraViewPosition();
	HDC dc = GameEngine::GetInstance()->GetMemoryDC();

	// ī�޶� ���� �ȿ� ������ ��, ���� ����ϱ�
	FloatPoint vCamLook = CameraMGR::GetInstance()->GetLookAt();
	FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();
	FloatPoint vCamLeftTop = vCamLook - (vResolution * 0.5);
	FloatPoint vCamRightBot = vCamLook + (vResolution * 0.5);

	FloatPoint vOwnerPos = GetOwner()->GetPosition();
	vCamLeftTop = vCamLeftTop - vOwnerPos;

	int LeftTopCol = (int)(vCamLeftTop.x / TILE_SIZE);
	int LeftTopRow = (int)(vCamLeftTop.y / TILE_SIZE);

	if (LeftTopCol < 0)
		LeftTopCol = 0;
	if (LeftTopRow < 0)
		LeftTopRow = 0;

	vCamRightBot = vCamRightBot - vOwnerPos;
	int RightBotCol = (int)((vCamRightBot.x / TILE_SIZE) + 1);
	int RightBotRow = (int)((vCamRightBot.y / TILE_SIZE) + 1);

	if (m_Col < RightBotCol)
		RightBotCol = m_Col;
	if (m_Row < RightBotRow)
		RightBotRow = m_Row;

	for (int Row = LeftTopRow; Row < RightBotRow; ++Row)
	{
		for (int Col = LeftTopCol; Col < RightBotCol; ++Col)
		{
			// �ݺ��� ȸ���� �´� ��Ŀ� ���ؼ� �̰� ���° Ÿ���������� 1���� �ε����� ��ȯ
			// �ش� Ÿ�������� �����Ѵ�.
			int TileIdx = m_Col * Row + Col;
			int ImageIndex = m_vecTileInfo[TileIdx].ImageIndex;

			// �ش� Ÿ���� ImageIndex �� -1 �� ���, Blank Tile
			if (ImageIndex == -1)
				continue;

			int ImgRow = ImageIndex / m_ATLASTileCol; //  1 ��
			int ImgCol = ImageIndex % m_ATLASTileCol; //   6 ��

			assert(!(ImageIndex < 0 || m_ATLASTileCol * m_ATLASTileRow <= ImageIndex));

			BitBlt(dc
				, (int)OwnerRenderPos.x + Col * TILE_SIZE
				, (int)OwnerRenderPos.y + Row * TILE_SIZE
				, TILE_SIZE, TILE_SIZE
				, m_ATLAS->GetDC()
				, ImgCol * TILE_SIZE, ImgRow * TILE_SIZE
				, SRCCOPY);
		}
	}
}

void MapTile::SetRowCol(int Row, int Col)
{
	m_Row = Row;
	m_Col = Col;

	if (m_vecTileInfo.size() < m_Row * m_Col)
		m_vecTileInfo.resize(m_Row * m_Col);
}

void MapTile::SetAtlasTexture(Texture* _Atlas)
{
	m_ATLAS = _Atlas;

	if (nullptr == m_ATLAS)
		return;

	// ��Ʋ�� �ؽ��� ���� ��������
	m_ATLASResolution = FloatPoint((float)m_ATLAS->GetWidth(), (float)m_ATLAS->GetHeight());
	m_ATLASTileCol = (int)(m_ATLASResolution.x / TILE_SIZE);
	m_ATLASTileRow = (int)(m_ATLASResolution.y / TILE_SIZE);
}

Tile* MapTile::GeTileInfo(FloatPoint _MousePos)
{
	if (KeyMGR::GetInstance()->IsMouseOffScreen())
		return nullptr;

	_MousePos = CameraMGR::GetInstance()->GetInGameView(_MousePos);
	FloatPoint vOffset = _MousePos - GetOwner()->GetPosition();

	// ���콺 ��ġ�� Ÿ�ϸ��� ������ Ÿ�� �߿��� ���� � ��ġ���� �˾Ƴ���.
	int Col = (int)vOffset.x / TILE_SIZE;
	int Row = (int)vOffset.y / TILE_SIZE;

	if (Col < 0 || Row < 0 || m_Col <= Col || m_Row <= Row)
		return nullptr;

	int idx = Row * m_Col + Col;
	return &m_vecTileInfo[idx];
}

bool MapTile::SaveMapTile(wstring _FullPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FullPath.c_str(), L"wb");
	assert(pFile);

	// Ÿ�� ��, �� ���� ����
	fwrite(&m_Col, sizeof(int), 1, pFile);
	fwrite(&m_Row, sizeof(int), 1, pFile);

	// �����ϴ� ��Ʋ�� �ؽ��� ����
	SaveAssetRef(m_ATLAS, pFile);

	// ������ Ÿ���� ����ϴ� �̹��� �ε��� ����
	int TileCount = m_Col * m_Row;
	for (int i = 0; i < TileCount; ++i)
	{
		fwrite(&m_vecTileInfo[i], sizeof(Tile), 1, pFile);
	}

	fclose(pFile);

	return true;
}

bool MapTile::LoadMapTile(wstring _FullPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FullPath.c_str(), L"rb");
	assert(pFile);

	// Ÿ�� ��, �� ���� ����
	fread(&m_Col, sizeof(int), 1, pFile);
	fread(&m_Row, sizeof(int), 1, pFile);
	SetRowCol(m_Row, m_Col);

	// �����ϴ� ��Ʋ�� �ؽ��� ����
	m_ATLAS = (Texture*)LoadAssetRef(pFile);
	SetAtlasTexture(m_ATLAS);

	// ������ Ÿ���� ����ϴ� �̹��� �ε��� ����
	int TileCount = m_Col * m_Row;
	for (int i = 0; i < TileCount; ++i)
	{
		fread(&m_vecTileInfo[i], sizeof(Tile), 1, pFile);
	}

	fclose(pFile);

	return true;
}