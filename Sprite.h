#pragma once

class Asset;

class Sprite :
    public Asset
{
private:
    Texture* m_ATLAS;    // 스프라이트가 타겟으로 지정한 아틀라스 텍스쳐

    FloatPoint        m_UPLEFT;  // 좌, 상단 픽셀 위치
    FloatPoint        m_SLICE;    // 조각 크기
    FloatPoint        m_OFFSET;   // 추가 보정이동

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