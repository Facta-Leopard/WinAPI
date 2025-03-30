#include "PreCompile.h"
#include "PortraitMGR.h"

PortraitMGR::PortraitMGR()
	// : m_VECTOR_PAIR_UNITTYPE_PORTRAIT()

	// 안되서 InGameStage에 구현중
	//m_VECTOR_PORTRAIT{}
	//, m_UNITNAME(L"Nothing")
{

}

PortraitMGR::~PortraitMGR()
{
	// 안되서 InGameStage에 구현중
	//Delete_Vector(m_VECTOR_PORTRAIT);
}

// 여기는 테스트하는 부분이므로 하드코딩함
// 필요시 모듈화예정
void PortraitMGR::Init()
{
	// 안되서 InGameStage에 구현중
	// MakePortraitUnit();
}

void PortraitMGR::Render(UNIT_TYPE _UNITTYPE, bool _talk)
{
	// 안되서 InGameStage에 구현중
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

// 안되서 InGameStage에 구현중
// 테스트용 코드
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

	// 시간이 없어서 일단 하드코딩함
	// 향후, 모듈화해야 함..

//	// Advisor
//	Portrait tPORTRAIT0 = Portrait(L"StarInOut"
//		, UNIT_TYPE::ETC
//		// 테스트용 IDLE값을 1으로 설정
//		, (PORTRAIT_TYPE)(0)
//		// 테스트용으로 {60, 56} 값 삽임
//		Portrait
//	tPORTRAIT0.SetDuration(0.4f);
//	tPORTRAIT0.Init();
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT0);
//
//	// Marine
//	// 테스트용 코드
//	// 마린을 집어서 설정
//	// 테스트용으로 MARINE 값 삽입
//		Portrait tPORTRAIT1 = Portrait(L"MARINE_IDLE"
//		, UNIT_TYPE::MARINE
//			// 테스트용 IDLE값을 0으로 설정
//		, (PORTRAIT_TYPE)(0)
//		// 테스트용으로 {60, 56} 값 삽임
//		, { 60, 56 });
//
//	// 스택과 힙의 영역 할당 부분 문제를 생각하자.. new는 힙에다가 영역설정이다..
//	// 자꾸 이거 까먹는 듯
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT1);
//
//	// Marine
//	Portrait tPORTRAIT2 = Portrait(L"MARINE_TALK"
//		, UNIT_TYPE::MARINE
//		// 테스트용 IDLE값을 1으로 설정
//		, (PORTRAIT_TYPE)(1)
//		// 테스트용으로 {60, 56} 값 삽임
//		, { 60, 56 });
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT2);
//
//	// Advisor
//	// 테스트용 코드
//	// 마린을 집어서 설정
//	// 테스트용으로 MARINE 값 삽입
//	Portrait tPORTRAIT3 = Portrait(L"ADVISOR_IDLE"
//		, UNIT_TYPE::ADVISOR
//		// 테스트용 IDLE값을 0으로 설정
//		, (PORTRAIT_TYPE)(0)
//		// 테스트용으로 {60, 56} 값 삽임
//		, { 60, 56 });
//
//	// 스택과 힙의 영역 할당 부분 문제를 생각하자.. new는 힙에다가 영역설정이다..
//	// 자꾸 이거 까먹는 듯
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT3);
//
//	// Advisor
//	Portrait tPORTRAIT4 = Portrait(L"ADVISOR_TALK"
//		, UNIT_TYPE::ADVISOR
//		// 테스트용 IDLE값을 1으로 설정
//		, (PORTRAIT_TYPE)(1)
//		// 테스트용으로 {60, 56} 값 삽임
//		, { 60, 56 });
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT4);
//
//	// Hydralisk
//// 테스트용 코드
//// 마린을 집어서 설정
//// 테스트용으로 MARINE 값 삽입
//	Portrait tPORTRAIT5 = Portrait(L"HYDRALISK_IDLE"
//		, UNIT_TYPE::HYDRALISK
//		// 테스트용 IDLE값을 0으로 설정
//		, (PORTRAIT_TYPE)(0)
//		// 테스트용으로 {60, 56} 값 삽임
//		, { 60, 56 });
//	
//	// 스택과 힙의 영역 할당 부분 문제를 생각하자.. new는 힙에다가 영역설정이다..
//	// 자꾸 이거 까먹는 듯
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT5);
//
//	// Hydralisk
//	Portrait tPORTRAIT6 = Portrait(L"HYDRALISK_TALK"
//		, UNIT_TYPE::HYDRALISK
//		// 테스트용 IDLE값을 1으로 설정
//		, (PORTRAIT_TYPE)(1)
//		// 테스트용으로 {60, 56} 값 삽임
//		, { 60, 56 });
//
//	m_VECTOR_PORTRAIT.push_back(tPORTRAIT6);

// 테스트용 코드
//void PortraitMGR::MakeMovingMotionUnit(wstring _UNITNAME, UNIT_TYPE _UNITTYPE, FloatPoint _SCALE)
//{
//	// 유닛별 모션타입 생성
//	m_UNITNAME = _UNITNAME;
//	for (int i = MOVINGMOTION_TYPE::IDLE_UP; i < MOVINGMOTION_TYPE::ATTACK_DOWNRIGHT; i++)
//	{
//		MovingMotion tMovingMotion(m_UNITNAME
//			, _UNITTYPE
//			, (MOVINGMOTION_TYPE)(i)
//			, _SCALE);
//
//		// 스택과 힙의 영역 할당 부분 문제를 생각하자.. new는 힙에다가 영역설정이다..
//		// MovingMotion tMovingMotion = new MovingMotion(m_UNITNAME
//		//	, _BROODTYPE
//		//	, _UNITTYPE
//		//	, (MOVINGMOTION_TYPE)(i));
//
//		m_VECTOR_PAIR_UNITTYPE_MOVINGMOTION.push_back(make_pair(_UNITTYPE, tMovingMotion));
//	}
//}

 // 테스트용 코드
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
//			// 이 코드 하나 쓰려고 진짜..
//			// MovingMotion 복사생성자랑 대입연산자 오버로딩까지 함 -0-.. 망할..
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
//	// 임시로 테스트하기 위해 MARINE의 크기(64*64)인 크기 64의 UNIT_RENDER_SIZE 사용중
//	// 향후 크기가 다른 리소스 유닛사용시 변수로 변경해야함
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