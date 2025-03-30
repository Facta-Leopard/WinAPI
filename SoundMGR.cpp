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
		MessageBox(NULL, L"���� ����̽� ���� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// ���� ������������ ����
	HWND hWnd = GameEngine::GetInstance()->GetMainWndHwnd();
	if (FAILED(m_SOUNDDEVICE->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"���� �Ŵ��� �ʱ�ȭ ����", L"SYSTEM ERROR", MB_OK);
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