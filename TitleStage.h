#pragma once
#include "Stage.h"

class TitleStage :
    public Stage
{
    // Foundation Member
/*
private:
static UINT g_NextID;

private:
    wstring		m_Name;
    const UINT	m_ID;
    */

    // Stage Member

    /*
private:
    vector<Object*>    m_VECTOROBJECTS[(UINT)LAYER_TYPE::EOL];
    vector<Collider*>  c_VECTORCOLLIDER[(UINT)LAYER_TYPE::EOL];
    */

private:
    Texture*    m_TEXTURE;
    float       m_Time;

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void DeInit() override;

public:
    void LoadAllObject();

public:
    TitleStage();
    ~TitleStage();
};