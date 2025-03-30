#pragma once
#include "Object.h"
#include "FSM.h"

class Player2 :
    public Object
{
    // Foundation Member

/* private:
    static UINT g_NextID;

private:
    wstring		m_Name;
    const UINT	m_ID;
*/

    // Object Member

/* private:
    FloatPoint          m_POSITION;
    FloatPoint          m_PREVIOUSPOSTION;
    FloatPoint          m_SCALE;
    vector<Component*>   m_COMPONENT;
    LAYER_TYPE           m_LAYERTYPE;
    bool                 m_Dead;         // 삭제 예정
*/

private:
    UnitInfomation    m_INFORMATION;

    int         m_Dir;
    float       m_Speed;
    FloatPoint  m_InitPos;
    float       m_Dist;

    Texture* m_Tex;
    Collider* m_COLLIDER;
    FSM* m_FSM;

public:
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void SetDistance(float _Dist) { m_Dist = _Dist; }

    const UnitInfomation& GeUnitInfomation() { return m_INFORMATION; }

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER) override;

public:
    Player2();
    ~Player2();
};