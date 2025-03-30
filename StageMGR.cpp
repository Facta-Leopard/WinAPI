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
    // �������� ����
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::TITLE] = new TitleStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::MAIN] = new MainStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::SUBMAIN] = new SubMainStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::BRIEFING] = new BriefingStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::INGAME] = new InGameStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::VICTORY] = new VictoryStage;
    m_ARRAYSTAGE[(UINT)STAGE_TYPE::DEFEAT] = new DefeatStage;

    // ���� ���������� MainStage �� ����
    // ���� Ÿ��Ʋ�� ��ȯ��, Ÿ��Ʋ �̹��� ��� �� ��� ��ü �ε��ϴ� �ɷ� ����
    // �ӽ÷� �����ϸ鼭 ��ü �Ϻ� �ε� ���� ��

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
    // 1. ���� ���������� �����Ϸ��� ���������� �����ϸ� �ƹ��ϵ� ���Ͼ��.
    if (m_CURRENTSTAGE == m_ARRAYSTAGE[(UINT)_ANOTHERSTAGE])
        return;
    else
    {
        KeyMGR::GetInstance()->SetCursorType(CURSOR_TYPE::STARCRAFT_CURSOR);
    }

    // 2. ���� ���������� End �� ȣ���Ų��.
    m_CURRENTSTAGE->DeInit();

    // 3. ���� ��û�� ���������� ���� ���������� �����Ѵ�.
    m_CURRENTSTAGE = m_ARRAYSTAGE[(UINT)_ANOTHERSTAGE];

    // 3. ����� ���������� Begin �� ȣ���Ų��.
    m_CURRENTSTAGE->Init();

}

Object* StageMGR::FindObjectByName(LAYER_TYPE _LAYER, const wstring& _Name)
{
    if (nullptr == m_CURRENTSTAGE)
        return nullptr;

    return m_CURRENTSTAGE->FindObjectByName(_LAYER, _Name);
}