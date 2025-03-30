#include "PreCompile.h"
#include "StageMGR.h"

#include "Stage.h"

#include "TitleStage.h"
#include "MainStage.h"
#include "SubMainStage.h"
#include "BriefingStage.h"
#include "InGameStage.h"
#include "VictoryStage.h"
#include "DefeatStage.h"

StageMGR::StageMGR()
    : m_ARRAYSTAGE{}
    , m_CURRENTSTAGE(nullptr)

    , m_Player1UnitCount(0)
    , m_Player2UnitCount(0)
    , m_MaxSelectPossibleCount(12)
    , m_SelectedUnitCount(0)

{
}

StageMGR::~StageMGR()
{
    Delete_Array(m_ARRAYSTAGE);
}

void StageMGR::Init()
{
    // 스테이지 제작
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::TITLE] = new TitleStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::MAIN] = new MainStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::SUBMAIN] = new SubMainStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::BRIEFING] = new BriefingStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::INGAME] = new InGameStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::VICTORY] = new VictoryStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::DEFEAT] = new DefeatStage;

    // 현재 스테이지을 MainStage 로 지정
    // 향후 타이틀로 변환후, 타이틀 이미지 띄운 뒤 모든 객체 로딩하는 걸로 예정
    // 임시로 조정하면서 객체 일부 로딩 시험 중

    m_CURRENTSTAGE = m_ARRAYSTAGE[(UINT)STAGE_TYPE::TITLE];
    m_CURRENTSTAGE->Init();

    KeyMGR::GetInstance()->SetMouseCursor(STARCRAFT_CURSOR);
}

void StageMGR::Tick()
{
    if (nullptr == m_CURRENTSTAGE)
        return;

    m_CURRENTSTAGE->Tick();
    m_CURRENTSTAGE->FinalTick();
}

void StageMGR::Render()
{
    m_CURRENTSTAGE->Render();
}

void StageMGR::MoveStage()
{
    wstring tName = GetCurrentStage()->GetName();
    if (L"MouseoverSinglePlayer" == tName)
    {
        ChangeStage(STAGE_TYPE::SUBMAIN);
    }
    else if (L"MouseoverExit" == tName)
    {
        PostQuitMessage(0);
    }
    else
    {
        ChangeStage(STAGE_TYPE::MAIN);
    }
}

void StageMGR::ChangeStage(STAGE_TYPE _ANOTHERSTAGE)
{
    // 1. 현재 스테이지과 변경하려는 스테이지이 동일하면 아무일도 안일어난다.
    if (m_CURRENTSTAGE == m_ARRAYSTAGE[(UINT)_ANOTHERSTAGE])
        return;
    else
    {
        KeyMGR::GetInstance()->SetCursorType(CURSOR_TYPE::STARCRAFT_CURSOR);
    }

    // 2. 현재 스테이지에 End 를 호출시킨다.
    m_CURRENTSTAGE->DeInit();

    // 3. 변경 요청한 스테이지을 현재 스테이지로 지정한다.
    m_CURRENTSTAGE = m_ARRAYSTAGE[(UINT)_ANOTHERSTAGE];

    // 3. 변경된 스테이지의 Begin 을 호출시킨다.
    m_CURRENTSTAGE->Init();

}

Object* StageMGR::FindObjectByName(LAYER_TYPE _LAYER, const wstring& _Name)
{
    if (nullptr == m_CURRENTSTAGE)
        return nullptr;

    return m_CURRENTSTAGE->FindObjectByName(_LAYER, _Name);
}