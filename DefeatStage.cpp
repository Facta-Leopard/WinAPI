#include "PreCompile.h"
#include "DefeatStage.h"
#include "CameraMGR.h"

DefeatStage::DefeatStage()
    : m_TEXTURE(nullptr)
{
    m_Return = 0.f;
    m_TEXTURE = AssetMGR::GetInstance()->LoadTexture(L"TDefeat", L"Texture\\TDefeat.BMP");
}

DefeatStage::~DefeatStage()
{

}

void DefeatStage::Init()
{
    // 배경음 지정
    Sound* pBGM = AssetMGR::GetInstance()->LoadSound(L"TerranDefeat", L"Sound\\Tdefeat.wav");
    if (nullptr != pBGM)
    {
        pBGM->SetVolume(70.f);
        pBGM->PlayToBGM(true);
    }

    Sound* pSoundDefeat = nullptr;

    pSoundDefeat = AssetMGR::GetInstance()->LoadSound(L"scorefillend", L"Sound\\scorefillend.wav");

    pSoundDefeat->Play(false);
    pSoundDefeat->SetVolume(80.f);


    // Camera 효과
    CameraMGR::GetInstance()->PostProcessEffect(FADE_IN, 1.f);
}

void DefeatStage::Tick()
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

void DefeatStage::Render()
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

void DefeatStage::DeInit()
{
    DeleteAllObject();
}