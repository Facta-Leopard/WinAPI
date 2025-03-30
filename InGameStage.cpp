#include "PreCompile.h"
#include "Object.h"
#include "InGameStage.h"
#include "R_Obstruction.h"

#include "Player_Unit.h"
#include "Player1_Building.h"
#include "Player2_Unit.h"

#include "AssetMGR.h"
#include "ColliderMGR.h"
#include "CameraMGR.h"

#include "StarUnit.h"

InGameStage::InGameStage()
    : m_TEXTURE1(AssetMGR::GetInstance()->LoadTexture(L"InGamePanel", L"Texture\\Menu\\InGamePanel\\InGamePanel.BMP"))
    , m_TEXTURE2(AssetMGR::GetInstance()->LoadTexture(L"TestMiniMap", L"Texture\\TestMap\\TestMiniMap.BMP"))
    , m_TEXTURE_COMMAND_ATTACK(AssetMGR::GetInstance()->LoadTexture(L"Attack_Icon", L"Texture\\Unit\\Marine\\Attack_Icon.BMP"))
    , m_TEXTURE_COMMAND_SKILL(AssetMGR::GetInstance()->LoadTexture(L"SteamPack_Icon", L"Texture\\Unit\\Marine\\SteamPack_Icon.BMP"))
    , m_TEXTURE_FRAME(AssetMGR::GetInstance()->LoadTexture(L"WireFrame", L"Texture\\Unit\\Marine\\WireFrame.BMP"))
    , m_TEXTURE_FRAME2(AssetMGR::GetInstance()->LoadTexture(L"WireFrame", L"Texture\\Unit\\Hydralisk\\WireFrame.BMP"))

    , m_TEXTURE_PORTRAIT(AssetMGR::GetInstance()->LoadTexture(L"StaticPortrait", L"Texture\\Portrait\\Advisor\\PORTRAITE_IDLE.BMP"))
    , m_TEXTURE_PORTRAIT2(AssetMGR::GetInstance()->LoadTexture(L"MirinePortrait", L"Texture\\Portrait\\Marine\\PORTRAITE_TALK.BMP"))


    // �ÿ��� �ӽø��

    , m_Time1(0.f)
    , m_Duration1(4.f)
    , m_FPS_Time1(0)
    , m_Index1(0)
    , m_MaxFrame1(45)

    , m_Time2(0.f)
    , m_Duration2(2.f)
    , m_FPS_Time2(0)
    , m_Index2(0)
    , m_MaxFrame2(42)





    , m_Menu(false)

    , m_VECTOR_PORTRAIT({})
    , m_TEMPPORTRAIT()
    , m_PortraitCount(0)

    , m_DRAGANDDROPBOX{{}, {}}
    //, m_MINIMAPTANGLEPOSITION{{},{}}
    
    , m_Player1Selected(false)
    , m_Player2Selected(false)

    , m_Portrait_Talking(false)
    // ���ϴ� �ʻ�ȭ �����ð� ������ ����..
    , m_Portrait_Duration_Talking(0.f)
    , m_Portrait_In_Out(false)
    // �ʻ�ȭ ��ȯ�ð� ������ ����..
    , m_Portrait_Duration_In_Out(0.f)


    , m_IsRelease(false)
{
    //m_MINIMAPTANGLEPOSITION = { {5, (int)(RESOLUTION.y * 0.75) + 5}, { (int)(RESOLUTION.x * 0.1), (int)(RESOLUTION.y * 0.85) + 5 } };
}

InGameStage::~InGameStage()
{
}

void InGameStage::Init()
{
    // ȭ�� �߾����� ȭ�� ����
    CameraMGR::GetInstance()->SetLookAtCentre();

    // ȭ�� ����
    CameraMGR::GetInstance()->SetOffScreenMoveable();


    // Camera ȿ��
    CameraMGR::GetInstance()->PostProcessEffect(FADE_IN, 0.5f);

    // ����� ����
    Sound* pBGM = AssetMGR::GetInstance()->LoadSound(L"TerranBGM", L"Sound\\Terran1.wav");
    if (nullptr != pBGM)
    {
        pBGM->SetVolume(70.f);
        pBGM->PlayToBGM(true);
    }

    Sound* pSound = AssetMGR::GetInstance()->LoadSound(L"NuclearLaunchDetected", L"Sound\\Advisor\\NuclearLaunchDetected.wav");

    if (nullptr != pSound)
    {
        pSound->Play(false);
        pSound->SetVolume(80.f);
    }

    // ȭ�� �ػ� 
    FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();

    // �ʻ�ȭ ��� ����
    MakePortraitUnit();

    // �� �̹��� ����

    Map* pTestMap = new Map(L"TestMap");
    pTestMap->SetPosition(vResolution.x / 2, vResolution.y / 2);
    pTestMap->SetScale(vResolution.x, vResolution.y);
    AddObject(pTestMap, LAYER_TYPE::BACKGROUND);

    Stage::Init();

    // �׽�Ʈ�� �Ʊ� ���� ����
    Player_Unit* tMarine = new Player_Unit(L"MARINE", UNIT_TYPE::MARINE);
    tMarine->SetPosition(180, 240);
    tMarine->SetScale(64.f, 64.f);

    AddObject(tMarine, LAYER_TYPE::PLAYER1);

    // �׽�Ʈ�� �Ʊ� ����2 ����
    Player_Unit* tMarine2 = new Player_Unit(L"MARINE2", UNIT_TYPE::MARINE);
    tMarine2->SetPosition(160, 300);
    tMarine2->SetScale(64.f, 64.f);

    AddObject(tMarine2, LAYER_TYPE::PLAYER1);

    // �����ϰ� ���� 7�� ����

    //for (int i = 0; i < 5; i++)
    //{
    //    int X = rand() % 460;
    //    X += ((rand() % 20) * i + 1);
    //    if (X <= 80)
    //    {
    //        X = 80;
    //    }
    //    int Y = rand() % 30;

    //    Y += ((rand() % 20) * i + 1);
    //    if (Y <= 20)
    //    {
    //        Y = 20;
    //    }

    //    Player2_Unit* tHydralisk = new Player2_Unit(L"MARINE", UNIT_TYPE::MARINE);
    //    tHydralisk->SetPosition(X, Y);
    //    tHydralisk->SetScale(41.f, 54.f);

    //    AddObject(tHydralisk, LAYER_TYPE::PLAYER1);
    //}

    // �����ϰ� ����󸮽�ũ 5 ���� ����

    for (int i = 0; i < 5; i++)
    {
        int X = rand() % 460;
        X += ((rand() % 20)*i + 1 );
        if (X <= 80)
        {
            X = 80;
        }
        int Y = rand() % 30;

        Y += ((rand() % 20)*i + 1);
        if (Y <= 20)
        {
            Y = 20;
        }

        Player2_Unit* tHydralisk = new Player2_Unit(L"HYDRALISK", UNIT_TYPE::HYDRALISK);
        tHydralisk->SetPosition(X, Y);
        tHydralisk->SetScale(41.f, 54.f);

        AddObject(tHydralisk, LAYER_TYPE::PLAYER2);
    }

    // �ÿ��� �ڵ� ���ϰ� �ϵ��ڵ�

    // �����Ӵ� �ɸ��� �ð�
    m_FPS_Time1 = m_Duration1 / m_MaxFrame1;

    // �����Ӵ� �ɸ��� �ð�
    m_FPS_Time2 = m_Duration2 / m_MaxFrame2;



    //// R_Obstruction Object �߰�
    //Object* pR_Obstruction = new R_Obstruction;
    //pR_Obstruction->SetPosition(vResolution.x * 0.5, (vResolution.y * 3.f) / 4.f);
    //AddObject(pR_Obstruction, LAYER_TYPE::TILE);

    //// MapTile Object �߰�
    //Map* pMAPTILE = new Map;
    //pMAPTILE->SetPosition(FloatPoint(0.f, 0.f));
    //wstring FilePath = PathMGR::GetContentPath();
    //pMAPTILE->GeMapTile()->LoadMapTile(FilePath + L"MapTile\\Temp.tile");
    //AddObject(pMAPTILE, LAYER_TYPE::TILE);

    //// MapTile Object �߰�
    //pMAPTILE = new Map;
    //pMAPTILE->SetPosition(FloatPoint(1000.f, 1000.f));
    //pMAPTILE->GeMapTile()->LoadMapTile(FilePath + L"MapTile\\Temp.tile");
    //AddObject(pMAPTILE, LAYER_TYPE::TILE);

    //// �浹 ����
    //ColliderMGR::GetInstance()->CollisionCheckClear();
    //ColliderMGR::GetInstance()->CollisionCheck(LAYER_TYPE::PLAYER1, LAYER_TYPE::PLAYER2);
    //ColliderMGR::GetInstance()->CollisionCheck(LAYER_TYPE::PLAYER1_MISSILE, LAYER_TYPE::PLAYER2);
    //ColliderMGR::GetInstance()->CollisionCheck(LAYER_TYPE::PLAYER2_MISSILE, LAYER_TYPE::PLAYER1);
    //ColliderMGR::GetInstance()->CollisionCheck(LAYER_TYPE::PLAYER1, LAYER_TYPE::TILE);
    //ColliderMGR::GetInstance()->CollisionCheck(LAYER_TYPE::PLAYER2, LAYER_TYPE::TILE);
}

void InGameStage::DeInit()
{
    DeleteAllObject();
}

void InGameStage::Tick()
{
    KeyCheck();
    Stage::Tick();
    DragAndDropCheck();

    CheckTheEnd();


    // �ÿ��� �ڵ�
    // �ӽ��ڵ�

    if (KEY_TAP(B))
    {
        Player_Unit* tMarine = new Player_Unit(L"MARINE", UNIT_TYPE::MARINE);
        tMarine->SetPosition(180, 240);
        tMarine->SetScale(64.f, 64.f);

        AddObject(tMarine, LAYER_TYPE::PLAYER1);
    }

}

void InGameStage::Render()
{
    HWND tHWND = GameEngine::GetInstance()->GetMainWndHwnd();
    HDC tDC = GameEngine::GetInstance()->GetMemoryDC();

    //// ���ڰ��� ǥ�� �׸���
    //RenderUnitText();

    // ���ֵ� �׸���
    Stage::Render();

    RenderDragAndDrop();

    // �г� �̹����� ����
    TransparentBlt(tDC
        , 0
        , 0
        , RESOLUTION.x
        , RESOLUTION.y
        , m_TEXTURE1->GetDC()
        , 0
        , 0
        , RESOLUTION.x
        , RESOLUTION.y
        , RGB(0, 0, 0));

    RenderButton();

    RenderMiniMap();

    // ���ο�� ������.. ����..
    // ����ü �̿��ؼ� ����..

    HFONT hFont = CreateFont(
        40,        
        0,           
        0,        
        0,        
        FW_NORMAL,    
        FALSE,       
        FALSE,        
        FALSE,         
        ANSI_CHARSET,  
        OUT_DEFAULT_PRECIS, 
        CLIP_DEFAULT_PRECIS, 
        DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_SWISS, 
        L"Arial"       
    );



    HGDIOBJ thgdi = SelectObject(tDC, hFont);

    vector<Object*> tObject = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);

    if (0 != tObject.size())
    {
        for (vector<Object*>::iterator iter = tObject.begin() ; iter != tObject.end(); iter++)
        {
            // �������� �θ� Ŭ������ �����ϴٰ� ��� �κ�, ���θ�� �غ�����
            // �̷���� �ڽ�Ŭ�������� ������ �κ� �� ���� Ȯ���� -0-
            Player_Unit* tPLAYERUNIT = dynamic_cast<Player_Unit*>(*iter);

                if (tPLAYERUNIT->m_IsSelected)
                {
                    int HP = dynamic_cast<Player_Unit*>(tPLAYERUNIT)->m_IsHitPoint;
                    int MAXHP = dynamic_cast<Player_Unit*>(tPLAYERUNIT)->m_MaxHitPoint;

                    wstring twstring = std::to_wstring(HP) + L" / " + std::to_wstring(MAXHP);

                    if (100 <= HP)
                    {
                        SetTextColor(tDC, RGB(50, 250, 50));
                        SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
                        TextOut(tDC, 230, 410, twstring.c_str(), 9);
                    }
                    else if (40 <= HP)
                    {
                        SetTextColor(tDC, RGB(250, 250, 50));
                        SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
                        TextOut(tDC, 230, 410, twstring.c_str(), 9);
                    }
                    else
                    {
                        SetTextColor(tDC, RGB(250, 50, 50));
                        SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
                        TextOut(tDC, 230, 410, twstring.c_str(), 9);
                    }

                    
                    // �ϵ��ڵ��ϱ� ������.. 
                    // �ð��� ����..

                    TransparentBlt(
                        tDC,                   
                        170, 400,              
                        40, 64,               
                        m_TEXTURE_FRAME->GetDC()
                        , 0, 0,                
                        40, 64,               
                        RGB(255, 255, 255));

                    break;
                }
        }

    }

    SelectObject(tDC, thgdi);

    // �̷� ����� ó������.. �����Լ��� ���ӽ����̽��� �����ؼ� ::�� ���ٴ�..;;
    ::DeleteObject(hFont);
    ReleaseDC(tHWND, tDC);  // HDC ��� �� ����


    PortraitCheck();
    RenderPortrait();

}

void InGameStage::KeyCheck()
{
    if (!m_Menu && KEY_TAP(KEY::ESC))
    {
        // �޴��� �ε��ϰ� �����쿡 ����
        HMENU hMenu = LoadMenu(GameEngine::GetInstance()->GetHandleInstance(), MAKEINTRESOURCEW(IDC_WINAPI));
        SetMenu(GameEngine::GetInstance()->GetMainWndHwnd(), hMenu);
        m_Menu = true;
        DrawMenuBar(GameEngine::GetInstance()->GetMainWndHwnd());

        TimeMGR::GetInstance()->SetOnTimeStop();

        GameEngine::GetInstance()->ChangeWindowSize(RESOLUTION);
    }
    else if (m_Menu && KEY_TAP(KEY::ESC))
    {
        // �޴��� ����
        SetMenu(GameEngine::GetInstance()->GetMainWndHwnd(), nullptr);
        m_Menu = false;
        DrawMenuBar(GameEngine::GetInstance()->GetMainWndHwnd());

        TimeMGR::GetInstance()->SetOffTimeStop();

        GameEngine::GetInstance()->ChangeWindowSize(RESOLUTION);
    }


}

// �巡�׾ص�� �׸� ��ǥ���� �Լ�
// ���⿡ ������Ʈ ���õǴ� bool�� �� ��Ŀ���� ���� ���� ���뿹��
// bool�� �Ϸ� �� ��Ŀ���� �Ϸ�
// ���ð��� �׷츸��� �ʿ�
void InGameStage::DragAndDropCheck()
{
    if (KEY_TAP(LBTN))
    {
        m_DRAGANDDROPBOX.m_CLICK.x = 0;
        m_DRAGANDDROPBOX.m_CLICK.y = 0;
        m_DRAGANDDROPBOX.m_CLICK.x = (LONG)(KeyMGR::GetInstance()->GetMousePos().x);
        m_DRAGANDDROPBOX.m_CLICK.y = (LONG)(KeyMGR::GetInstance()->GetMousePos().y);
    }
    else if (KEY_PRESSED(LBTN))
    {
        m_DRAGANDDROPBOX.m_RELEASE.x = 0;
        m_DRAGANDDROPBOX.m_RELEASE.y = 0;
        m_DRAGANDDROPBOX.m_RELEASE.x = (LONG)(KeyMGR::GetInstance()->GetMousePos().x);
        m_DRAGANDDROPBOX.m_RELEASE.y = (LONG)(KeyMGR::GetInstance()->GetMousePos().y);
    }
    else if (KEY_TAP(RBTN))
    {
        m_DRAGANDDROPBOX.m_CLICK.x = 0;
        m_DRAGANDDROPBOX.m_CLICK.y = 0;
        m_DRAGANDDROPBOX.m_CLICK.x = (LONG)(KeyMGR::GetInstance()->GetMousePos().x);
        m_DRAGANDDROPBOX.m_CLICK.y = (LONG)(KeyMGR::GetInstance()->GetMousePos().y);
    }
    else if (KEY_PRESSED(RBTN))
    {
        m_DRAGANDDROPBOX.m_RELEASE.x = 0;
        m_DRAGANDDROPBOX.m_RELEASE.y = 0;
        m_DRAGANDDROPBOX.m_RELEASE.x = (LONG)(KeyMGR::GetInstance()->GetMousePos().x);
        m_DRAGANDDROPBOX.m_RELEASE.y = (LONG)(KeyMGR::GetInstance()->GetMousePos().y);
    }
    else if (KEY_NONE(LBTN) || KEY_NONE(RBTN))
    {
        m_DRAGANDDROPBOX.m_CLICK.x = 0;
        m_DRAGANDDROPBOX.m_CLICK.y = 0;
        m_DRAGANDDROPBOX.m_RELEASE.x = 0;
        m_DRAGANDDROPBOX.m_RELEASE.y = 0;
    }
    // �巡�׾� ��� �ڽ��� Ű �Ŵ����� �� �ű�
    KeyMGR::GetInstance()->SetDragAndDropBox(m_DRAGANDDROPBOX);
}

// �巡�׾ص�� �׸�׸��� �Լ�
void InGameStage::RenderDragAndDrop()
{
    if (KEY_PRESSED(LBTN) || KEY_PRESSED(RBTN))
    {
        HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
        SELECT_PEN(PEN_COLOR::GREEN);
        SELECT_BRUSH(BRUSH_COLOR::HOLLOW);
        Rectangle(tDC
            , (m_DRAGANDDROPBOX.m_CLICK.x)
            , (m_DRAGANDDROPBOX.m_CLICK.y)
            , (m_DRAGANDDROPBOX.m_RELEASE.x)
            , (m_DRAGANDDROPBOX.m_RELEASE.y));
    }
}

void InGameStage::RenderMiniMap()
{
    HDC tDC = GameEngine::GetInstance()->GetMemoryDC();

    // �̴ϸ� ������ġ ����
    FloatPoint MINIMAPLEFTTOP = { 5.f, (float)(RESOLUTION.y * 0.75) + 5.f };

    // �̴ϸ�
    BitBlt(tDC
        , (int)MINIMAPLEFTTOP.x
        , (int)MINIMAPLEFTTOP.y
        , m_TEXTURE2->GetWidth()
        , m_TEXTURE2->GetHeight()
        , m_TEXTURE2->GetDC()
        , 0, 0
        , SRCCOPY);

    // �̴ϸ� ���� ������Ʈ ��ġ ǥ��
    vector<Object*> tVECTOR2 = GetObjects(LAYER_TYPE::PLAYER2);
    if (0 != tVECTOR2.size())
    {
        for (vector<Object*>::iterator iter = tVECTOR2.begin(); iter != tVECTOR2.end(); iter++)
        {
            FloatPoint* tFLOATPOINT = new FloatPoint((*iter)->GetPosition());

            FloatPoint tSCALE = (*iter)->GetScale();

            // ��ǥ�� ����
            tFLOATPOINT->x += (float)(RESOLUTION.x * 0.5);
            tFLOATPOINT->y += (float)(RESOLUTION.y * 0.5);

            // �̴ϸ� ǥ�õ������� ��ǥ ũ�� ���� ���
            *tFLOATPOINT *= 0.1;

            // �̴ϸ� �������� ��ǥ�̵�
            *tFLOATPOINT += MINIMAPLEFTTOP;

            tSCALE *= 0.1;

            // ���� �ʹ� �۾Ƽ� ���� �׸�� ��ȯ
            SELECT_PEN(PEN_COLOR::RED);
            SELECT_BRUSH(BRUSH_COLOR::RED);
            Rectangle(tDC, (int)tFLOATPOINT->x - (int)tSCALE.x * 0.3
                , (int)tFLOATPOINT->y + (int)tSCALE.y * 0.3
                , (int)tFLOATPOINT->x + (int)tSCALE.x * 0.3
                , (int)tFLOATPOINT->y - (int)tSCALE.y * 0.3);
        }
    }

    // �̴ϸ� �Ʊ� ������Ʈ ��ġ ǥ��
    vector<Object*> tVECTOR = GetObjects(LAYER_TYPE::PLAYER1);
    if (0 != tVECTOR.size())
    {
        for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
        {
            FloatPoint tFLOATPOINT = (*iter)->GetPosition();
            FloatPoint tSCALE = (*iter)->GetScale();

            // ��ǥ�� ����
            // �� �ػ� ���ݸ�ŭ ������ ������..?
            tFLOATPOINT.x += (float)(RESOLUTION.x * 0.5);
            tFLOATPOINT.y += (float)(RESOLUTION.y * 0.5);

            // �̴ϸ� ǥ�õ������� ��ǥ ũ�� ���� ���
            tFLOATPOINT *= 0.1;

            // �̴ϸ� �������� ��ǥ�̵�
            tFLOATPOINT += MINIMAPLEFTTOP;

            tSCALE *= 0.1;

            // ���� �ʹ� �۾Ƽ� ���� �׸�� ��ȯ
            SELECT_PEN(PEN_COLOR::GREEN);
            SELECT_BRUSH(BRUSH_COLOR::GREEN);
            Rectangle(tDC, (int)tFLOATPOINT.x - (int)tSCALE.x * 0.3
                , (int)tFLOATPOINT.y + (int)tSCALE.y * 0.3
                , (int)tFLOATPOINT.x + (int)tSCALE.x * 0.3
                , (int)tFLOATPOINT.y - (int)tSCALE.y * 0.3);

            // �����
            //SetPixel(tDC, (int)tFLOATPOINT.x, (int)tFLOATPOINT.y, RGB(100, 255, 100));

        }
    }



    // �̴ϸ� ȭ��ǥ�� �׸��� �Լ�
    CameraMGR::GetInstance()->MiniMapRender();
}


// ���� ������ ���� �ذ��� ���� �ٸ� ����� ���ڴ�..
// �ÿ��� ��ð� �� ����
void InGameStage::RenderPortrait()
{

    // �� �ڵ尡 �����ΰ���..
    // �ϴ�, �ÿ��� ���ϴ� �ּ�ó����
    //vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);
    //if (0 != tVECTOR.size())
    //{
    //    for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
    //    {
    //        Player_Unit* tPLAYERUNIT = dynamic_cast<Player_Unit*>(*iter);
    //        if (tPLAYERUNIT->m_IsSelected)
    //        {
    //            m_TEMPPORTRAIT.FinalTick();
    //            return;
    //        }
    //    }
    //}
    //m_VECTOR_PORTRAIT[0]->FinalTick();

    HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
    FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();

    // �г� �� ��ġ�� ��ƾߵ�..
    FloatPoint tPOS = { vResolution.x * 0.70 - 5, vResolution.y * 0.9 + 5 };
    FloatPoint SCALE = { 60.f, 56.f };


    // �ÿ��� �ڵ�
    vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);
    if (0 != tVECTOR.size())
    {
        for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
        {
            Player_Unit* tPLAYERUNIT = dynamic_cast<Player_Unit*>(*iter);
            if (tPLAYERUNIT->m_IsSelected)
            {
                BitBlt(tDC
                    , (int)tPOS.x - (int)(SCALE.x * 0.5)
                    , (int)tPOS.y - (int)(SCALE.y * 0.5)
                    , (int)m_TEXTURE_PORTRAIT2->GetWidth()
                    , (int)SCALE.y
                    , m_TEXTURE_PORTRAIT2->GetDC()
                    , 0, (SCALE.y * m_Index1)
                    , SRCCOPY);
                return;
            }
        }
    }
    BitBlt(tDC
        , (int)tPOS.x - (int)(SCALE.x * 0.5)
        , (int)tPOS.y - (int)(SCALE.y * 0.5)
        , (int)m_TEXTURE_PORTRAIT->GetWidth()
        , (int)SCALE.y
        , m_TEXTURE_PORTRAIT->GetDC()
        , 0, (SCALE.y * m_Index2)
        , SRCCOPY);

}

// �� ¥����..
// �ٸ� ������� �ҷ�
void InGameStage::PortraitCheck()
{
    // �ÿ��� �ӽ��ڵ�
    m_Time1 += DELTATIME;
    if (m_MaxFrame1 < m_Index1)
    {
        m_Index1 = 0;
    }

    if (m_FPS_Time1 < m_Time1)
    {
        m_Time1 -= m_FPS_Time1;
        m_Index1++;
    }

    m_Time2 += DELTATIME;
    if (m_MaxFrame2 < m_Index2)
    {
        m_Index2 = 0;
    }

    if (m_FPS_Time2 < m_Time2)
    {
        m_Time2 -= m_FPS_Time2;
        m_Index2++;
    }



}
//{
//    // ������ ǥ��
//    if (m_Portrait_In_Out)
//    {
//        m_PortraitCount = 0;
//        m_Portrait_Duration_In_Out += DELTATIME;
//    }
//    if (0.3f <= m_Portrait_Duration_In_Out)
//    {
//        {
//            m_PortraitCount = 1;
//            m_Portrait_Duration_In_Out = 0.f;
//            m_Portrait_In_Out = false;
//        }
//    }
//
//    // ���ϴ� ����
//    if (m_Portrait_Talking)
//    {
//        m_Portrait_Duration_Talking += DELTATIME;
//    }
//
//    if (1.5f <= m_Portrait_Duration_Talking)
//    {
//        m_Portrait_Duration_Talking = 0.f;
//        m_Portrait_Talking = false;
//    }
//
//    // ���°� ���� ���� ����
//    if (!m_Portrait_In_Out && m_Portrait_Talking)
//    {
//        if (m_Player2Selected)
//        {
//            m_PortraitCount = 6;
//            m_Player1Selected = false;
//            m_Portrait_In_Out = true;
//        }
//        else if (m_Player1Selected)
//        {
//            m_PortraitCount = 4;
//            m_Player2Selected = false;
//            m_Portrait_In_Out = true;
//        }
//    }
//    else if (!m_Portrait_In_Out && !m_Portrait_Talking)
//    {
//        if (m_Player2Selected)
//        {
//            m_PortraitCount = 5;
//            m_Player1Selected = false;
//            m_Portrait_In_Out = true;
//        }
//        else if (m_Player1Selected)
//        {
//            m_PortraitCount = 3;
//            m_Player2Selected = false;
//            m_Portrait_In_Out = true;
//        }
//    }


    //// ������ǥ��
    //if (m_Portrait_In_Out)
    //{
    //    m_PortraitCount = 0;
    //    m_Portrait_Duration_In_Out += DELTATIME;
    //}
    //if (m_Portrait_In_Out && (0.1f < m_Portrait_Duration_In_Out))
    //{
    //    m_PortraitCount = 1;
    //    m_Portrait_Duration_In_Out = 0.f;
    //    m_Portrait_In_Out = false;
    //}
    //// ���ϴ� ����
    //if (m_Portrait_Talking)
    //{
    //    m_Portrait_Duration_Talking += DELTATIME;
    //}
    //if (m_Portrait_Talking && 1.5f < m_Portrait_Duration_Talking)
    //{
    //    m_Portrait_Duration_Talking = 0.f;
    //    m_Portrait_Talking = false;
    //}
    //if (!m_Portrait_In_Out && m_Portrait_Talking)
    //{
    //    if (m_Player2Selected)
    //    {
    //        m_PortraitCount = 6;
    //        m_Player1Selected = false;
    //        m_Portrait_In_Out = true;
    //    }
    //    else if (m_Player1Selected)
    //    {
    //        m_PortraitCount = 4;
    //        m_Player2Selected = false;
    //        m_Portrait_In_Out = true;
    //    }
    //}
    //else if (!m_Portrait_In_Out && !m_Portrait_Talking)
    //{
    //    if (m_Player2Selected)
    //    {
    //        m_PortraitCount = 5;
    //        m_Player1Selected = false;
    //        m_Portrait_In_Out = true;
    //    }
    //    else if (m_Player1Selected)
    //    {
    //        m_PortraitCount = 3;
    //        m_Player2Selected = false;
    //        m_Portrait_In_Out = true;
    // 

void InGameStage::RenderButton()
{
    HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
    if (m_Player1Selected)

        // ���� �޴�
        TransparentBlt(tDC
            , 615 - (m_TEXTURE_COMMAND_ATTACK->GetWidth() * 0.5)
            , 374 - (m_TEXTURE_COMMAND_ATTACK->GetHeight() * 0.5)
            , m_TEXTURE_COMMAND_ATTACK->GetWidth()
            , m_TEXTURE_COMMAND_ATTACK->GetHeight()
            , m_TEXTURE_COMMAND_ATTACK->GetDC()
            , 0
            , 0
            , m_TEXTURE_COMMAND_ATTACK->GetWidth()
            , m_TEXTURE_COMMAND_ATTACK->GetHeight()
            , RGB(0, 0, 0));


        // ��ų �κ�
        TransparentBlt(tDC
            , 523 - (m_TEXTURE_COMMAND_SKILL->GetWidth() * 0.5)
            , 453 - (m_TEXTURE_COMMAND_SKILL->GetHeight() * 0.5)
            , m_TEXTURE_COMMAND_SKILL->GetWidth()
            , m_TEXTURE_COMMAND_SKILL->GetHeight()
            , m_TEXTURE_COMMAND_SKILL->GetDC()
            , 0
            , 0
            , m_TEXTURE_COMMAND_SKILL->GetWidth()
            , m_TEXTURE_COMMAND_SKILL->GetHeight()
            , RGB(0, 0, 0));
    
}

void InGameStage::RenderUnitText()
{
    vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);

    for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
    {
        Player_Unit* tPLAYER1 = dynamic_cast<Player_Unit*>(*iter);
        tPLAYER1->TextRender();
    }
    tVECTOR.clear();

    vector<Object*> tVECTOR2 = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);
    for (vector<Object*>::iterator iter = tVECTOR2.begin(); iter != tVECTOR2.end(); iter++)
    {
        Player2_Unit* tPLAYER2 = dynamic_cast<Player2_Unit*>(*iter);
        tPLAYER2->TextRender();
    }
    tVECTOR2.clear();
}

void InGameStage::CheckTheEnd()
{
    vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);

    vector<Object*> tVECTOR2 = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);

    if (0 == tVECTOR.size())
    {
        StageMGR::GetInstance()->ChangeStage(STAGE_TYPE::DEFEAT);
    }
    else if (0 == tVECTOR2.size())
    {
        StageMGR::GetInstance()->ChangeStage(STAGE_TYPE::VICTORY);
    }

}

// �ƴ� �ù�.. ���� ������..!!
// ��ĥ ��, ������ ���� �ڵ絥 ��!! ���� �Ⱥ��̳İ�!!
void InGameStage::MakePortraitUnit()
{
    Portrait* tPortrait = new Portrait(L"Etc"
        , UNIT_TYPE::ETC
        , PORTRAIT_TYPE::PORTRAITE_IDLE
        , { 60, 56 });
    tPortrait->SetDuration(0.2f);

    m_VECTOR_PORTRAIT.push_back(tPortrait);

    for (int i = (int)UNIT_TYPE::ADVISOR; i <= (int)UNIT_TYPE::HYDRALISK; i++)
    {
        for (int j = (int)PORTRAIT_TYPE::PORTRAITE_IDLE; j <= (int)PORTRAIT_TYPE::PORTRAITE_TALK; j++)
        {
            Portrait* tPortrait2 = new Portrait((wstring)(UNIT_TYPE_TO_STRING((UNIT_TYPE)(i)) + std::to_wstring(j))
                , UNIT_TYPE(i)
                , (PORTRAIT_TYPE)(j)
                , { 60, 56 });

            m_VECTOR_PORTRAIT.push_back(tPortrait2);
        }
    }


    // �ÿ��� ���� ��¿ �� ����..
    // �ϵ��ڵ��ؼ� �� ����� �����..
    m_TEMPPORTRAIT = Portrait(L"Marineport"
        , UNIT_TYPE::MARINE
        , PORTRAIT_TYPE::PORTRAITE_TALK
        , { 60, 56 });


}

void InGameStage::SetOnDebugging()
{
    vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);

    for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
    {
        Player_Unit* tUNIT = dynamic_cast<Player_Unit*>((*iter));
        tUNIT->SetOnDebugging();
    }

    vector<Object*> tVECTOR2 = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);

    for (vector<Object*>::iterator iter = tVECTOR2.begin(); iter != tVECTOR2.end(); iter++)
    {
        Player_Unit* tUNIT = dynamic_cast<Player_Unit*>((*iter));
        tUNIT->SetOffDebugging();
    }

}

void InGameStage::SetOffDebugging()
{
    vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);

    for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
    {
        Player_Unit* tUNIT = dynamic_cast<Player_Unit*>((*iter));
        tUNIT->SetOffDebugging();
    }

    vector<Object*> tVECTOR2 = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);

    for (vector<Object*>::iterator iter = tVECTOR2.begin(); iter != tVECTOR2.end(); iter++)
    {
        Player_Unit* tUNIT = dynamic_cast<Player_Unit*>((*iter));
        tUNIT->SetOffDebugging();
    }

}
