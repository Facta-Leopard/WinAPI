#pragma once
#include "Component.h"

class MapTile :
    public Component
{
private:
    int             m_Col;              // 타일 열 개수
    int             m_Row;              // 타일 행 개수    

    Texture*        m_ATLAS;
    int             m_ATLASTileCol;     // 아틀라스 텍스쳐 안에 있는 타일 열 개수
    int             m_ATLASTileRow;     // 아틀라스 텍스쳐 안에 있는 타일 행 개수
    FloatPoint      m_ATLASResolution;  // 아틀라스 해상도

    // 각 타일마다 자신이 원하는 이미지를 고를 수 있어야함
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