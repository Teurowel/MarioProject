#include "CTitleState.h"

#include "CGame.h"
#include "CObjMgr.h"
#include "CImgMgr.h"
#include "CAudioMgr.h"
#include "CInput.h"
#include "CStateMgr.h"
#include "CGameState.h"
#include "CGameState2.h"
#include "CFactory.h"
#include "CUI.h"
#include "CTitleBackGround.h"
#include "CButton.h"
#include "CPlayer.h"
#include "CFont.h"


CTitleState::CTitleState()
{

}

CTitleState::~CTitleState()
{

}

bool CTitleState::Init()
{
	CObjMgr::GetInst()->Shutdown();

	//Create Objects for Title

	//start button
	CObject* pObj = CFactory<CButton>::CreateObj("StartButton", { 0, 0, 360, 80 }, { 100, CGame::SCREEN_HEIGHT - 100, 190, 70 });
	CObjMgr::GetInst()->AddObj(pObj, OBJ_UI);

	//title background
	pObj = CFactory<CTitleBackGround>::CreateObj("Title", { 0, 0, 1187, 584 }, { 0, 0, CGame::SCREEN_WIDTH, CGame::SCREEN_HEIGHT });
	CObjMgr::GetInst()->AddObj(pObj, OBJ_BACKGROUND);


	//CObject* pFont = new CFont("Test", { 0, 0, 0, 255 }, 100, 100);
	//CObjMgr::GetInst()->AddObj(pFont, OBJ_FONT);

	//title music
	CAudioMgr::GetInst()->PlayMusic("Title");

	return true;
}

void CTitleState::Update(double dDt)
{
	CObjMgr::GetInst()->Update(dDt);

	//play button click check
	CButton* pStartBtn = dynamic_cast<CButton*>(CObjMgr::GetInst()->GetObj(OBJ_UI, btn::play));
	if (pStartBtn != nullptr)
	{
		if (pStartBtn->GetClicked())
		{
			CGame::GetInst()->GetStateMgr()->SetState(CStateMgr::STATE_GAME1);
			return;
		}
	}
}

void CTitleState::Render()
{
	//Clear the screen 
	SDL_SetRenderDrawColor(CGame::GetInst()->GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(CGame::GetInst()->GetRenderer());

	//Render Objects
	CObjMgr::GetInst()->Render(CGame::GetInst()->GetRenderer());

	//Draw screen
	SDL_RenderPresent(CGame::GetInst()->GetRenderer());

}



void CTitleState::Shutdown()
{
	CObjMgr::GetInst()->Shutdown();

	//DeleteObjectsInScene();

	CAudioMgr::GetInst()->StopMusic();
}