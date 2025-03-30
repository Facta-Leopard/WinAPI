#pragma once
#include "StarUnit.h"

#include "MenuUI.h"

class MouseoverMenuUI
	: public MenuUI
{
public:
    MouseoverMenuUI(wstring _wString, float _duration = 3.f);
    ~MouseoverMenuUI();

    // Foundation Member

/* private:
    static UINT g_NextID;

private:
    wstring		m_Name;
    const UINT	m_ID;
*/

// Object Member

/* private:
    FloatPoint           m_POSITION;
    FloatPoint           m_PREVIOUSPOSTION;
    FloatPoint           m_SCALE;
    vector<Component*>   m_COMPONENT;
    LAYER_TYPE           m_LAYERTYPE;
    bool                 m_Dead;         // 삭제 예정
*/

    // Menu Member
//protected:
//    float               m_Time;
//    float               m_Duration;
//    float               m_FPS_Time;
//    float               m_Index;
//    int                 m_MaxFrame;
//
//    Texture*            m_TEXTURE;

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render() override;

    void MouseoverCheck() override;
    void MouseClickCheck() override;
};