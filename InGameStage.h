#pragma once
#include "Stage.h"
#include "Map.h"
#include "Portrait.h"

class InGameStage :
    public Stage
{
public:
    InGameStage();
    ~InGameStage();

    // �� �κ��� ���� ���ȭ�ϴ� ���� ������
    // �ð��� �����Ƿ� �ϴ� ������ ����
    friend class Player_Unit;
    friend class Player2_Unit;

 private:
bool                m_Menu;

// PortraitMGR�� �ȵǼ� �� ������� �׽�Ʈ ��
vector<Portrait*>	m_VECTOR_PORTRAIT;

// �ÿ��� ���
// �̷��Ա��� �ϱ� �Ⱦ��µ�..

Portrait            m_TEMPPORTRAIT;

int                 m_PortraitCount;

// �巡�׾ص� �׸�׸���� ������
DragAndDrop         m_DRAGANDDROPBOX;

//DragAndDrop         m_MINIMAPTANGLEPOSITION;

bool                m_Player1Selected;
bool                m_Player2Selected;

bool                m_Portrait_Talking;
float               m_Portrait_Duration_Talking;

bool                m_Portrait_In_Out;
float               m_Portrait_Duration_In_Out;


bool                m_IsRelease;

// �� �ؽ�ó
Texture*            m_TEXTURE1;
// �̴ϸ� �ؽ�ó
Texture*            m_TEXTURE2;


// ��� �ؽ�ó
Texture*            m_TEXTURE_COMMAND_ATTACK;

Texture*            m_TEXTURE_COMMAND_SKILL;


// ���� ������ �ؽ�ó
Texture*            m_TEXTURE_FRAME;
Texture*            m_TEXTURE_FRAME2;

// �ÿ��� �ӽ� �ʻ�ȭ �ؽ�ó

Texture* m_TEXTURE_PORTRAIT;
Texture* m_TEXTURE_PORTRAIT2;

// �ÿ��� �ӽ� ���
float               m_Time1;
float               m_Duration1;
float               m_FPS_Time1;
int                 m_Index1;
int                 m_MaxFrame1;

float               m_Time2;
float               m_Duration2;
float               m_FPS_Time2;
int                 m_Index2;
int                 m_MaxFrame2;



public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void DeInit() override;

private:



    void KeyCheck();

    void DragAndDropCheck();

    void PortraitCheck();

    void RenderButton();
    
    void RenderUnitText();

    void RenderDragAndDrop();
    
    
    void RenderMiniMap();

    // PortraitMGR�� �ȵǼ� �� ������� �׽�Ʈ ��
    void RenderPortrait();



    void CheckTheEnd();


    // PortraitMGR�� �ȵǼ� �� ������� �׽�Ʈ ��
    void MakePortraitUnit();

public:

    void SetOnDebugging();

    void SetOffDebugging();
};


