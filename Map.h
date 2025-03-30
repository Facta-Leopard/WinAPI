#pragma once
#include "PreCompile.h"
#include "Object.h"

class Map :
	public Object
{
public:
	Map(wstring _wString);
	~Map();


    // Foundation Member
/* private:
    static UINT g_NextID;

private:
    wstring		m_Name;
    const UINT	m_ID; */

    // Object Member
//protected:
//    FloatPoint           m_POSITION;
//    FloatPoint           m_PREVIOUSPOSTION;
//    FloatPoint           m_SCALE;
//    vector<Component*>   m_COMPONENT;
//    LAYER_TYPE           m_LAYERTYPE;
//    bool                 m_Dead;         // 삭제 예정

private:

    Texture* m_TEXTURE;

    void Init() override;
    void Tick() override;
    virtual void Render() override;
};