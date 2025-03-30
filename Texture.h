#pragma once
#include "Asset.h"

// GDI+를 쓰기 위한 전처리
// GDI PLUS
#include <objidl.h>
#include <gdiplus.h>
#include <gdiplusinit.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

class Texture :
    public Asset
{
    friend class AssetMGR;

public:
    Texture();
    ~Texture();

    // Foundation Member

/*
private:
static UINT g_NextID;

private:
    wstring		m_Name;
    const UINT	m_ID;
    */

    // Asset Member

    /*
private:
    wstring             m_Key;          // 에셋의 고유한 이름(에셋매니저에서 해당 에셋을 찾아올때 사용)
    wstring             m_RelativePath; // 에셋의 경로
    const ASSET_TYPE    m_TYPE;
    */

private:
    HBITMAP     m_HANDLEBITMAP;        // 비트맵 핸들
    HDC         m_DC;                  // 비트맵을 목적지로 지정하는 DC
    BITMAP      m_BITMAPINFORMATION;   // 비트맵 정보

    Image*      m_IMAGE;

public:
    HDC GetDC()
    {
        return m_DC;
    }
    
    UINT GetWidth()
    {
        return m_BITMAPINFORMATION.bmWidth;
    }
    
    UINT GetHeight()
    {
        return m_BITMAPINFORMATION.bmHeight;
    }

private:
    virtual int Load(const wstring& _FilePath) override;
    void Create(UINT _Width, UINT _Height);


};