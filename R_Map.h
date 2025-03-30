#pragma once
#include "Object.h"
#include "MapTile.h"

class R_Map :
    public Object
{
private:
    MapTile* m_MapTile;


public:
    MapTile* GeMapTile() { return m_MapTile; }
    virtual void Tick() override;
    virtual void Render() override;

public:
    R_Map();
    ~R_Map();
};