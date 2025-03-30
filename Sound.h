#pragma once

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

#include "Asset.h"

class Sound :
    public Asset
{
public:
    Sound();
    ~Sound();

    friend class AssetMGR;

private:
    LPDIRECTSOUNDBUFFER		m_pSoundBuffer;
    DSBUFFERDESC			m_tBuffInfo;
    int						m_iVolume;

public:
    virtual int Load(const wstring& _strFilePath);

private:
    bool LoadWaveSound(const wstring& _strPath);

public:
    // ���� ���
    void Play(bool _bLoop = false);

    // ����������� ���
    void PlayToBGM(bool _bLoop = false);

    // ����
    void Stop(bool _bReset = false);

    // ���� ���� (0 ~ 100)
    void SetVolume(float _fVolume);

    // ���� ��� ��ġ (0 ~ 100)
    void SetPosition(float _fPosition); // 0 ~ 100 

    int GetDecibel(float _fVolume);
};