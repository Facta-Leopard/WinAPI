#pragma once

#include "StarUnit.h"
#include "Texture.h"

#include "PortraitMGR.h"

class Player_Unit :
    public StarUnit
{
    // 시연이 급하니 일단, 프랜드 다 떄려박자
    friend class InGameStage;
    friend class Player2_Unit;


public:
    Player_Unit(wstring _wString, UNIT_TYPE m_UNITTYPE, float _duration = 1.f);
    virtual ~Player_Unit();

protected:
    // 움직임 표현
    vector<MovingMotion*>   m_VECTOR_MOVINGMOTION;

    // 인공지능 FSM 컴포넌트 벡터
    // 테스트 몇개 해보고 구현예정
    // vector<FSM*>            m_VECTOR_FSM;

    UNIT_TYPE               m_UNITTYPE;
    STATE_TYPE              m_STATETYPE;
    MOVINGMOTION_TYPE       m_MOVINGMOTIONTYPE;

    FloatPoint              m_WASPOSITION;
    float                   m_DirectionAngle;


    bool                    m_Debugging;

    // 유닛의 상태값
    // 테스트 중
    // 향후 Setter를 설정하는 것이 좋을 듯

    int                     m_MaxHitPoint;
    int                     m_IsHitPoint;
    int                     m_wasHitPoint;
    int                     m_AttackPoint;


    bool                    m_Skill_On;
    float                   m_Skill_Duration;

    // 유닛의 시야
    // 테스트 중
    // 향후 Setter를 설정하는 것이 좋을 듯
    int                     m_ViewRange;
    int                     m_AttackRange;

    // 유닛의 속도
    // 테스트 중
    // 향후 Setter를 설정하는 것이 좋을 듯
    float                   m_MoveSpeed;
    float                   m_AttackSpeed;
    float                   m_AttackDuration;

    // 업그레이드 관련
    // 테스트 중
    // 향후 Setter를 설정하는 것이 좋을 듯
    int                     m_ShieldUpgrade;
    int                     m_DefenseUpgrade;
    int                     m_AttackUpgrade;

    bool                    m_IsSelected;

    // 향후, 오른쪽 클릭 등의 기능은 상속받을 클래스에서 구현하자
    Player_Unit*            m_TARGET;
    FloatPoint*             m_TARGETPOSITION;

    bool                    m_TargetMouseover;
    bool                    m_IsTagetSelected;

    // 성향값을 인트값으로 하고, 플래그로 마스킹하면 용량효율성은 더 좋을 것 같지만..
    // 지금 그거까지 생각하자니 머리가 아프니 그냥 boolean으로 하자..

    // 명령 관련
    // 테스트 중
    bool                    m_KeyOrder;
    bool                    m_KeyAttack;
    bool                    m_KeyMove;

    bool                    m_IsOrder;
    bool                    m_OrderMove;
    bool                    m_OrderAttack;

    // FSM 대비용
    bool                    m_IsUnderAttack;

    bool                    m_IsMouseover;
    bool                    m_WasMouseover;

    // 소리재생관련
    bool                    m_Soundable;
    float                   m_SoundDuration;

    // 포인터함수를 통한 기능 구현 추구
protected:

    // StarUnit Memeber : Pointer Function
    // std::function<void(LAYER_TYPE)> m_Trigger_PointerFunction;

    // 포인터함수를 통한 기능 구현 추구(사운드)
    // std::function<void(UNIT_TYPE)> m_Sound_PointerFunction;

    std::function<void(UNIT_TYPE, MOVINGMOTION_TYPE, POINT)> m_Trigger_PointerFunction2;
    std::function<void(UNIT_TYPE, MOVINGMOTION_TYPE)> m_Sound_PointerFunction2;

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render() override;

    virtual void TextRender();

    virtual void SetPosition(float _x, float _y) final
    {
        m_POSITION = FloatPoint(_x, _y);
        m_WASPOSITION = m_POSITION;
    }

    virtual void PlaySound() override;

    virtual void MouseoverCheck() override;

    virtual void KeyCheck();

    virtual void SelectedCheck();

    virtual void DirectionCheck();

    virtual bool ViewRangeCheck(Player_Unit* _TARGET);

    virtual bool AttackRangeCheck();

    // 이게 문제인지 확인 중
    //virtual Player_Unit* AttackRangeCheck();

    // 테스트용 코드
 // 충돌관련
    virtual bool CollisionCheck();
    
    virtual void SelectRender();
    
 

    // 테스트용 코드
    // FSM 코드를 일부 실험 중
    // 테스트 후, 컴포넌트로 별도 구현예정
    virtual void TemporaryFSMCheck();

    // FSM 관련 boole값 조정하는 함수 일람

    void SetIsUnderAttack(bool _IsUnderAttack)
    {
        m_IsUnderAttack = _IsUnderAttack;
    }

    void SetTarget(Player_Unit* _Unit)
    {
        m_TARGET = _Unit;
    }





    //virtual void MovingMotionTypeCheck();

    virtual void MakeMovingMotionUnit();

    void Attack();

    void SetHitPoint(int _damege)
    {
        m_IsHitPoint -= _damege;
    }

    void Move();

    // FloatPoint* 는 상대적으로 타겟을 가르키기 위함


    bool GetIsSelected()
    {
        return m_IsSelected;
    }

    Player_Unit* GetTarget()
    {
        return m_TARGET;
    }

    void SetOnDebugging()
    {
        m_Debugging = true;
    }

    void SetOffDebugging()
    {
        m_Debugging = false;
    }

    // 포인터함수를 통한 기능 설정
    // 트리거용 포인터 함수
    virtual void SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction);

    // 트리거용 포인터 함수(오버로드 : 모션재생용 포인터 함수)
    virtual void SetTriggerPointerFunction2(std::function<void(UNIT_TYPE, MOVINGMOTION_TYPE, POINT)> PointFunction);

    // 사운드 재생용 포인터 함수
    virtual void SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction);

    // 사운드 재생용 포인터 함수(오버로드 : 유닛이 말하는 포인터 함수)
    virtual void SetSoundPointerFunction2(std::function<void(UNIT_TYPE, MOVINGMOTION_TYPE)> PointFunction);
};