#include "PreCompile.h"
#include "MainStage.h"

#include "CameraMGR.h"

#include "Object.h"
#include "MenuUI.h"
#include "MouseoverMenuUI.h"

MainStage::MainStage()
    : m_TEXTURE(AssetMGR::GetInstance()->LoadTexture(L"MainImage", L"Texture\\MainImage.BMP"))
{
}

MainStage::~MainStage()
{

}

void MainStage::Init()
{
    // Camera 효과
    CameraMGR::GetInstance()->PostProcessEffect(FADE_IN, 0.2f);

    // 화면 해상도
    FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();

    // MouseoverSinglePlayer 메뉴 생성
    MouseoverMenuUI* MOUSEOVERSINGLEPLAYER = new MouseoverMenuUI(L"MouseoverSinglePlayer", 6.f);
    MOUSEOVERSINGLEPLAYER->SetName(L"MouseoverSinglePlayer");
    MOUSEOVERSINGLEPLAYER->SetPosition(vResolution.x / 5.f, 140.f);
    MOUSEOVERSINGLEPLAYER->SetScale(252.f, 124.f);
    MOUSEOVERSINGLEPLAYER->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(MOUSEOVERSINGLEPLAYER, LAYER_TYPE::MENU_PREMOUSEOVER);


    // SinglePlayer 메뉴 생성
    MenuUI* SINGLEPLAYER = new MenuUI(L"SinglePlayer");
    SINGLEPLAYER->SetName(L"SinglePlayer");
    SINGLEPLAYER->SetPosition(vResolution.x / 5.f, 100.f);
    SINGLEPLAYER->SetScale(320.f, 116.f);
    SINGLEPLAYER->SetOnText();
    SINGLEPLAYER->SetTriggerPointerFunction(TransferStage);
    SINGLEPLAYER->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(SINGLEPLAYER, LAYER_TYPE::MENU_SUBMAIN);


    // Exit 메뉴 생성
    MenuUI* EXITMENU = new MenuUI(L"Exit");
    EXITMENU->SetName(L"Exit");
    EXITMENU->SetPosition(vResolution.x * (3.8f / 5.f), vResolution.y * 0.7f);
    EXITMENU->SetScale(184.f, 128.f);
    EXITMENU->SetOnText();
    EXITMENU->SetTriggerPointerFunction(TransferStage);
    EXITMENU->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(EXITMENU, LAYER_TYPE::MENU_EXIT);

    // MouseoverExit 메뉴 생성
    MouseoverMenuUI* MOUSEOVEREXIT = new MouseoverMenuUI(L"MouseoverExit");
    MOUSEOVEREXIT->SetName(L"MouseoverExit");
    MOUSEOVEREXIT->SetPosition(vResolution.x * (4.f / 5.f), vResolution.y * 0.7f);
    MOUSEOVEREXIT->SetScale(216.f, 136.f);
    MOUSEOVEREXIT->Init();

    // MainStage Member m_VECTOROBJECTS에 오브젝트 삽입
    AddObject(MOUSEOVEREXIT, LAYER_TYPE::MENU_MOUSEOVER);

}

void MainStage::DeInit()
{
    DeleteAllObject();
}

void MainStage::Tick()
{
    Stage::Tick();
}

void MainStage::Render()
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
}