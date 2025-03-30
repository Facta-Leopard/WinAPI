#pragma once
#include "Component.h"

class Portrait :
	public Component
{
    friend class Object;
    friend class PortraitMGR;

public:
    Portrait();
    Portrait(wstring _Name
		, UNIT_TYPE _UNIT = UNIT_TYPE::MARINE
		, PORTRAIT_TYPE _PORTRAITTYPE = PORTRAIT_TYPE::PORTRAITE_IDLE
        , FloatPoint _SIZE = { 60, 56 });
	~Portrait();

    // 복사 생성자
    Portrait(const Portrait& _OTHER);

    // 대입 연산자
    Portrait& operator=(const Portrait& _OTHER);

private:
    wstring             m_Name;
    float               m_Time;
    float               m_Duration;
    float               m_FPS_Time;
    int                 m_Index;
    int                 m_MaxFrame;

    Texture*            m_TEXTURE;

    UNIT_TYPE           m_UNITTYPE;
    PORTRAIT_TYPE       m_PORTRAITTYPE;

    FloatPoint          m_SCALE;

public:
    virtual void Init();
    virtual void FinalTick() override;

    void Render();

    void SetDuration(float _Duration)
    {
        m_Duration = _Duration;
    }

};