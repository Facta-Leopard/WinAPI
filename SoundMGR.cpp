#include "PreCompile.h"
#include "SoundMGR.h"

SoundMGR::SoundMGR()
	: m_SOUNDDEVICE(nullptr)
	, m_pBGM(nullptr)
	, m_Time(0.f)
{
}

SoundMGR::~SoundMGR()
{

}

int SoundMGR::Init()
{
	if (FAILED(DirectSoundCreate8(NULL, &m_SOUNDDEVICE, NULL)))
	{
		MessageBox(NULL, L"사운드 디바이스 생성 실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 협조스테이지 설정
	HWND hWnd = GameEngine::GetInstance()->GetMainWndHwnd();
	if (FAILED(m_SOUNDDEVICE->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"사운드 매니저 초기화 실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void SoundMGR::RegisterToBGM(Sound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}