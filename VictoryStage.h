#pragma once
#include "Stage.h"

class VictoryStage :
    public Stage
{
private:
    Texture* m_TEXTURE;

    float   m_Return;

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void DeInit() override;

public:
    void SaveMapTile();
    void LoadMapTile();

public:
    VictoryStage();
    ~VictoryStage();
};