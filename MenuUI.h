#pragma once

#include "StarUnit.h"
#include "Texture.h"

#include <functional>

class MenuUI :
    public StarUnit
{
public:
    MenuUI(wstring _wString, float _duration = 5.f);
    ~MenuUI();

protected:
    bool                m_ClickSoundable;
    bool                m_MouseoverSoundable;

    // 향후, 오른쪽 클릭 등의 기능은 상속받을 클래스에서 구현하자
    bool                m_IsMouseover;
    bool                m_WasMouseover;
    bool                m_IsLeftButtonClick;
    bool                m_WasLeftButtonClick;

    Texture*            m_TEXTURE;

    float               m_Index;
    int                 m_MaxFrame;

    // StarUnit 클래스의 주요부분
    //Texture* m_TEXTURE;

    //// 포인터함수를 통한 기능 구현 추구
    //std::function<void(LAYER_TYPE)> m_Trigger_PointerFunction;

    //// 포인터함수를 통한 기능 구현 추구(사운드)
    //std::function<void(UNIT_TYPE)> m_Sound_PointerFunction;

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void PlaySound();

    virtual void MouseoverCheck() override;
    virtual void MouseClickCheck() override;


    virtual void SetOnText();
    virtual void SetOffText();


    // 포인터함수를 통한 기능 설정
    // 테스트용
    virtual void SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction);

    // 
    virtual void SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction);
};