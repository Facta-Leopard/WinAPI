#include "PreCompile.h"
#include "BriefingStage.h"
#include "CameraMGR.h"

#include "MenuUI.h"
#include "MovingMenu.h"
#include "MouseoverMenuUI.h"

BriefingStage::BriefingStage()
    : m_TEXTURE(nullptr)
{
    // 화면 해상도 
    FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();
}

BriefingStage::~BriefingStage()
{

}

void BriefingStage::Init()
{
    // Camera 효과
    CameraMGR::GetInstance()->PostProcessEffect(FADE_IN, 0.2f);

    // 배경음 지정
    Sound* pBGM = AssetMGR::GetInstance()->LoadSound(L"TerranBGM", L"Sound\\Trdyroom.wav");
    if (nullptr != pBGM)
    {
        pBGM->SetVolume(70.f);
        pBGM->PlayToBGM(true);
    }

    // 화면 해상도 
    FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();

    // 움직이는 판넬2 생성
    MovingMenuUI* SubMainPanel2 = new MovingMenuUI(L"SubMainPanel2", { vResolution.x * 0.675, vResolution.y * 0.925 }, 1.f);
    SubMainPanel2->SetName(L"SubMainPanel2");
    SubMainPanel2->SetPosition(vResolution.x * 1.3f, vResolution.y * 0.925);
    SubMainPanel2->SetScale(408.f, 70.f);
    SubMainPanel2->Init();
    SubMainPanel2->SetTriggerPointerFunction(TransferStage);
    SubMainPanel2->SetOffText();
    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(SubMainPanel2, LAYER_TYPE::MENU_MAIN);
}

void BriefingStage::Tick()
{
    Stage::Tick();
}

void BriefingStage::Render()
{
    Stage::Render();
    m_TEXTURE = AssetMGR::GetInstance()->LoadTexture(L"TBriefing", L"Texture\\TBriefing.BMP");
}

void BriefingStage::DeInit()
{
    DeleteAllObject();
}