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

    // 이 부분은 향후 모듈화하는 것이 좋을듯
    // 시간이 없으므로 일단 프렌드 선언
    friend class Player_Unit;
    friend class Player2_Unit;

 private:
bool                m_Menu;

// PortraitMGR이 안되서 이 방법으로 테스트 중
vector<Portrait*>	m_VECTOR_PORTRAIT;

// 시연용 멤버
// 이렇게까지 하기 싫었는데..

Portrait            m_TEMPPORTRAIT;

int                 m_PortraitCount;

// 드래그앤드 네모그리기용 변수들
DragAndDrop         m_DRAGANDDROPBOX;

//DragAndDrop         m_MINIMAPTANGLEPOSITION;

bool                m_Player1Selected;
bool                m_Player2Selected;

bool                m_Portrait_Talking;
float               m_Portrait_Duration_Talking;

bool                m_Portrait_In_Out;
float               m_Portrait_Duration_In_Out;


bool                m_IsRelease;

// 맵 텍스처
Texture*            m_TEXTURE1;
// 미니맵 텍스처
Texture*            m_TEXTURE2;


// 명령 텍스처
Texture*            m_TEXTURE_COMMAND_ATTACK;

Texture*            m_TEXTURE_COMMAND_SKILL;


// 유닛 프레임 텍스처
Texture*            m_TEXTURE_FRAME;
Texture*            m_TEXTURE_FRAME2;

// 시연용 임시 초상화 텍스처

Texture* m_TEXTURE_PORTRAIT;
Texture* m_TEXTURE_PORTRAIT2;

// 시연용 임시 멤버
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

    // PortraitMGR이 안되서 이 방법으로 테스트 중
    void RenderPortrait();



    void CheckTheEnd();


    // PortraitMGR이 안되서 이 방법으로 테스트 중
    void MakePortraitUnit();

public:

    void SetOnDebugging();

    void SetOffDebugging();
};


