#pragma once
#include "assert.h"
#include <cmath>

struct FloatPoint
{
public:
	FloatPoint()
		: x(0.f)
		, y(0.f)
	{
	}

	template <typename T>
	FloatPoint(T _x, T _y)
		: x((float)_x)
		, y((float)_y)
	{
	}

	FloatPoint(const FloatPoint& _OTHER)
		: x(_OTHER.x)
		, y(_OTHER.y)
	{
	}

	FloatPoint(const POINT& _OTHER)
		: x((float)_OTHER.x)
		, y((float)_OTHER.y)
	{
	}

	~FloatPoint()
	{
	}

public:
	float x;
	float y;

public:
	// ������ ����
	float Length()
	{
		return sqrt((x * x) + (y * y));
	}

	// ����ȭ
	void Normalize()
	{
		float Len = Length();
		x /= Len;
		y /= Len;
	}

	// ����
	float DotProduct(const FloatPoint& _OTHER) const
	{
		return x * _OTHER.x + y * _OTHER.y;
	}

	// ����
	// ���� ����̸� A�� B�� �������� �ݽð� �������� ȸ���ϰ� �ִٴ� �ǹ�
	// ���� ���� �����̸� A�� B�� �������� �ð� �������� ȸ���ϰ� �ִٴ� �ǹ�
	float CrossProduct(const FloatPoint& _OTHER) const
	{
		return ((x * _OTHER.x) - y * _OTHER.y);
	}


	// �ƴ� ����..
	// ���� ������� �����ؾߵ� ���� ������ ���ߴµ�..
	// �ڲ� �̻��ѵ��� ���װ� ������ �İ��İ��� ���Ⱑ ��������..

	FloatPoint& operator=(const FloatPoint& other)
	{
		if (this != &other) {

			x = other.x;
			y = other.y;
		}
		return *this;
	}


	FloatPoint operator + (FloatPoint _OTHER)
	{
		return FloatPoint(x + _OTHER.x, y + _OTHER.y);
	}

	FloatPoint operator + (float _IN)
	{
		return FloatPoint(x + _IN, y + _IN);
	}
	
	void operator += (FloatPoint _OTHER)
	{
		x += _OTHER.x; y += _OTHER.y;
	}
	
	void operator += (float _IN)
	{
		x += _IN; y += _IN;
	}

	FloatPoint operator - (FloatPoint _OTHER)
	{
		return FloatPoint(x - _OTHER.x, y - _OTHER.y);
	}
	
	FloatPoint operator - (float _IN)
	{
		return FloatPoint(x - _IN, y - _IN);
	}
	
	void operator -= (FloatPoint _OTHER)
	{
		x -= _OTHER.x; y -= _OTHER.y;
	}

	void operator -= (float _IN)
	{
		x -= _IN; y -= _IN;
	}

	FloatPoint operator * (FloatPoint _OTHER)
	{
		return FloatPoint(x * _OTHER.x, y * _OTHER.y);
	}
	
	FloatPoint operator * (float _IN)
	{
		return FloatPoint(x * _IN, y * _IN);
	}

	void operator *= (FloatPoint _OTHER)
	{
		x *= _OTHER.x; y *= _OTHER.y;
	}

	void operator *= (float _IN)
	{
		x *= _IN; y *= _IN; 
	}

	FloatPoint operator / (FloatPoint _OTHER)
	{
		// 0�� ��쵵 ������
		assert(_OTHER.x && _OTHER.y);
		
		return FloatPoint(x / _OTHER.x, y / _OTHER.y);
	}
	
	FloatPoint operator / (float _IN) 
	{
		// 0�� ��쵵 ������
		assert(_IN);
		
		return FloatPoint(x / _IN, y / _IN);
	}
	
	void operator /= (FloatPoint _OTHER)
	{ 
		// 0�� ��쵵 ������
		assert(_OTHER.x && _OTHER.y);
		
		x /= _OTHER.x; y /= _OTHER.y;
	}
	
	void operator /= (float _IN)
	{
		// 0�� ��쵵 ������
		assert(_IN);

		x /= _IN; y /= _IN;
	}
};

struct DragAndDrop
{
	POINT m_CLICK;
	POINT m_RELEASE;
};

struct DbgRenderInfo
{
	DEBUG_SHAPE		Type;
	FloatPoint		Position0;
	FloatPoint		Position1;
	FloatPoint		Scale;
	PEN_COLOR		Color;
	float			Duration;	// ǥ�� �ð�
	float			Time;		// ���� �ð�
};

struct KeyInfo
{
	KEY_STATE	STATE;			// ���� ����
	bool		bPrevPressed;	// ���� �����ӿ� ���ȴ���
};

struct CameraEffect
{
	POST_PROCESS	Effect;		// �������� ȿ�� ����	
	float			Time;		// ȿ�� ����ð� ���
	float			Duration;	// ȿ�� �ִ� ���� �ð�
};

struct UnitInfomation
{
	float MaxHP;
	float CurHP;

	float MaxMP;
	float CurMP;

	float Att;
	float Def;
	float Dex;

	float AttRange;
	float DetectRange;

	float Speed;
};

struct Task
{
	TASK_TYPE	Type;
	DWORD_PTR	Param0;
	DWORD_PTR	Param1;
};

struct Tile
{
	int ImageIndex;
};