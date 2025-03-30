#include "PreCompile.h"
#include "Map.h"

Map::Map(wstring _wString)
	: Object()
	, m_TEXTURE(nullptr)
{
	SetName(_wString);
	m_TEXTURE = AssetMGR::GetInstance()->LoadTexture(_wString
		, L"Texture\\" + _wString + L"\\" + _wString + L".BMP");
}

Map::~Map()
{
}

void Map::Init()
{

}

void Map::Tick()
{
    GetCameraViewPosition();
}

void Map::Render()
{
    FloatPoint tPOS = GetCameraViewPosition();

    HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
    BitBlt(tDC
        , 0
        , 0
        , RESOLUTION.x
        , RESOLUTION.y
        , m_TEXTURE->GetDC()
        , tPOS.x
        , tPOS.y
        , SRCCOPY);
}