#include "PreCompile.h"
#include "AssetMGR.h"

AssetMGR::AssetMGR()
{

}

AssetMGR::~AssetMGR()
{
    Delete_Map(m_MAP_TEXTURE);
    Delete_Map(m_MAP_SPRITE);
    Delete_Map(m_MAP_ANIMATION);
    Delete_Map(m_MAP_SOUND);
}

void AssetMGR::Init()
{

}

Texture* AssetMGR::FindTexture(const wstring& _Key)
{
    map<wstring, Texture*>::iterator iter = m_MAP_TEXTURE.find(_Key);

    if (iter == m_MAP_TEXTURE.end())
    {
        return nullptr;
    }

    return iter->second;
}

Texture* AssetMGR::LoadTexture(const wstring& _Key, const wstring& _RelativePath)
{
    Asset* pTex = FindTexture(_Key);
    
    // 이미 로딩한 적이 있는 Texture 라면
    if (nullptr != pTex)
    {
        // 로딩한 텍스쳐를 반환
        return (Texture*)pTex;
    }

    pTex = new Texture;
    pTex->Load(_RelativePath);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pTex->SetKey(_Key);
    pTex->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
    m_MAP_TEXTURE.insert(make_pair(_Key, (Texture*)pTex));

    return (Texture*)pTex;
}

Texture* AssetMGR::CreateTexture(const wstring& _Key, UINT _Width, UINT _Height)
{
    Texture* pTex = FindTexture(_Key);
    assert(!pTex);

    pTex = new Texture;
    pTex->Create(_Width, _Height);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값을 세팅해준다.
    pTex->SetKey(_Key);

    // 컨테이너에 텍스쳐 등록
    m_MAP_TEXTURE.insert(make_pair(_Key, (Texture*)pTex));

    return pTex;
}

Sprite* AssetMGR::FindSprite(const wstring& _Key)
{
    map<wstring, Sprite*>::iterator iter = m_MAP_SPRITE.find(_Key);

    if (iter == m_MAP_SPRITE.end())
    {
        return nullptr;
    }

    return iter->second;
}

Sprite* AssetMGR::LoadSprite(const wstring& _Key, const wstring& _RelativePath)
{
    Asset* pSprite = FindSprite(_Key);

    // 이미 로딩한 적이 있는 Texture 라면
    if (nullptr != pSprite)
    {
        // 로딩한 텍스쳐를 반환
        return (Sprite*)pSprite;
    }

    pSprite = new Sprite;
    pSprite->Load(_RelativePath);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pSprite->SetKey(_Key);
    pSprite->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
    m_MAP_SPRITE.insert(make_pair(_Key, (Sprite*)pSprite));

    return (Sprite*)pSprite;
}

void AssetMGR::AddSprite(const wstring& _Key, Sprite* _Sprite)
{
    assert(!FindSprite(_Key));

    _Sprite->SetKey(_Key);
    m_MAP_SPRITE.insert(make_pair(_Key, _Sprite));
}



Animation* AssetMGR::FindANIMATION(const wstring& _Key)
{
    map<wstring, Animation*>::iterator iter = m_MAP_ANIMATION.find(_Key);

    if (iter == m_MAP_ANIMATION.end())
    {
        return nullptr;
    }

    return iter->second;
}

Animation* AssetMGR::LoadANIMATION(const wstring& _Key, const wstring& _RelativePath)
{
    Asset* pANIMATION = FindANIMATION(_Key);

    // 이미 로딩한 적이 있는 Texture 라면
    if (nullptr != pANIMATION)
    {
        // 로딩한 텍스쳐를 반환
        return (Animation*)pANIMATION;
    }

    pANIMATION = new Animation;
    pANIMATION->Load(_RelativePath);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pANIMATION->SetKey(_Key);
    pANIMATION->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
    m_MAP_ANIMATION.insert(make_pair(_Key, (Animation*)pANIMATION));

    return (Animation*)pANIMATION;
}

void AssetMGR::AddANIMATION(const wstring& _Key, Animation* _ANIMATION)
{
    assert(!FindANIMATION(_Key));

    _ANIMATION->SetKey(_Key);
    m_MAP_ANIMATION.insert(make_pair(_Key, _ANIMATION));
}


Sound* AssetMGR::FindSound(const wstring& _Key)
{
    map<wstring, Sound*>::iterator iter = m_MAP_SOUND.find(_Key);

    if (iter == m_MAP_SOUND.end())
    {
        return nullptr;
    }

    return iter->second;
}

Sound* AssetMGR::LoadSound(const wstring& _Key, const wstring& _RelativePath)
{
    Asset* pSound = FindSound(_Key);

    // 이미 로딩한 적이 있는 Sound Asset이라면
    if (nullptr != pSound)
    {
        // 로딩한 Sound Asset을 반환
        return (Sound*)pSound;
    }

    pSound = new Sound;
    pSound->Load(_RelativePath);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pSound->SetKey(_Key);
    pSound->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
    m_MAP_SOUND.insert(make_pair(_Key, (Sound*)pSound));

    return (Sound*)pSound;
}