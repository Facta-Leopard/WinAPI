#include "PreCompile.h"
#include "BriefingStage.h"
#include "CameraMGR.h"

#include "MenuUI.h"
#include "MovingMenu.h"
#include "MouseoverMenuUI.h"

BriefingStage::BriefingStage()
    : m_TEXTURE(nullptr)
{
    // ȭ�� �ػ� 
    FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();
}

BriefingStage::~BriefingStage()
{

}

void BriefingStage::Init()
{
    // Camera ȿ��
    CameraMGR::GetInstance()->PostProcessEffect(FADE_IN, 0.2f);

    // ����� ����
    Sound* pBGM = AssetMGR::GetInstance()->LoadSound(L"TerranBGM", L"Sound\\Trdyroom.wav");
    if (nullptr != pBGM)
    {
        pBGM->SetVolume(70.f);
        pBGM->PlayToBGM(true);
    }

    // ȭ�� �ػ� 
    FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();

    // �����̴� �ǳ�2 ����
    MovingMenuUI* SubMainPanel2 = new MovingMenuUI(L"SubMainPanel2", { vResolution.x * 0.675, vResolution.y * 0.925 }, 1.f);
    SubMainPanel2->SetName(L"SubMainPanel2");
    SubMainPanel2->SetPosition(vResolution.x * 1.3f, vResolution.y * 0.925);
    SubMainPanel2->SetScale(408.f, 70.f);
    SubMainPanel2->Init();
    SubMainPanel2->SetTriggerPointerFunction(TransferStage);
    SubMainPanel2->SetOffText();
    // MainStage Member m_VECTOROBJECTS�� ������Ʈ ����
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