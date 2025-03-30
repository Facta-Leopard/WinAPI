#include "PreCompile.h"

#include "Object.h"
#include "Asset.h"
#include "AssetMGR.h"

#include "DBGRenderMGR.h"

void CreateObject(Object* _NEWOBJECT, LAYER_TYPE _LAYER)
{
	Task task = { TASK_TYPE::CREATE_OBJECT,  (DWORD_PTR)_NEWOBJECT , (DWORD_PTR)_LAYER };
	TaskMGR::GetInstance()->AddTask(task);
}

void DeleteObject(Object* _DELETEOBJECT)
{
	Task task = {};

	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param0 = (DWORD_PTR)_DELETEOBJECT;

	TaskMGR::GetInstance()->AddTask(task);
}

void ChangeStage(STAGE_TYPE _ANOTHERSTAGE)
{
	Task task = {};

	task.Type = TASK_TYPE::CHANGE_STAGE;
	task.Param0 = (DWORD_PTR)_ANOTHERSTAGE;

	TaskMGR::GetInstance()->AddTask(task);
}

bool IsValid(Object*& _OBJECT)
{
	if (nullptr == _OBJECT)
	{
		return false;
	}
	else if (_OBJECT->IsDead())
	{
		_OBJECT = nullptr;
		return false;
	}

	return true;
}

FloatPoint Rotate(FloatPoint _DIRECTION, float _Angle)
{
	_DIRECTION.Normalize();

	FloatPoint vRotate = FloatPoint(cosf(_Angle) * _DIRECTION.x - sinf(_Angle) * _DIRECTION.y
		, sinf(_Angle) * _DIRECTION.x + cosf(_Angle) * _DIRECTION.y);

	return vRotate;
}

bool GetClockWise(FloatPoint _A, FloatPoint _B)
{
	float F = _A.x * _B.y - _A.y * _B.x;

	if (0.f < F)
		return true;

	return false;
}

void SaveAssetRef(Asset* _ASSET, FILE* _FILE)
{
	// �����Ϸ��� Asset �� nullptr �̸� 0 �ϳ� �����Ѵ�.
	int Asset = !!_ASSET;
	fwrite(&Asset, sizeof(int), 1, _FILE);
	if (!Asset)
		return;

	// Asset �� ������ �����Ѵ�.
	ASSET_TYPE type = _ASSET->GetAssetType();
	fwrite(&type, sizeof(ASSET_TYPE), 1, _FILE);

	// �����Ϸ��� Asset �� Key, Path �� �����´�.
	const wstring& strKey = _ASSET->GetKey();
	const wstring& strPath = _ASSET->GetRelativePath();

	// Asset �� Key, Path ���ڿ��� �����Ѵ�.
	size_t len = strKey.length();
	fwrite(&len, sizeof(size_t), 1, _FILE);
	fwrite(strKey.c_str(), sizeof(wchar_t), strKey.length(), _FILE);

	len = strPath.length();
	fwrite(&len, sizeof(size_t), 1, _FILE);
	fwrite(strPath.c_str(), sizeof(wchar_t), strPath.length(), _FILE);
}

Asset* LoadAssetRef(FILE* _FILE)
{
	// �ҷ������� Asset �� ������ Ȯ��
	int isAsset = 0;
	fread(&isAsset, sizeof(int), 1, _FILE);
	if (!isAsset)
		return nullptr;

	// �ҷ��� Asset �� ������ �о���δ�.
	ASSET_TYPE type;
	fread(&type, sizeof(ASSET_TYPE), 1, _FILE);

	// �ҷ��� Asset �� Ű Path �� �˾Ƴ���.
	wstring strKey, strPath;

	wchar_t buffer[255] = {};

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, _FILE);
	fread(buffer, sizeof(wchar_t), len, _FILE);
	strKey = buffer;

	wmemset(buffer, 0, 255);

	fread(&len, sizeof(size_t), 1, _FILE);
	fread(buffer, sizeof(wchar_t), len, _FILE);
	strPath = buffer;

	Asset* pASSET = nullptr;
	switch (type)
	{
	case ASSET_TYPE::TEXTURE:
		pASSET = (Asset*)(AssetMGR::GetInstance()->LoadTexture(strKey, strPath));
		break;
	case ASSET_TYPE::SOUND:
		//pASSET = AssetMGR::GetInstance()->LoadTexture();
		break;
	case ASSET_TYPE::SPRITE:
		pASSET = (Asset*)(AssetMGR::GetInstance()->LoadSprite(strKey, strPath));
		break;
	case ASSET_TYPE::ANIMATION:
		pASSET = (Asset*)(AssetMGR::GetInstance()->LoadANIMATION(strKey, strPath));
		break;
	}

	return pASSET;
}

void DrawDebugRect(PEN_COLOR _PEN, FloatPoint _POS, FloatPoint _SCALE, float _Duration)
{
	DbgRenderInfo info = {};

	info.Type = DEBUG_SHAPE::RECT;
	info.Color = _PEN;
	info.Position0 = _POS;
	info.Scale = _SCALE;
	info.Duration = _Duration;
	info.Time = 0.f;

	DBGRenderMGR::GetInstance()->AddDbgInfo(info);
}

void DrawDebugCircle(PEN_COLOR _PEN, FloatPoint _POS, FloatPoint _SCALE, float _Duration)
{
	DbgRenderInfo info = {};

	info.Type = DEBUG_SHAPE::CIRCLE;
	info.Color = _PEN;
	info.Position0 = _POS;
	info.Scale = _SCALE;
	info.Duration = _Duration;
	info.Time = 0.f;

	DBGRenderMGR::GetInstance()->AddDbgInfo(info);
}

void DrawDebugLine(PEN_COLOR _PEN, FloatPoint _START, FloatPoint _End, float _Duration)
{
	DbgRenderInfo info = {};

	info.Type = DEBUG_SHAPE::LINE;
	info.Color = _PEN;
	info.Position0 = _START;
	info.Position1 = _End;
	info.Duration = _Duration;
	info.Time = 0.f;

	DBGRenderMGR::GetInstance()->AddDbgInfo(info);
}

// 0.f ~ 1.f ���� ���� �Լ�
float Saturate(float _Ratio)
{
	if (_Ratio < 0.f)
		_Ratio = 0.f;
	else if (1.f < _Ratio)
		_Ratio = 1.f;

	return _Ratio;
}

bool CheckMouseover(FloatPoint _MOUSEPOSITION, FloatPoint _TARGETPOINT, FloatPoint _TARGETSCALE)
{
	// �� ��ǥ�� ���� ��� (�ε��Ҽ��� ����)
	// �ּҰ��� �ִ밪�� ���� ����ؼ� �ڽ� �»������ ���ϴ����� ����
	float xMin = _TARGETPOINT.x - _TARGETSCALE.x * 0.3;
	float xMax = _TARGETPOINT.x + _TARGETSCALE.x * 0.3;
	float yMin = _TARGETPOINT.y - _TARGETSCALE.y * 0.3;
	float yMax = _TARGETPOINT.y + _TARGETSCALE.y * 0.3;

	// ���콺 ��ġ�� ���� �ȿ� �ִ��� Ȯ��
	if (_MOUSEPOSITION.x >= xMin && _MOUSEPOSITION.x <= xMax &&
		_MOUSEPOSITION.y >= yMin && _MOUSEPOSITION.y <= yMax)
	{
		return true;
	}

	return false;
}


bool CheckInsideGetDragAndDropBox(FloatPoint _TARGETPOINT)
{
	// �巡�� �� ��� �ڽ��� ������
	DragAndDrop tBOX = KeyMGR::GetInstance()->GetDragAndDropBox();

	// m_CLICK�� m_RELEASE�� x, y ��ǥ�� ���� ���� ���Ͽ�
	// �ּҰ��� �ִ밪�� ���� ����ؼ� �ڽ� �»������ ���ϴ����� ����
	float x_Minimum, x_Maximum, Y_Minimum, y_Maximum;

	// x ��ǥ ���
	if (tBOX.m_CLICK.x < tBOX.m_RELEASE.x) {
		x_Minimum = tBOX.m_CLICK.x;
		x_Maximum = tBOX.m_RELEASE.x;
	}
	else {
		x_Minimum = tBOX.m_RELEASE.x;
		x_Maximum = tBOX.m_CLICK.x;
	}

	// y ��ǥ ���
	if (tBOX.m_CLICK.y < tBOX.m_RELEASE.y) {
		Y_Minimum = tBOX.m_CLICK.y;
		y_Maximum = tBOX.m_RELEASE.y;
	}
	else {
		Y_Minimum = tBOX.m_RELEASE.y;
		y_Maximum = tBOX.m_CLICK.y;
	}

	// _TARGETPOINT�� �簢�� �ȿ� �ִ��� Ȯ��
	if (_TARGETPOINT.x >= x_Minimum && _TARGETPOINT.x <= x_Maximum &&
		_TARGETPOINT.y >= Y_Minimum && _TARGETPOINT.y <= y_Maximum)
	{
		return true;
	}
	return false;
}


DIRECTION_TYPE CurrentDirectionTypeCheck(float _Direction)
{
	int tDirection = (int)_Direction;
	if (0 > tDirection)
	{
		tDirection += 360;
	}
	tDirection += 22;
	tDirection % 360;
	tDirection / 45;
	switch (tDirection)
	{
	case 1: 
		return UPRIGHT_;
		break;
	case 2:
		return RIGHT_;
		break;
	case 3:
		return DOWNRIGHT_;
		break;
	case 4:
		return DOWN_;
		break;
	case 5:
		return DOWNLEFT_;
		break;
	case 6:
		return LEFT_;
		break;
	case 7:
		return UPLEFT_;
			break;
	// case 0 �̸鼭 8�� �׳� ����Ʈ�� ��
	default:
		return UP_;
		break;
	}
}

MOVINGMOTION_TYPE CurrentMovingMotionTypecCheck(DIRECTION_TYPE _DIRECTION, bool _IsMove, bool _IsAttack)
{
	switch (_DIRECTION)
	{
	case DOWN_:
		if (_IsAttack)
		{
			return MOVINGMOTION_TYPE::ATTACK_DOWN;
		}
		else if (_IsMove)
		{
			return MOVINGMOTION_TYPE::MOVE_DOWN;
		}
		else
		{
			return MOVINGMOTION_TYPE::IDLE_DOWN;
		}
		break;
	case DOWNLEFT_:
		if (_IsAttack)
		{
			return MOVINGMOTION_TYPE::ATTACK_DOWNLEFT;
		}
		else if (_IsMove)
		{
			return MOVINGMOTION_TYPE::MOVE_DOWNLEFT;
		}
		else
		{
			return MOVINGMOTION_TYPE::IDLE_DOWNLEFT;
		}
		break;
	case LEFT_:
		if (_IsAttack)
		{
			return MOVINGMOTION_TYPE::ATTACK_LEFT;
		}
		else if (_IsMove)
		{
			return MOVINGMOTION_TYPE::MOVE_LEFT;
		}
		else
		{
			return MOVINGMOTION_TYPE::IDLE_LEFT;
		}
		break;
	case UPLEFT_:
		if (_IsAttack)
		{
			return MOVINGMOTION_TYPE::ATTACK_UPLEFT;
		}
		else if (_IsMove)
		{
			return MOVINGMOTION_TYPE::MOVE_UPLEFT;
		}
		else
		{
			return MOVINGMOTION_TYPE::IDLE_UPLEFT;
		}
		break;
	case UP_:
		if (_IsAttack)
		{
			return MOVINGMOTION_TYPE::ATTACK_UP;
		}
		else if (_IsMove)
		{
			return MOVINGMOTION_TYPE::MOVE_UP;
		}
		else
		{
			return MOVINGMOTION_TYPE::IDLE_UP;
		}
		break;
	case UPRIGHT_:
		if (_IsAttack)
		{
			return MOVINGMOTION_TYPE::ATTACK_UPRIGHT;
		}
		else if (_IsMove)
		{
			return MOVINGMOTION_TYPE::MOVE_UPRIGHT;
		}
		else
		{
			return MOVINGMOTION_TYPE::IDLE_UPRIGHT;
		}
		break;
	case RIGHT_:
		if (_IsAttack)
		{
			return MOVINGMOTION_TYPE::ATTACK_RIGHT;
		}
		else if (_IsMove)
		{
			return MOVINGMOTION_TYPE::MOVE_RIGHT;
		}
		else
		{
			return MOVINGMOTION_TYPE::IDLE_RIGHT;
		}
		break;
		// ATTACK�� ���¸� �׳� DEFAULT�� ��
	default:
		if (_IsAttack)
		{
			return MOVINGMOTION_TYPE::ATTACK_DOWNRIGHT;
		}
		else if (_IsMove)
		{
			return MOVINGMOTION_TYPE::MOVE_DOWNRIGHT;
		}
		else
		{
			return MOVINGMOTION_TYPE::IDLE_DOWNRIGHT;
		}
		break;
	}
}



const wchar_t* unitTypeToString(UNIT_TYPE x) {
	if (x == UNIT_TYPE::RAYNOR) {
		return L"RAYNOR";
	}
	else if (x == UNIT_TYPE::ADVISOR) {
		return L"Advisor";
	}
	else if (x == UNIT_TYPE::MARINE) {
		return L"Marine";
	}
	else if (x == UNIT_TYPE::MEDIC) {
		return L"MEDIC";
	}
	else if (x == UNIT_TYPE::VULTURE) {
		return L"VULTURE";
	}
	else if (x == UNIT_TYPE::TANK) {
		return L"TANK";
	}
	else if (x == UNIT_TYPE::WRAITH) {
		return L"WRAITH";
	}
	else if (x == UNIT_TYPE::DROPSHIP) {
		return L"DROPSHIP";
	}
	else if (x == UNIT_TYPE::HYDRALISK) {
		return L"Hydralisk";
	}
	else if (x == UNIT_TYPE::SCV) {
		return L"SCV";
	}
	else if (x == UNIT_TYPE::ETC) {
		return L"Etc";
	}
	else {
		return L"Advisor";  // �⺻��
	}
}
