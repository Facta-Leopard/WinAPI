#include "PreCompile.h"
#include "PortraitMGR.h"

PortraitMGR::PortraitMGR()
	// : m_VECTOR_PAIR_UNITTYPE_PORTRAIT()

	// �ȵǼ� InGameStage�� ������
	//m_VECTOR_PORTRAIT{}
	//, m_UNITNAME(L"Nothing")
{

}

PortraitMGR::~PortraitMGR()
{
	// �ȵǼ� InGameStage�� ������
	//Delete_Vector(m_VECTOR_PORTRAIT);
}

// ����� �׽�Ʈ�ϴ� �κ��̹Ƿ� �ϵ��ڵ���
// �ʿ�� ���ȭ����
void PortraitMGR::Init()
{
	// �ȵǼ� InGameStage�� ������
	// MakePortraitUnit();
}

void PortraitMGR::Render(UNIT_TYPE _UNITTYPE, bool _talk)
{
	// �ȵǼ� InGameStage�� ������
	//if (UNIT_TYPE::ADVISOR == _UNITTYPE)
	//{
	//	if (_talk == false)
	//	{
	//		m_VECTOR_PORTRAIT[1]->FinalTick();
	//	}
	//	else
	//	{
	//		m_VECTOR_PORTRAIT[2]->FinalTick();
	//	}
	//}
	//else if (UNIT_TYPE::MARINE == _UNITTYPE)
	//{
	//	if (_talk == false)
	//	{
	//		m_VECTOR_PORTRAIT[3]->FinalTick();
	//	}
	//	else
	//	{
	//		m_VECTOR_PORTRAIT[4]->FinalTick();
	//	}
	//}
	//else if (UNIT_TYPE::HYDRALISK == _UNITTYPE)
	//{
	//	if (_talk == false)
	//	{
	//		m_VECTOR_PORTRAIT[5]->FinalTick();
	//	}
	//	else
	//	{
	//		m_VECTOR_PORTRAIT[6]->FinalTick();
	//	}
	//}
	//else
	//{
	//	m_VECTOR_PORTRAIT[0]->FinalTick();
	//}
}

// �ȵǼ� InGameStage�� ������
// �׽�Ʈ�� �ڵ�
//void PortraitMGR::MakePortraitUnit()
//{
//	Portrait* tPORTRAIT0 = new Portrait(UNIT_TYPE_TO_STRING(UNIT_TYPE::ETC)
//		, UNIT_TYPE::ETC
//		, PORTRAIT_TYPE::PORTRAITE_IDLE
//		, { 60, 56 });
//	tPORTRAIT0->SetDuration(0.1f);
//	tPORTRAIT0->Init();
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT0);
//
//	Portrait* tPORTRAIT1 = new Portrait(UNIT_TYPE_TO_STRING(UNIT_TYPE::MARINE)
//		, UNIT_TYPE::ETC
//		, PORTRAIT_TYPE::PORTRAITE_IDLE
//		, { 60, 56 });
//	tPORTRAIT1->SetDuration(0.1f);
//	tPORTRAIT1->Init();
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT1);
//
//	Portrait* tPORTRAIT2 = new Portrait(UNIT_TYPE_TO_STRING(UNIT_TYPE::MARINE)
//		, UNIT_TYPE::ETC
//		, PORTRAIT_TYPE::PORTRAITE_TALK
//		, { 60, 56 });
//	tPORTRAIT2->SetDuration(0.1f);
//	tPORTRAIT2->Init();
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT2);
//}





	//for (int i = 1; i < 3; i++)
	//	//for (int i = (int)UNIT_TYPE::ETC; i < (int)UNIT_TYPE::HYDRALISK; i++)
	//{
	//	for (int j = 0; j < 1; j++)
	//	//for (int j = (int)PORTRAIT_TYPE::PORTRAITE_IDLE; j < (int)PORTRAIT_TYPE::PORTRAITE_TALK; j++)
	//	{
	//		Portrait* tPORTRAIT = new Portrait(UNIT_TYPE_TO_STRING((UNIT_TYPE)(i))
	//			, (UNIT_TYPE)(i)
	//			, (PORTRAIT_TYPE)(j)
	//			, { 60, 56 });
	//		tPORTRAIT->Init();
	//		m_VECTOR_PORTRAIT.push_back(tPORTRAIT);
	//	}
	//}

	// �ð��� ��� �ϴ� �ϵ��ڵ���
	// ����, ���ȭ�ؾ� ��..

//	// Advisor
//	Portrait tPORTRAIT0 = Portrait(L"StarInOut"
//		, UNIT_TYPE::ETC
//		// �׽�Ʈ�� IDLE���� 1���� ����
//		, (PORTRAIT_TYPE)(0)
//		// �׽�Ʈ������ {60, 56} �� ����
//		Portrait
//	tPORTRAIT0.SetDuration(0.4f);
//	tPORTRAIT0.Init();
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT0);
//
//	// Marine
//	// �׽�Ʈ�� �ڵ�
//	// ������ ��� ����
//	// �׽�Ʈ������ MARINE �� ����
//		Portrait tPORTRAIT1 = Portrait(L"MARINE_IDLE"
//		, UNIT_TYPE::MARINE
//			// �׽�Ʈ�� IDLE���� 0���� ����
//		, (PORTRAIT_TYPE)(0)
//		// �׽�Ʈ������ {60, 56} �� ����
//		, { 60, 56 });
//
//	// ���ð� ���� ���� �Ҵ� �κ� ������ ��������.. new�� �����ٰ� ���������̴�..
//	// �ڲ� �̰� ��Դ� ��
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT1);
//
//	// Marine
//	Portrait tPORTRAIT2 = Portrait(L"MARINE_TALK"
//		, UNIT_TYPE::MARINE
//		// �׽�Ʈ�� IDLE���� 1���� ����
//		, (PORTRAIT_TYPE)(1)
//		// �׽�Ʈ������ {60, 56} �� ����
//		, { 60, 56 });
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT2);
//
//	// Advisor
//	// �׽�Ʈ�� �ڵ�
//	// ������ ��� ����
//	// �׽�Ʈ������ MARINE �� ����
//	Portrait tPORTRAIT3 = Portrait(L"ADVISOR_IDLE"
//		, UNIT_TYPE::ADVISOR
//		// �׽�Ʈ�� IDLE���� 0���� ����
//		, (PORTRAIT_TYPE)(0)
//		// �׽�Ʈ������ {60, 56} �� ����
//		, { 60, 56 });
//
//	// ���ð� ���� ���� �Ҵ� �κ� ������ ��������.. new�� �����ٰ� ���������̴�..
//	// �ڲ� �̰� ��Դ� ��
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT3);
//
//	// Advisor
//	Portrait tPORTRAIT4 = Portrait(L"ADVISOR_TALK"
//		, UNIT_TYPE::ADVISOR
//		// �׽�Ʈ�� IDLE���� 1���� ����
//		, (PORTRAIT_TYPE)(1)
//		// �׽�Ʈ������ {60, 56} �� ����
//		, { 60, 56 });
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT4);
//
//	// Hydralisk
//// �׽�Ʈ�� �ڵ�
//// ������ ��� ����
//// �׽�Ʈ������ MARINE �� ����
//	Portrait tPORTRAIT5 = Portrait(L"HYDRALISK_IDLE"
//		, UNIT_TYPE::HYDRALISK
//		// �׽�Ʈ�� IDLE���� 0���� ����
//		, (PORTRAIT_TYPE)(0)
//		// �׽�Ʈ������ {60, 56} �� ����
//		, { 60, 56 });
//	
//	// ���ð� ���� ���� �Ҵ� �κ� ������ ��������.. new�� �����ٰ� ���������̴�..
//	// �ڲ� �̰� ��Դ� ��
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT5);
//
//	// Hydralisk
//	Portrait tPORTRAIT6 = Portrait(L"HYDRALISK_TALK"
//		, UNIT_TYPE::HYDRALISK
//		// �׽�Ʈ�� IDLE���� 1���� ����
//		, (PORTRAIT_TYPE)(1)
//		// �׽�Ʈ������ {60, 56} �� ����
//		, { 60, 56 });
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT6);

// �׽�Ʈ�� �ڵ�
//void PortraitMGR::MakeMovingMotionUnit(wstring _UNITNAME, UNIT_TYPE _UNITTYPE, FloatPoint _SCALE)
//{
//	// ���ֺ� ���Ÿ�� ����
//	m_UNITNAME = _UNITNAME;
//	for (int i = MOVINGMOTION_TYPE::IDLE_UP; i < MOVINGMOTION_TYPE::ATTACK_DOWNRIGHT; i++)
//	{
//		MovingMotion tMovingMotion(m_UNITNAME
//			, _UNITTYPE
//			, (MOVINGMOTION_TYPE)(i)
//			, _SCALE);
//
//		// ���ð� ���� ���� �Ҵ� �κ� ������ ��������.. new�� �����ٰ� ���������̴�..
//		// MovingMotion tMovingMotion = new MovingMotion(m_UNITNAME
//		//	, _BROODTYPE
//		//	, _UNITTYPE
//		//	, (MOVINGMOTION_TYPE)(i));
//
//		m_VECTOR_PAIR_UNITTYPE_MOVINGMOTION.push_back(make_pair(_UNITTYPE, tMovingMotion));
//	}
//}

 // �׽�Ʈ�� �ڵ�
//void PortraitMGR::PlayMovingMotion(UNIT_TYPE _UNITTYPE, MOVINGMOTION_TYPE _MOVINGMOTIONTYPE, POINT _POSITION)
//{
//	vector<pair<UNIT_TYPE, MovingMotion>> tVECTOR =	m_VECTOR_PAIR_UNITTYPE_MOVINGMOTION;
//
//	MovingMotion pMovingMotion;
//
//	for (vector<pair<UNIT_TYPE, MovingMotion>>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
//	{
//		if (_UNITTYPE == iter->first)
//		{
//			// �� �ڵ� �ϳ� ������ ��¥..
//			// MovingMotion ��������ڶ� ���Կ����� �����ε����� �� -0-.. ����..
//			pMovingMotion = iter->second;
//			break;
//		}
//	}
//
//	//MovingMotion pMovingMotion = PortraitMGR::GetInstance()->m_VECTOR_PAIR_UNITTYPE_MOVINGMOTION[];
//
//	Texture* pTEXTURE = pMovingMotion.GetTexture();
//	float tDuration = pMovingMotion.GetDuration();
//	float tFPSTime = pMovingMotion.GetFPSTime();
//	int tIndex = pMovingMotion.GetIndex();
//	int tMaxFrame = pMovingMotion.GetMaxFrame();
//	FloatPoint tSCALE = pMovingMotion.GetScale();
//	
//	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
//
//	// �ӽ÷� �׽�Ʈ�ϱ� ���� MARINE�� ũ��(64*64)�� ũ�� 64�� UNIT_RENDER_SIZE �����
//	// ���� ũ�Ⱑ �ٸ� ���ҽ� ���ֻ��� ������ �����ؾ���
//	TransparentBlt(tDC
//		, _POSITION.x - UNIT_RENDER_SIZE * 0.5
//		, _POSITION.y - UNIT_RENDER_SIZE * 0.5
//		, tSCALE.x
//		, tSCALE.y
//		, pTEXTURE->GetDC()
//		, 0, tSCALE.y * tIndex
//		, pTEXTURE->GetWidth()
//		, tSCALE.x
//		, RGB(255, 255, 255));
//}

//private:
//	map<wstring, MovingMotion*>		m_MAP_WSTRING_MOVINGMOTION;
//	wstring							m_UNITNAME;