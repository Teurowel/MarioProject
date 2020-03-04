#include "CGameState3.h"

#include "CObjMgr.h"
#include "CInput.h"
#include "CGame.h"
#include "CFactory.h"
#include "Enums.h"
#include "CBackGround.h"
#include "CTile.h"
#include "CTurtle.h"
#include "CAudioMgr.h"
#include "CGameState.h"
#include "CStateMgr.h"
#include "CUI.h"
#include "CLevelTransition.h"
#include "CCoinItem.h"
#include "Cannon.h"
#include "CBulletItem.h"
#include "CPlayer.h"
#include <fstream>



CGameState3::CGameState3()
{
}


CGameState3::~CGameState3()
{
}

bool CGameState3::Init()
{
	//Create Objects
	CreateObject();

	//Create Map
	CreateMap();

	//Audio
	CAudioMgr::GetInst()->PlayMusic("Game2");

	return true;
}

void CGameState3::Update(double dDt)
{
	CObjMgr::GetInst()->Update(dDt);

	//if (CInput::GetInst()->KeyDown(SDL_SCANCODE_2))
	//{
	//	CGame::GetInst()->GetStateMgr()->ChangeState(new CGameState());
	//	return;
	//}

	CState::Update(dDt);
}

void CGameState3::Render()
{
	//Clear the screen 
	SDL_SetRenderDrawColor(CGame::GetInst()->GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(CGame::GetInst()->GetRenderer());

	//Render Objects
	CObjMgr::GetInst()->Render(CGame::GetInst()->GetRenderer());

	//Draw screen
	SDL_RenderPresent(CGame::GetInst()->GetRenderer());
}



void CGameState3::Shutdown()
{
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
void CGameState3::CreateObject()
{
	//Create Background
	CObjMgr::GetInst()->AddObj(CFactory<CBackGround>::CreateObj("Background3",
		{ 0, 0, 512, 432 }, { 0, 0, CGame::SCREEN_WIDTH, CGame::SCREEN_HEIGHT }), OBJ_BACKGROUND);

	//Create Enemy
	CObjMgr::GetInst()->AddObj(CFactory<CTurtle>::CreateObj(), OBJ_ENEMY);

}

//Create Map using txt file
void CGameState3::CreateMap()
{
	char tile;
	CObject* pItem, *enemy, * cannon;

	fstream mapfile("assets/level3.txt", ios::in);
	//mapfile.open("Level1.txt", ios::in);

	if (!mapfile.is_open())
		return;

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 250; x++)
		{
			mapfile.get(tile);

			if (tile == 'y')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 0, 0), OBJ_GROUNDTILE);
			else if (tile == 'h')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 16, 0), OBJ_GROUNDTILE);
			else if (tile == 'n')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 32, 0), OBJ_GROUNDTILE);
			else if (tile == 'u')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 48, 0), OBJ_GROUNDTILE);
			else if (tile == 'j')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 64, 0), OBJ_GROUNDTILE);
			else if (tile == 'm')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 80, 16), OBJ_GROUNDTILE);
			else if (tile == 'i')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 96, 16), OBJ_GROUNDTILE);
			else if (tile == 'k')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 0, 16), OBJ_GROUNDTILE);
			else if (tile == 'o')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 16, 16), OBJ_FILLERTILE);
			else if (tile == 'l')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 32, 16), OBJ_GROUNDTILE);
			else if (tile == '*')
				cout << ' ';
			else if (tile == 't')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 0, 32), OBJ_GROUNDTILE);
			else if (tile == 'g')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 16, 32), OBJ_GROUNDTILE);
			else if (tile == 'b')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 32, 32), OBJ_GROUNDTILE);
			else if (tile == 'r')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 80, 0), OBJ_GROUNDTILE);
			else if (tile == 'f')
				CObjMgr::GetInst()->AddObj(CFactory<CTile>::CreateObj("CaveTiles", x * (TILE_SIZE * 2), y * (TILE_SIZE * 2), 96, 0), OBJ_GROUNDTILE);
			else if (tile == 'P')
			{
				CObject* pPoll = CFactory<CLevelTransition>::CreateObj(x * (TILE_SIZE * 2), y * (TILE_SIZE * 2));
				((CLevelTransition*)pPoll)->SetStateToChange(CStateMgr::STATE_WIN);
				CObjMgr::GetInst()->AddObj(pPoll, OBJ_ETC);
			}
			else if (tile == '@')
			{
				//	CObjMgr::GetInst()->AddObj(CFactory<CPlayer>::CreateObj(), OBJ_PLAYER);
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
				cannon = CFactory<Cannon>::CreateObj(x * TILE_SIZE * 2, y * TILE_SIZE * 2);
				CObjMgr::GetInst()->AddObj(cannon, OBJ_GROUNDTILE);
			}
			else if (tile == 'c') // Coin
			{
				pItem = CFactory<CCoinItem>::CreateObj(x * TILE_SIZE * 2, y * TILE_SIZE * 2);
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