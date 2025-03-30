#pragma once

#include "PreCompile.h"
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

#include "Sound.h"

class SoundMGR
{
	SINGLE(SoundMGR)
private:
	LPDIRECTSOUND8		m_SOUNDDEVICE;	// 사운드 카드 제어
	Sound*				m_pBGM;			// BGM Sound
	float				m_Time;

public:
	int Init();

	LPDIRECTSOUND8 GetSoundDevice()
	{
		return m_SOUNDDEVICE;
	}
	void RegisterToBGM(Sound* _pSound);
};