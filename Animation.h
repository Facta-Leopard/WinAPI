#pragma once

#include "Asset.h"

class Animation :
    public Asset
{
private:
    vector<Sprite*>    m_Sprites;

public:
    void AddSprite(Sprite* _Sprite)
    {
        m_Sprites.push_back(_Sprite);
    }
    
    Sprite* GetSprite(int _Idx)
    {
        return m_Sprites[_Idx];
    }

    int GetMaxSpriteCount()
    {
        return m_Sprites.size();
    }

public:
    virtual int Save(const wstring& _RelativePath) override;
    virtual int Load(const wstring& _RelativePath) override;

public:
    Animation();
    ~Animation();
};