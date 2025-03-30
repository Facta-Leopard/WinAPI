//#pragma once
//#include "Component.h"
//
//class Animation;
//
//class R_AnimationPlayer :
//    public Component
//{
//private:
//    vector<Animation*>  m_veAnimation;  // ANIMATION 목록
//    Animation*          m_CURRENTANIMATION;  // 현재 재생중인 ANIMATION
//    int                 m_SpriteIdx;    // 현재 재생중인 ANIMATION 에서, 화면에 노출중인 Sprite 인덱스
//
//    float               m_FPS;          // ANIMATION 재생속도
//    float               m_Time;         // 누적시간
//    bool                m_Repeat;       // 반복재생인지 아닌지
//    bool                m_Finish;       // 재생이 끝났는지 체크
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