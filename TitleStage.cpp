#include "PreCompile.h"
#include "TitleStage.h"

#include "CameraMGR.h"

#include "Object.h"

TitleStage::TitleStage()
	: m_TEXTURE(AssetMGR::GetInstance()->LoadTexture(L"TitleIamge", L"Texture\\TitleImage.BMP"))
	, m_Time(0.f)
{
}

TitleStage::~TitleStage()
{
}

void TitleStage::Init()
{
	// Camera 효과
	CameraMGR::GetInstance()->PostProcessEffect(FADE_IN, 0.2f);

	// 배경음 지정
	Sound* pBGM = AssetMGR::GetInstance()->LoadSound(L"Title", L"Sound\\Title.wav");
	if (nullptr != pBGM)
	{
		pBGM->SetVolume(70.f);
		pBGM->PlayToBGM(true);
	}
}

void TitleStage::DeInit()
{
}

void TitleStage::LoadAllObject()
{
}

void TitleStage::Tick()
{
	Render();
	Stage::Tick();
	m_Time += DELTATIME;

	if (5 < m_Time)
	{
		StageMGR::GetInstance()->ChangeStage(STAGE_TYPE::MAIN);
	}
}

void TitleStage::Render()
{
	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();

	BitBlt(tDC
		, 0
		, 0
		, RESOLUTION.x
		, RESOLUTION.y
		, m_TEXTURE->GetDC()
		, 0, 0
		, SRCCOPY);

	Stage::Render();

	FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();

	// 로딩중이라는 텍스트 구현
	if (1 >= (m_Time / 2))
	{
		SetTextColor(tDC, RGB(100, 250, 100));
		SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
		TextOutW(tDC, (vResolution.x * 0.45)
			, (vResolution.y * 0.85)
			, L"Loading.", 8); // 메뉴 텍스트
	}
	else if (1 >= (m_Time / 3))
	{
		SetTextColor(tDC, RGB(125, 250, 125));
		SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
		TextOutW(tDC, (vResolution.x * 0.45)
			, (vResolution.y * 0.85)
			, L"Loading..", 9); // 메뉴 텍스트
	}
	else
	{
		SetTextColor(tDC, RGB(150, 250, 150));
		SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
		TextOutW(tDC, (vResolution.x * 0.45)
			, (vResolution.y * 0.85)
			, L"Loading...", 10); // 메뉴 텍스트
	}
}