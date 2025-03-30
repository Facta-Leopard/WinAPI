#pragma once

#include "Object.h"
#include "Texture.h"

#include <functional>

class StarUnit :
    public Object
{
public:
    StarUnit(wstring _wString, float _duration = 8.f);
    virtual ~StarUnit();

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
    bool                 m_Dead;         // ���� ����
*/

protected:
    float                   m_Time;

    float                   m_Duration;
    float                   m_FPS_Time;

    bool                    m_OnText;

    // �������Լ��� ���� ��� ���� �߱�
    std::function<void(LAYER_TYPE)> m_Trigger_PointerFunction;

    // �������Լ��� ���� ��� ���� �߱�(����)
    std::function<void(UNIT_TYPE)> m_Sound_PointerFunction;

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render() override;

    virtual void PlaySound() = 0;

    virtual void MouseoverCheck();
    virtual void MouseClickCheck();
    
    void SetOnText();
    void SetOffText();


    // �������Լ��� ���� ��� ����
    // �׽�Ʈ��
    virtual void SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction);

    // 
    virtual void SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction);
};