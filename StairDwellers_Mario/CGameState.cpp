#include "CGameState.h"

#include "CObjMgr.h"
#include "CInput.h"
#include "CGame.h"
#include "CFactory.h"
#include "Enums.h"
#include "CPlayer.h"
#include "CBackGround.h"
#include "CTile.h"
#include "CTurtle.h"
#include "CUI.h"
#include "CAudioMgr.h"
#include "CStateMgr.h"
#include "CTimeFont.h"
#include "CLevelTransition.h"
#include "CBulletItem.h"
#include "CCoinItem.h"
#include "CCoinScoreFont.h"
#include "Cannon.h"
#include <fstream>
#include <string>


CGameState::CGameState()
{
}


CGameState::~CGameState()
{
}

bool CGameState::Init()
{
	//Create Objects
	CreateObject();

	//Create Map
	CreateMap();

	//Audio
	CAudioMgr::GetInst()->PlayMusic("Game1");
	CGame::GetInst()->m_hp = 3;

	return true;
}

void CGameState::Update(double dDt)
{
	CObjMgr::GetInst()->Update(dDt);

	
	//for (CUI* u : CObjMgr::GetInst()->DeleteObjList)
	if (CGame::GetInst()->m_hp == 2)
	{
		CObjMgr::GetInst()->DeleteObjList(H3);
	}
	else if (CGame::GetInst()->m_hp == 1)
	{
		CObjMgr::GetInst()->DeleteObjList(H2);
	}
	else if (CGame::GetInst()->m_hp == 0)
	{
		CObjMgr::GetInst()->DeleteObjList(H1);
	}

	CState::Update(dDt);
}

void CGameState::Render()
{
	//Clear the screen 
	SDL_SetRenderDrawColor(CGame::GetInst()->GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(CGame::GetInst()->GetRenderer());

	//Render Objects
	CObjMgr::GetInst()->Render(CGame::GetInst()->GetRenderer());

	//Draw screen
	SDL_RenderPresent(CGame::GetInst()->GetRenderer());
}



void CGameState::Shutdown()
{
	//CObjMgr::GetInst()->Shutdown();
	CObjMgr::GetInst()->DeleteObjList(OBJ_BACKGROUND);
	CObjMgr::GetInst()->DeleteObjList(OBJ_GROUNDTILE);
	CObjMgr::GetInst()->DeleteObjList(OBJ_FILLERTILE);
	CObjMgr::GetInst()->DeleteObjList(OBJ_ENEMY);
	CObjMgr::GetInst()->DeleteObjList(OBJ_BULLET);
	CObjMgr::GetInst()->DeleteObjList(OBJ_ITEM);
	CObjMgr::GetInst()->DeleteObjList(OBJ_ETC);

	CAudioMgr::GetInst()->StopMusic();
}


//Create all objects for game, should be called after making ObjMgr
void CGameState::CreateObject()
{
	//Create Background
	CObjMgr::GetInst()->AddObj(CFactory<CBackGround>::CreateObj("BackGround", 
		{ 0, 0, 512, 432 }, { 0, 0, CGame::SCREEN_WIDTH, CGame::SCREEN_HEIGHT }), OBJ_BACKGROUND);

	//Create Player
	//CObjMgr::GetInst()->AddObj(CFactory<CPlayer>::CreateObj(), OBJ_PLAYER);

	//Create Enemy
	//CObjMgr::GetInst()->AddObj(CFactory<CTurtle>::CreateObj(), OBJ_ENEMY);

	
	CObjMgr::GetInst()->AddObj(CFactory<CUI>::CreateObj("Bullets",
		{ 0, 0, 16, 16}, { 455, 15, 30, 30 }), OBJ_UI);

	CObjMgr::GetInst()->AddObj(CFactory<CUI>::CreateObj("UI",
		{ 0, 0, 28, 28 }, { 450, 10, 40, 40 }), OBJ_Wind);

	CObjMgr::GetInst()->AddObj(CFactory<CUI>::CreateObj("UI",
		{ 0, 28, 16, 16 }, { 10, 10, 16, 16 }), H1);

	CObjMgr::GetInst()->AddObj(CFactory<CUI>::CreateObj("UI",
		{ 0, 28, 16, 16 }, { 30, 10, 16, 16 }), H2);

	CObjMgr::GetInst()->AddObj(CFactory<CUI>::CreateObj("UI",
		{ 0, 28, 16, 16 }, { 50, 10, 16, 16 }), H3);


	//Add timer
	CObject* pFont = new CTimeFont("Test", { 0, 0, 0, 255 }, CGame::SCREEN_WIDTH - 300, 20);	CObjMgr::GetInst()->AddObj(pFont, OBJ_FONT);

	//Add Coin Score
	pFont = new CCoinScoreFont("Test", { 255, 255, 255, 255 }, 200, 20);
	CObjMgr::GetInst()->AddObj(pFont, OBJ_FONT);

	//Add instruction
	pFont = new CFont("Press W, A, D to move around", { 0, 0, 0, 255 }, 50, 100, 10);
	CObjMgr::GetInst()->AddObj(pFont, OBJ_FONT);

	pFont = new CFont("Press Space to shoot", { 0, 0, 0, 255 }, 50, 120, 10);
	CObjMgr::GetInst()->AddObj(pFont, OBJ_FONT);

	


	//Add level transition
	//CObjMgr::GetInst()->AddObj(CFactory<CLevelTransition>::CreateObj(700, 260), OBJ_ETC);


	//Add item
	//CObject* pItem = CFactory<CBulletItem>::CreateObj(500, 360);
	//((CBulletItem*)pItem)->SetBulletType(bulletType::FIRE);
	//CObjMgr::GetInst()->AddObj(pItem, OBJ_ITEM);
	//
	//pItem = CFactory<CBulletItem>::CreateObj(550, 360);
	//((CBulletItem*)pItem)->SetBulletType(bulletType::SHRINK);
	//CObjMgr::GetInst()->AddObj(pItem, OBJ_ITEM);
	//
	//for (int i = 0; i < 10; ++i)
	//{
	//	pItem = CFactory<CCoinItem>::CreateObj(600 + i * 20, 345);
	//	CObjMgr::GetInst()->AddObj(pItem, OBJ_ITEM);
	//}
}

//Create Map using txt file
void CGameState::CreateMap()
{
	char tile;

	fstream mapfile("assets/Level1.txt", ios::in);
	//mapfile.open("Level1.txt", ios::in);

	if (!mapfile.is_open())
		return;

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 250; x++)
		{
			mapfile.get(tile);

			CObject* pItem, * enemy, * cannon;
	
		
			if (tile == 'y')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 0, 0), OBJ_GROUNDTILE);
			else if (tile == 'h')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 16, 0), OBJ_GROUNDTILE);
			else if (tile == 'n')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 32, 0), OBJ_GROUNDTILE);
			else if (tile == 'u')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 48, 0), OBJ_GROUNDTILE);
			else if (tile == 'j')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 64, 0), OBJ_GROUNDTILE);
			else if (tile == 'm')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 80, 16), OBJ_GROUNDTILE);
			else if (tile == 'i')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 96, 16), OBJ_GROUNDTILE);
			else if (tile == 'k')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 0, 16), OBJ_GROUNDTILE);
			else if (tile == 'o')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 16, 16), OBJ_FILLERTILE);
			else if (tile == 'l')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 32, 16), OBJ_GROUNDTILE);
			else if (tile == '*')
				cout << ' ';
			else if (tile == 't')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 0, 32), OBJ_GROUNDTILE);
			else if (tile == 'g')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 16, 32), OBJ_GROUNDTILE);
			else if (tile == 'b')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("Tiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 32, 32), OBJ_GROUNDTILE);
			else if (tile == 'P')
			{
				CObject* pPoll = CFactory<CLevelTransition>::CreateObj(x * (TILE_SIZE * 2), y * (TILE_SIZE * 2));
				((CLevelTransition*)pPoll)->SetStateToChange(CStateMgr::STATE_GAME2);
				CObjMgr::GetInst()->AddObj(pPoll, OBJ_ETC);
			}
			else if (tile == '@')
			{
				CObjMgr::GetInst()->AddObj(CFactory<CPlayer>::CreateObj(), OBJ_PLAYER);
				CObjMgr::GetInst()->GetObj(OBJ_PLAYER)->SetDestX(x * TILE_SIZE * 2);
				CObjMgr::GetInst()->GetObj(OBJ_PLAYER)->SetDestY(y*TILE_SIZE * 2);
				CObjMgr::GetInst()->GetObj(OBJ_PLAYER)->SetX(x * TILE_SIZE * 2);
				CObjMgr::GetInst()->GetObj(OBJ_PLAYER)->SetY(y * TILE_SIZE * 2);
			}
			else if (tile == 'p') // Enemy facing Right
			{
				enemy = CFactory<CTurtle>::CreateObj(x * TILE_SIZE * 2, y * TILE_SIZE * 2);
				((CDynamicObject*)enemy)->SetIsFacingRight(true);
				CObjMgr::GetInst()->AddObj(enemy, OBJ_ENEMY);
			}
			else if (tile == 'q') // Enemy facing Left
			{
				enemy = CFactory<CTurtle>::CreateObj(x * TILE_SIZE * 2, y * TILE_SIZE * 2);
				((CDynamicObject*)enemy)->SetIsFacingRight(false);
				CObjMgr::GetInst()->AddObj(enemy, OBJ_ENEMY);
			}
			else if (tile == 'Q') // Cannon
			{
				cannon = CFactory<Cannon>::CreateObj(x* TILE_SIZE * 2, y * TILE_SIZE * 2);
				CObjMgr::GetInst()->AddObj(cannon, OBJ_GROUNDTILE);
			}
			else if (tile == 'c') // Coin
			{
				pItem = CFactory<CCoinItem>::CreateObj(x* TILE_SIZE * 2, y * TILE_SIZE * 2);
				CObjMgr::GetInst()->AddObj(pItem, OBJ_ITEM);
			}
			else if (tile == 'a') // Fire Bullet
			{
				pItem = CFactory<CBulletItem>::CreateObj(x * TILE_SIZE * 2, y * TILE_SIZE * 2);
				((CBulletItem*)pItem)->SetBulletType(bulletType::FIRE);
				CObjMgr::GetInst()->AddObj(pItem, OBJ_ITEM);
			}
			else if (tile == 'z') // Shrink Bullet
			{
				pItem = CFactory<CBulletItem>::CreateObj(x * TILE_SIZE * 2, y * TILE_SIZE * 2);
				((CBulletItem*)pItem)->SetBulletType(bulletType::SHRINK);
				CObjMgr::GetInst()->AddObj(pItem, OBJ_ITEM);
			}
			else if (tile == 'w') // Metal Bullet
			{
				pItem = CFactory<CBulletItem>::CreateObj(x * TILE_SIZE * 2, y * TILE_SIZE * 2);
				((CBulletItem*)pItem)->SetBulletType(bulletType::METAL);
				CObjMgr::GetInst()->AddObj(pItem, OBJ_ITEM);
			}
			else if (tile == 's') // Ghost Bullet
			{
				pItem = CFactory<CBulletItem>::CreateObj(x * TILE_SIZE * 2, y * TILE_SIZE * 2);
				((CBulletItem*)pItem)->SetBulletType(bulletType::GHOST);
				CObjMgr::GetInst()->AddObj(pItem, OBJ_ITEM);
			}
		}
	}
	
	mapfile.close();
}