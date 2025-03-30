//#pragma once
//#include "Component.h"
//
//class Animation;
//
//class R_AnimationPlayer :
//    public Component
//{
//private:
//    vector<Animation*>  m_veAnimation;  // ANIMATION ���
//    Animation*          m_CURRENTANIMATION;  // ���� ������� ANIMATION
//    int                 m_SpriteIdx;    // ���� ������� ANIMATION ����, ȭ�鿡 �������� Sprite �ε���
//
//    float               m_FPS;          // ANIMATION ����ӵ�
//    float               m_Time;         // �����ð�
//    bool                m_Repeat;       // �ݺ�������� �ƴ���
//    bool                m_Finish;       // ����� �������� üũ
//
//public:
//    void AddANIMATION(Animation* _ANIMATION) { m_veAnimation.push_back(_ANIMATION); }
//    void AddANIMATION(int _idx, Animation* _ANIMATION)
//    {
//        if (m_veAnimation.size() <= _idx)
//        {
//            m_veAnimation.resize(_idx + 1);
//        }
//
//        m_veAnimation[_idx] = _ANIMATION;
//    }
//
//    void Play(int _AnimaionIndex, float _FPS, bool _Repeat)
//    {
//        m_CURRENTANIMATION = m_veAnimation[_AnimaionIndex];
//        m_SpriteIdx = 0;
//        m_FPS = _FPS;
//        m_Repeat = _Repeat;
//        m_Finish = false;
//        m_Time = 0.f;
//    }
//
//    bool IsFinish() { return m_Finish; }
//
//    void Reset()
//    {
//        m_Finish = false;
//        m_SpriteIdx = 0;
//    }
//
//
//public:
//    virtual void FinalTick() override;
//    void Render();
//
//public:
//    R_AnimationPlayer();
//    ~R_AnimationPlayer();
//};