#pragma once
#include "Foundation.h"

class Asset :
    public Foundation
{
    // Foundation Member

    /*
    private:
	static UINT g_NextID;

private:
	wstring		m_Name;
	const UINT	m_ID;
    */

private:
    wstring             m_Key;          // ������ ������ �̸�(���¸Ŵ������� �ش� ������ ã�ƿö� ���)
    wstring             m_RelativePath; // ������ ���
    const ASSET_TYPE    m_TYPE;

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }
    ASSET_TYPE GetAssetType() { return m_TYPE; }

protected:
    void CheckExt(const wstring& _Ext, wstring& _strFilePath);
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    void SetRelativePath(const wstring& _RelativePath) { m_RelativePath = _RelativePath; }

private:
    virtual int Save(const wstring& _FilePath) { return S_OK; }
    virtual int Load(const wstring& _FilePath) = 0;

public:
    Asset(ASSET_TYPE _Type);
    ~Asset();

    friend class AssetMGR;
};