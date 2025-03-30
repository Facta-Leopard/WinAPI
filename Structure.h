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
	// 벡터의 길이
	float Length()
	{
		return sqrt((x * x) + (y * y));
	}

	// 정규화
	void Normalize()
	{
		float Len = Length();
		x /= Len;
		y /= Len;
	}

	// 내적
	float DotProduct(const FloatPoint& _OTHER) const
	{
		return x * _OTHER.x + y * _OTHER.y;
	}

	// 외적
	// 값이 양수이면 A가 B를 기준으로 반시계 방향으로 회전하고 있다는 의미
	// 외적 값이 음수이면 A가 B를 기준으로 시계 방향으로 회전하고 있다는 의미
	float CrossProduct(const FloatPoint& _OTHER) const
	{
		return ((x * _OTHER.x) - y * _OTHER.y);
	}


	// 아니 씨발..
	// 깊은 복사까지 설정해야될 지는 생각도 못했는데..
	// 자꾸 이상한데서 버그가 터져서 파고파고보다 여기가 문제였네..

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
		// 0일 경우도 포함함
		assert(_OTHER.x && _OTHER.y);
		
		return FloatPoint(x / _OTHER.x, y / _OTHER.y);
	}
	
	FloatPoint operator / (float _IN) 
	{
		// 0일 경우도 포함함
		assert(_IN);
		
		return FloatPoint(x / _IN, y / _IN);
	}
	
	void operator /= (FloatPoint _OTHER)
	{ 
		// 0일 경우도 포함함
		assert(_OTHER.x && _OTHER.y);
		
		x /= _OTHER.x; y /= _OTHER.y;
	}
	
	void operator /= (float _IN)
	{
		// 0일 경우도 포함함
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
	float			Duration;	// 표시 시간
	float			Time;		// 진행 시간
};

struct KeyInfo
{
	KEY_STATE	STATE;			// 현재 상태
	bool		bPrevPressed;	// 이전 프레임에 눌렸는지
};

struct CameraEffect
{
	POST_PROCESS	Effect;		// 진행중인 효과 종류	
	float			Time;		// 효과 진행시간 계산
	float			Duration;	// 효과 최대 진행 시간
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