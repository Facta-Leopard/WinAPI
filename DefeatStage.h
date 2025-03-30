#pragma once
#include "Stage.h"

class DefeatStage :
    public Stage
{
private:
    float   m_Return;

private:
    Texture* m_TEXTURE;

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void DeInit() override;

public:
    DefeatStage();
    ~DefeatStage();
};