#pragma once
#include "Component.h"

class MapTile :
    public Component
{
private:
    int             m_Col;              // Ÿ�� �� ����
    int             m_Row;              // Ÿ�� �� ����    

    Texture*        m_ATLAS;
    int             m_ATLASTileCol;     // ��Ʋ�� �ؽ��� �ȿ� �ִ� Ÿ�� �� ����
    int             m_ATLASTileRow;     // ��Ʋ�� �ؽ��� �ȿ� �ִ� Ÿ�� �� ����
    FloatPoint      m_ATLASResolution;  // ��Ʋ�� �ػ�

    // �� Ÿ�ϸ��� �ڽ��� ���ϴ� �̹����� �� �� �־����
    vector<Tile>   m_vecTileInfo;

public:
    void SetRowCol(int Row, int Col);
    void SetAtlasTexture(Texture* _Atlas);
    Tile* GeTileInfo(FloatPoint _MousePos);

public:
    bool SaveMapTile(wstring _FullPath);
    bool LoadMapTile(wstring _FullPath);


public:
    virtual void FinalTick() override;
    void Render();

public:
    MapTile();
    ~MapTile();
};