#pragma once

class Asset;

class Sprite :
    public Asset
{
private:
    Texture* m_ATLAS;    // ��������Ʈ�� Ÿ������ ������ ��Ʋ�� �ؽ���

    FloatPoint        m_UPLEFT;  // ��, ��� �ȼ� ��ġ
    FloatPoint        m_SLICE;    // ���� ũ��
    FloatPoint        m_OFFSET;   // �߰� �����̵�

public:
    Texture* GetAtlas() { return m_ATLAS; }
    FloatPoint GetLeftTop() { return m_UPLEFT; }
    FloatPoint GetSlice() { return m_SLICE; }
    FloatPoint GetOffset() { return m_OFFSET; }

    void SetOffset(FloatPoint _OFFSET) { m_OFFSET = _OFFSET; }
public:
    virtual int Save(const wstring& _RelativePath) override;
    virtual int Load(const wstring& _RelativePath) override;

    void Create(Texture* _Atlas, FloatPoint _LeftTop, FloatPoint _Slice);

public:
    Sprite();
    ~Sprite();
};