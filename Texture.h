#pragma once
#include "Asset.h"

// GDI+�� ���� ���� ��ó��
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
    wstring             m_Key;          // ������ ������ �̸�(���¸Ŵ������� �ش� ������ ã�ƿö� ���)
    wstring             m_RelativePath; // ������ ���
    const ASSET_TYPE    m_TYPE;
    */

private:
    HBITMAP     m_HANDLEBITMAP;        // ��Ʈ�� �ڵ�
    HDC         m_DC;                  // ��Ʈ���� �������� �����ϴ� DC
    BITMAP      m_BITMAPINFORMATION;   // ��Ʈ�� ����

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