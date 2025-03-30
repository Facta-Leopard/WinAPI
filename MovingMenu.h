#pragma once

#include "StarUnit.h"
#include "Texture.h"
#include "MenuUI.h"

#include <functional>

class MovingMenuUI :
    public MenuUI
{
public:
    FloatPoint          m_TARGETPOINT;

public:
    MovingMenuUI(wstring _wString, FloatPoint _TARGETPOINT, float _duration = 5.f, float _velocity = 800.f);
    ~MovingMenuUI();

protected:
float           m_Velocity;

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void PlaySound() override;
};