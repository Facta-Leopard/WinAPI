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
	Stage* m_ARRAYSTAGE[(UINT)STAGE_TYPE::EOL];	// ��� ����������
	Stage* m_CURRENTSTAGE;						// ���� ������� ��������

    // �̱�ų� ���ų� üũ�ϱ� ����
    int                m_Player1UnitCount;
    int                m_Player2UnitCount;

    // �ִ�� ���ð����� ���� ��
    int                m_MaxSelectPossibleCount;

    // ������ ���� ��
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