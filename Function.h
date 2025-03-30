#pragma once

#include "TaskMGR.h"
#include "AssetMGR.h"
#include "Asset.h"

#include "DBGRenderMGR.h"

void CreateObject(class Object* _NEWOBJECT, LAYER_TYPE _LAYER);
void DeleteObject(Object* _DELETEOBJECT);
void ChangeStage(STAGE_TYPE _ANOTHERSTAGE);

bool IsValid(Object*& _OBJECT);

FloatPoint Rotate(FloatPoint _DIRECTION, float _Angle);
bool GetClockWise(FloatPoint _A, FloatPoint _B);

class Asset;
void SaveAssetRef(Asset* _ASSET, FILE* _FILE);
Asset* LoadAssetRef(FILE* _FILE);


void DrawDebugRect(PEN_COLOR _PEN, FloatPoint _POS, FloatPoint _SCALE, float _Duration);
void DrawDebugCircle(PEN_COLOR _PEN, FloatPoint _POS, FloatPoint _SCALE, float _Duration);
void DrawDebugLine(PEN_COLOR _PEN, FloatPoint _START, FloatPoint _End, float _Duration);

float Saturate(float _Ratio);

bool CheckMouseover(FloatPoint _MOUSEPOSITION, FloatPoint _TARGETPOINT, FloatPoint _TARGETSCALE);

bool CheckInsideGetDragAndDropBox(FloatPoint _TARGETPOINT);





template<typename T>
void Delete_Vector(vector<T*>& _VECTOR)
{
	for (size_t i = 0; i < _VECTOR.size(); ++i)
	{
		DELETE(_VECTOR[i]);
	}

	_VECTOR.clear();
}

template<typename T>
void Delete_Vector(vector<T> _VECTOR)
{
	//for (size_t i = 0; i < _VECTOR.size(); ++i)
	//{
	//	delete _VECTOR[i];
	//}

	_VECTOR.clear();
}


template<typename T, int ArraySize>
void Delete_Array(T* (&arr)[ArraySize])
{
	for (int i = 0; i < ArraySize; ++i)
	{
		DELETE(arr[i]);
	}
}

template<typename T1, typename T2>
void Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		delete iter->second;
	}

	_map.clear();
}






const wchar_t* unitTypeToString(UNIT_TYPE x);