#pragma once

#include "StarUnit.h"
#include "Texture.h"

#include "PortraitMGR.h"

class Player_Unit :
    public StarUnit
{
    // �ÿ��� ���ϴ� �ϴ�, ������ �� ��������
    friend class InGameStage;
    friend class Player2_Unit;


public:
    Player_Unit(wstring _wString, UNIT_TYPE m_UNITTYPE, float _duration = 1.f);
    virtual ~Player_Unit();

protected:
    // ������ ǥ��
    vector<MovingMotion*>   m_VECTOR_MOVINGMOTION;

    // �ΰ����� FSM ������Ʈ ����
    // �׽�Ʈ � �غ��� ��������
    // vector<FSM*>            m_VECTOR_FSM;

    UNIT_TYPE               m_UNITTYPE;
    STATE_TYPE              m_STATETYPE;
    MOVINGMOTION_TYPE       m_MOVINGMOTIONTYPE;

    FloatPoint              m_WASPOSITION;
    float                   m_DirectionAngle;


    bool                    m_Debugging;

    // ������ ���°�
    // �׽�Ʈ ��
    // ���� Setter�� �����ϴ� ���� ���� ��

    int                     m_MaxHitPoint;
    int                     m_IsHitPoint;
    int                     m_wasHitPoint;
    int                     m_AttackPoint;


    bool                    m_Skill_On;
    float                   m_Skill_Duration;

    // ������ �þ�
    // �׽�Ʈ ��
    // ���� Setter�� �����ϴ� ���� ���� ��
    int                     m_ViewRange;
    int                     m_AttackRange;

    // ������ �ӵ�
    // �׽�Ʈ ��
    // ���� Setter�� �����ϴ� ���� ���� ��
    float                   m_MoveSpeed;
    float                   m_AttackSpeed;
    float                   m_AttackDuration;

    // ���׷��̵� ����
    // �׽�Ʈ ��
    // ���� Setter�� �����ϴ� ���� ���� ��
    int                     m_ShieldUpgrade;
    int                     m_DefenseUpgrade;
    int                     m_AttackUpgrade;

    bool                    m_IsSelected;

    // ����, ������ Ŭ�� ���� ����� ��ӹ��� Ŭ�������� ��������
    Player_Unit*            m_TARGET;
    FloatPoint*             m_TARGETPOSITION;

    bool                    m_TargetMouseover;
    bool                    m_IsTagetSelected;

    // ���Ⱚ�� ��Ʈ������ �ϰ�, �÷��׷� ����ŷ�ϸ� �뷮ȿ������ �� ���� �� ������..
    // ���� �װű��� �������ڴ� �Ӹ��� ������ �׳� boolean���� ����..

    // ��� ����
    // �׽�Ʈ ��
    bool                    m_KeyOrder;
    bool                    m_KeyAttack;
    bool                    m_KeyMove;

    bool                    m_IsOrder;
    bool                    m_OrderMove;
    bool                    m_OrderAttack;

    // FSM ����
    bool                    m_IsUnderAttack;

    bool                    m_IsMouseover;
    bool                    m_WasMouseover;

    // �Ҹ��������
    bool                    m_Soundable;
    float                   m_SoundDuration;

    // �������Լ��� ���� ��� ���� �߱�
protected:

    // StarUnit Memeber : Pointer Function
    // std::function<void(LAYER_TYPE)> m_Trigger_PointerFunction;

    // �������Լ��� ���� ��� ���� �߱�(����)
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

    // �̰� �������� Ȯ�� ��
    //virtual Player_Unit* AttackRangeCheck();

    // �׽�Ʈ�� �ڵ�
 // �浹����
    virtual bool CollisionCheck();
    
    virtual void SelectRender();
    
 

    // �׽�Ʈ�� �ڵ�
    // FSM �ڵ带 �Ϻ� ���� ��
    // �׽�Ʈ ��, ������Ʈ�� ���� ��������
    virtual void TemporaryFSMCheck();

    // FSM ���� boole�� �����ϴ� �Լ� �϶�

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

    // FloatPoint* �� ��������� Ÿ���� ����Ű�� ����


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

    // �������Լ��� ���� ��� ����
    // Ʈ���ſ� ������ �Լ�
    virtual void SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction);

    // Ʈ���ſ� ������ �Լ�(�����ε� : �������� ������ �Լ�)
    virtual void SetTriggerPointerFunction2(std::function<void(UNIT_TYPE, MOVINGMOTION_TYPE, POINT)> PointFunction);

    // ���� ����� ������ �Լ�
    virtual void SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction);

    // ���� ����� ������ �Լ�(�����ε� : ������ ���ϴ� ������ �Լ�)
    virtual void SetSoundPointerFunction2(std::function<void(UNIT_TYPE, MOVINGMOTION_TYPE)> PointFunction);
};