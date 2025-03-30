#pragma once
#include "Component.h"

class Object;

class MovingMotion :
    public Component
{
    friend class Object;

public:
    MovingMotion();

    // ���� ������.. �ƿ�.. ���� �̰ű��� �ؾߵǳ�..
    MovingMotion(const MovingMotion& _OTHER);

    // ���� ������.. �� ���� ������ ���� �����..
    MovingMotion& operator=(const MovingMotion& _OTHER);

    MovingMotion(wstring _Name
               , UNIT_TYPE _UNIT = UNIT_TYPE::MARINE
               , MOVINGMOTION_TYPE _MOVINGMOTION = MOVINGMOTION_TYPE::IDLE_DOWN
               , FloatPoint _SIZE = { 64.f , 64.f });
    ~MovingMotion();

    //Foundation Member
    /*
    private:
        static UINT g_NextID;

    private:
        wstring		m_Name;
        const UINT	m_ID;
        */

    // Component Member
    /*
private:
    Object* m_OWNER;
    const COMPONENT_TYPE    m_TYPE;
    */

private:
    wstring             m_Name;
    float               m_Time;
    float               m_Duration;
    float               m_FPS_Time;
    int                 m_Index;
    int                 m_MaxFrame;

    Texture* m_TEXTURE;
    
    UNIT_TYPE   m_UNITTYPE;
    MOVINGMOTION_TYPE   m_MOVINGMOTIONTYPE;

    FloatPoint          m_SCALE;

public:

    MOVINGMOTION_TYPE GetMovingMotionType()
    {
        return m_MOVINGMOTIONTYPE;
    }

    FloatPoint GetScale()
    {
        return m_SCALE;
    }

    void SetScale(FloatPoint _Scale)
    {
        m_SCALE = _Scale;
    }

    Texture* GetTexture()
    {
        return m_TEXTURE;
    }


    float GetDuration()
    {
        return m_Duration;
    }

    float GetFPSTime()
    {
        return m_FPS_Time;
    }
    int GetIndex()
    {
        return m_Index;
    }
    int GetMaxFrame()
    {
        return m_MaxFrame;
    }

public:
    virtual void Init();
    virtual void FinalTick() override;

    void Render();
};