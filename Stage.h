#pragma once
#include "Collider.h"

class Stage :
    public Foundation
{
    friend class UIMGR;

public:
    Stage();
    ~Stage();

private:
    vector<Object*>    m_VECTOROBJECTS[(UINT)LAYER_TYPE::EOL];
    vector<Collider*>  c_VECTORCOLLIDER[(UINT)LAYER_TYPE::EOL];

public:
    virtual void Init();
    virtual void Tick();
    virtual void FinalTick();
    virtual void Render();
    virtual void DeInit() = 0;

public:
    void AddObject(Object* _Object, LAYER_TYPE _Type);
    const vector<Object*>& GetObjects(LAYER_TYPE _Type) { return m_VECTOROBJECTS[(UINT)_Type]; }

    // Collider �� ���̾� ��ȣ�� �´� ���� ���
    void RegisterCollider(Collider* _COLLIDER, LAYER_TYPE _Type) { c_VECTORCOLLIDER[(UINT)_Type].push_back(_COLLIDER); }
    const vector<Collider*>& GetColliders(LAYER_TYPE _Type) { return c_VECTORCOLLIDER[(UINT)_Type]; }

    Object* FindObjectByName(LAYER_TYPE _Layer, const wstring& _Name);

protected:
    void DeleteObject(int _LayerIdx);
    void DeleteAllObject();


    // �׽�Ʈ�� �Լ�
    // �������Լ��� �ϸ� ���� �� �ѵ�..
    // �ӽ÷� ����
public:

//virtual void SetPortraitPlayer1Selected()
//{}
//
//virtual void SetPortraitPlayer2Selected()
//{}

};