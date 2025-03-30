#include "PreCompile.h"
#include "VictoryStage.h"

#include "CameraMGR.h"

VictoryStage::VictoryStage()
    : m_TEXTURE(nullptr)
{
    m_Return = 0.f;
    m_TEXTURE = AssetMGR::GetInstance()->LoadTexture(L"TVictory", L"Texture\\TVictory.BMP");
}

VictoryStage::~VictoryStage()
{
}

void VictoryStage::Init()
{
    // 배경음 지정
    Sound* pBGM = AssetMGR::GetInstance()->LoadSound(L"TerranVictory", L"Sound\\tvict.wav");
    if (nullptr != pBGM)
    {
        pBGM->SetVolume(70.f);
        pBGM->PlayToBGM(true);
    }

	Sound* pSoundVictory = nullptr;

    pSoundVictory = AssetMGR::GetInstance()->LoadSound(L"scorefillend", L"Sound\\scorefillend.wav");

    pSoundVictory->Play(false);
    pSoundVictory->SetVolume(80.f);


    // Camera 효과
    CameraMGR::GetInstance()->PostProcessEffect(FADE_IN, 1.f);
}

void VictoryStage::Tick()
{
    Stage::Tick();
    m_Return += DELTATIME;

    if (8.f < m_Return)
    {
        Sound* pBGM = AssetMGR::GetInstance()->LoadSound(L"Title", L"Sound\\Title.wav");
        if (nullptr != pBGM)
        {
            pBGM->SetVolume(70.f);
            pBGM->PlayToBGM(true);
        }
        StageMGR::GetInstance()->ChangeStage(STAGE_TYPE::TITLE);
    }
}

void VictoryStage::DeInit()
{
	DeleteAllObject();
}

void VictoryStage::Render()
{
    HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
    FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();


    TransparentBlt(tDC
        , 0
        , 0
        , RESOLUTION.x
        , RESOLUTION.y
        , m_TEXTURE->GetDC()
        , 0
        , 0
        , RESOLUTION.x
        , RESOLUTION.y
        , RGB(0, 0, 0));
}