#pragma once
#include "PreCompile.h"

class Stage;
class Object;

class StageMGR
{
	SINGLE(StageMGR)

	friend class KeyMGR;
	friend class TaskMGR;

private:
	Stage* m_ARRAYSTAGE[(UINT)STAGE_TYPE::EOL];	// 모든 스테이지들
	Stage* m_CURRENTSTAGE;						// 현재 재생중인 스테이지

    // 이기거나 지거나 체크하기 위함
    int                m_Player1UnitCount;
    int                m_Player2UnitCount;

    // 최대로 선택가능한 유닉 수
    int                m_MaxSelectPossibleCount;

    // 선택한 유닛 수
    int                m_SelectedUnitCount;

public:
	Stage* GetCurrentStage()
	{
		return m_CURRENTSTAGE;
	}
	
	Object* FindObjectByName(LAYER_TYPE _TYPE, const wstring& _Name);

public:
	void ChangeStage(STAGE_TYPE _ANOTHERSTAGE);

public:
	void Init();
	void Tick();

public:
	void Render();

	void MoveStage();

    void AddPlayer1UnitCount()
    {
        ++m_Player1UnitCount;
    }

    void SubtractPlayer1UnitCount()
    {
        --m_Player2UnitCount;
    }

    void AddPlayer2UnitCount()
    {
        ++m_Player2UnitCount;
    }

    void SubtractPlayer2UnitCount()
    {
        --m_Player2UnitCount;
    }

    void AddSelectedUnitCount()
    {
        ++m_SelectedUnitCount;
    }

    void SubtractSelectedUnitCount()
    {
        --m_SelectedUnitCount;
    }
};