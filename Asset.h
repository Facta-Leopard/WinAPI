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
    wstring             m_Key;          // 에셋의 고유한 이름(에셋매니저에서 해당 에셋을 찾아올때 사용)
    wstring             m_RelativePath; // 에셋의 경로
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