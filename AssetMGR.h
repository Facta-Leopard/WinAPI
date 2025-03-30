#pragma once
#include "PreCompile.h"
#include "Sprite.h"
#include "Animation.h"
#include "Sound.h"

class AssetMGR
{
	SINGLE(AssetMGR);

private:
	map<wstring, Texture*>		m_MAP_TEXTURE;
	map<wstring, Sprite*>		m_MAP_SPRITE;
	map<wstring, Animation*>	m_MAP_ANIMATION;
	map<wstring, Sound*>		m_MAP_SOUND;

public:
	void Init();

	Texture* FindTexture(const wstring& _Key);
	Texture* LoadTexture(const wstring& _Key, const wstring& _RelativePath);
	Texture* CreateTexture(const wstring& _Key, UINT _Width, UINT _Height);

	Sprite* FindSprite(const wstring& _Key);
	Sprite* LoadSprite(const wstring& _Key, const wstring& _RelativePath);
	void AddSprite(const wstring& _Key, Sprite* _Sprite);

	Animation* FindANIMATION(const wstring& _Key);
	Animation* LoadANIMATION(const wstring& _Key, const wstring& _RelativePath);
	void AddANIMATION(const wstring& _Key, Animation* _ANIMATION);

	Sound* FindSound(const wstring& _Key);
	Sound* LoadSound(const wstring& _Key, const wstring& _RelativePath);




};