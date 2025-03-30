#pragma once

#include "StarUnit.h"
#include "Texture.h"

class Player1_Building :
    public StarUnit
{
    Player1_Building(wstring _wString, UNIT_TYPE m_UNITTYPE, float _duration = 8.f);
    ~Player1_Building();

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

    bool                m_ClickSoundable;

    // 향후, 오른쪽 클릭 등의 기능은 상속받을 클래스에서 구현하자
    bool                m_IsMouseover;
    bool                m_WasMouseover;
    bool                m_IsLeftButtonClick;
    bool                m_WasLeftButtonClick;


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

    virtual void MouseoverCheck() override;
    virtual void MouseClickCheck() override;

    // 포인터함수를 통한 기능 설정
    // 트리거용 포인터 함수
    virtual void SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction);

    // 사운드 재생용 포인터 함수
    virtual void SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction);
};