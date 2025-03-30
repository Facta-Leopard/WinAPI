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
    bool                 m_Dead;         // 삭제 예정
*/

protected:
    float                   m_Time;

    float                   m_Duration;
    float                   m_FPS_Time;

    bool                    m_OnText;

    // 포인터함수를 통한 기능 구현 추구
    std::function<void(LAYER_TYPE)> m_Trigger_PointerFunction;

    // 포인터함수를 통한 기능 구현 추구(사운드)
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


    // 포인터함수를 통한 기능 설정
    // 테스트용
    virtual void SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction);

    // 
    virtual void SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction);
};