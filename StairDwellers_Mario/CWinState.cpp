#include "CWinState.h"

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
#include "CTitleState.h"

CWinState::CWinState()
{

}

CWinState::~CWinState()
{

}

bool CWinState::Init()
{
	CObjMgr::GetInst()->Shutdown();

	//Create Objects for Title

	//start button
	CObjMgr::GetInst()->AddObj(CFactory<CButton>::CreateObj("ContinueButton", { 0, 0, 380, 80 }, { CGame::SCREEN_WIDTH - 290, CGame::SCREEN_HEIGHT - 100, 190, 70 }), OBJ_UI);

	//background
	CObjMgr::GetInst()->AddObj(CFactory<CTitleBackGround>::CreateObj("Win", { 0, 0, 711, 374}, { 0, 0, CGame::SCREEN_WIDTH, CGame::SCREEN_HEIGHT }), OBJ_BACKGROUND);

	//title music
	CAudioMgr::GetInst()->PlaySound("Win");
	return true;
}

void CWinState::Update(double dDt)
{
	CObjMgr::GetInst()->Update(dDt);

	//play button click check
	CButton* pContinueBtn = dynamic_cast<CButton*>(CObjMgr::GetInst()->GetObj(OBJ_UI, btn::mainmenu));
	if (pContinueBtn != nullptr)
	{
		if (pContinueBtn->GetClicked())
		{
			CGame::GetInst()->GetStateMgr()->SetState(CStateMgr::STATE_TITLE);
			return;
		}
	}
}

void CWinState::Render()
{
	//Clear the screen 
	SDL_SetRenderDrawColor(CGame::GetInst()->GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(CGame::GetInst()->GetRenderer());

	//Render Objects
	CObjMgr::GetInst()->Render(CGame::GetInst()->GetRenderer());

	//Draw screen
	SDL_RenderPresent(CGame::GetInst()->GetRenderer());

}



void CWinState::Shutdown()
{
	CObjMgr::GetInst()->Shutdown();
	CAudioMgr::GetInst()->StopSound();
}