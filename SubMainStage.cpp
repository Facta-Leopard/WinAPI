#include "PreCompile.h"
#include "SubMainStage.h"

#include "CameraMGR.h"

#include "Object.h"
#include "MenuUI.h"
#include "MovingMenu.h"
#include "MouseoverMenuUI.h"

SubMainStage::SubMainStage()
    : m_TEXTURE(AssetMGR::GetInstance()->LoadTexture(L"SubMainImage", L"Texture\\SubMainImage.BMP"))
{
}

SubMainStage::~SubMainStage()
{
}

void SubMainStage::Init()
{
    // 생길 때 소리
    Sound* pSound = AssetMGR::GetInstance()->LoadSound(L"MovingMenuUIIn", L"Sound\\MovingMenuUIIn.wav");

    if (nullptr != pSound)
    {
        pSound->Play(false);
        pSound->SetVolume(80.f);
    }

    // Camera 효과
    CameraMGR::GetInstance()->PostProcessEffect(FADE_IN, 0.5f);


    // 화면 해상도 
    FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();


    // ProtossCircle 메뉴 생성
    MenuUI* ProtossCircle = new MenuUI(L"LiveCircle", 1.5f);
    ProtossCircle->SetName(L"LiveCircle");
    ProtossCircle->SetPosition(vResolution.x * 0.5f, 265.f);
    ProtossCircle->SetScale(148.f, 60.f);
    ProtossCircle->SetOffText();
    ProtossCircle->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(ProtossCircle, LAYER_TYPE::MENU_PREMOUSEOVER);

    // Protoss 메뉴 생성
    MenuUI* PROTOSS = new MenuUI(L"Protoss", 5.f);
    PROTOSS->SetName(L"Protoss");
    PROTOSS->SetPosition(vResolution.x * 0.5f, 150.f);
    PROTOSS->SetScale(180.f, 240.f);
    PROTOSS->SetTriggerPointerFunction(TransferStage);
    PROTOSS->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(PROTOSS, LAYER_TYPE::MENU_MAIN);

    // MouseoverProtoss 메뉴 생성
    MouseoverMenuUI* MOUSEOVERPROTOSS = new MouseoverMenuUI(L"MouseoverProtoss", 1.5f);
    MOUSEOVERPROTOSS->SetName(L"MouseoverProtoss");
    MOUSEOVERPROTOSS->SetPosition(vResolution.x * 0.5f, 150.f);
    MOUSEOVERPROTOSS->SetScale(256.f, 256.f);
    MOUSEOVERPROTOSS->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(MOUSEOVERPROTOSS, LAYER_TYPE::MENU_MOUSEOVER);


    // TerranCircle 메뉴 생성
    MenuUI* TerranCircle = new MenuUI(L"LiveCircle", 1.5f);
    TerranCircle->SetName(L"LiveCircle");
    TerranCircle->SetPosition(vResolution.x * 0.2f, 320.f);
    TerranCircle->SetScale(148.f, 60.f);
    TerranCircle->SetOffText();
    TerranCircle->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(TerranCircle, LAYER_TYPE::MENU_PREMOUSEOVER);

    // Terran 메뉴 생성
    MenuUI* TERRAN = new MenuUI(L"Terran", 5.f);
    TERRAN->SetName(L"Terran");
    TERRAN->SetPosition(vResolution.x * 0.2f, 200.f);
    TERRAN->SetScale(180.f, 252.f);
    TERRAN->SetTriggerPointerFunction(TransferStage);
    TERRAN->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(TERRAN, LAYER_TYPE::MENU_INGAME);

    // MouseoverTerran 메뉴 생성
    MouseoverMenuUI* MOUSEOVERTERRAN = new MouseoverMenuUI(L"MouseoverTerran", 1.5f);
    MOUSEOVERTERRAN->SetName(L"MouseoverTerran");
    MOUSEOVERTERRAN->SetPosition(vResolution.x * 0.25f, 150.f);
    MOUSEOVERTERRAN->SetScale(356.f, 224.f);
    MOUSEOVERTERRAN->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(MOUSEOVERTERRAN, LAYER_TYPE::MENU_MOUSEOVER);

    // ZergCircle 메뉴 생성
    MenuUI* ZergCircle = new MenuUI(L"LiveCircle", 1.5f);
    ZergCircle->SetName(L"LiveCircle");
    ZergCircle->SetPosition(vResolution.x * 0.8f, 340.f);
    ZergCircle->SetScale(148.f, 60.f);
    ZergCircle->SetOffText();
    ZergCircle->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(ZergCircle, LAYER_TYPE::MENU_PREMOUSEOVER);

    // Zerg 메뉴 생성
    MenuUI* ZERG = new MenuUI(L"Zerg", 5.f);
    ZERG->SetName(L"Zerg");
    ZERG->SetPosition(vResolution.x * 0.8f, 200.f);
    ZERG->SetScale(204.f, 280.f);
    PROTOSS->SetTriggerPointerFunction(TransferStage);
    ZERG->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(ZERG, LAYER_TYPE::MENU_BRIEDFING);


    // MouseoverZerg 메뉴 생성
    MouseoverMenuUI* MOUSEOVERZERG = new MouseoverMenuUI(L"MouseoverZerg", 1.5f);
    MOUSEOVERZERG->SetName(L"MouseoverZerg");
    MOUSEOVERZERG->SetPosition(vResolution.x * 0.8f, 200.f);
    MOUSEOVERZERG->SetScale(256.f, 256.f);
    MOUSEOVERZERG->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(MOUSEOVERZERG, LAYER_TYPE::MENU_MOUSEOVER);


    // 움직이는 판넬1 생성
    MovingMenuUI* SubMainPanel1 = new MovingMenuUI(L"SubMainPanel1", { vResolution.x * 0.35, vResolution.y * 0.9 }, 1.f);
    SubMainPanel1->SetName(L"SubMainPanel1");
    SubMainPanel1->SetPosition(vResolution.x * 0.3f * (-1), vResolution.y * 0.9);
    SubMainPanel1->SetScale(436.f, 89.f);
    SubMainPanel1->Init();
    SubMainPanel1->SetTriggerPointerFunction(TransferStage);
    SubMainPanel1->SetOffText();
    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(SubMainPanel1, LAYER_TYPE::MENU_MAIN);

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

void SubMainStage::DeInit()
{
    Sound* pSound = AssetMGR::GetInstance()->LoadSound(L"MovingMenuUIOut", L"Sound\\MovingMenuUIOut.wav");

    if (nullptr != pSound)
    {
        pSound->Play(false);
        pSound->SetVolume(80.f);
    }
	DeleteAllObject();
}

void SubMainStage::Tick()
{
    Stage::Tick();
}

void SubMainStage::Render()
{
    HDC dc = GameEngine::GetInstance()->GetMemoryDC();

    BitBlt(dc
        , 0
        , 0
        , RESOLUTION.x
        , RESOLUTION.y
        , m_TEXTURE->GetDC()
        , 0, 0
        , SRCCOPY);

    Stage::Render();
}