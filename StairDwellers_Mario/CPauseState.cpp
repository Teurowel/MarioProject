#include "CPauseState.h"




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


CPauseState::CPauseState()
	:pPauseBackGround(nullptr)
{
}


CPauseState::~CPauseState()
{
}

bool CPauseState::Init()
{
	CAudioMgr::GetInst()->ToggleMusic();
	CAudioMgr::GetInst()->PlaySound("Pause");
	pPauseBackGround = CFactory<CTitleBackGround>::CreateObj("PauseBackground", { 0, 0, 895, 627 }, { 0, 0, CGame::SCREEN_WIDTH, CGame::SCREEN_HEIGHT });
	pContinueButton = CFactory<CButton>::CreateObj("ContinueButton", { 0, 0, 360, 80 }, { CGame::SCREEN_WIDTH - 290, CGame::SCREEN_HEIGHT - 100, 190, 70 });
		
	//CObjMgr::GetInst()->AddObj(CFactory<CTitleBackGround>::CreateObj("Pause", { 0, 0, 1280, 720 }, { 0, 0, CGame::SCREEN_WIDTH, CGame::SCREEN_HEIGHT }), OBJ_UI);
	//CObjMgr::GetInst()->AddObj(CFactory<CButton>::CreateObj("Continue Button", { 50, 150, 190, 70 }, { CGame::SCREEN_WIDTH - 290, CGame::SCREEN_HEIGHT - 100, 190, 70 }), OBJ_UI);


	return true;
}

void CPauseState::Update(double dDt)
{
	//CObjMgr::GetInst()->Update(dDt);

	pPauseBackGround->Update(dDt);
	pContinueButton->Update(dDt);

	if (dynamic_cast<CButton*>(pContinueButton)->GetClicked())
	{
		CGame::GetInst()->GetStateMgr()->PopState();
		return;
	}
}

void CPauseState::Render()
{
	SDL_SetRenderDrawColor(CGame::GetInst()->GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(CGame::GetInst()->GetRenderer());

	//Render Objects
	//CObjMgr::GetInst()->Render(CGame::GetInst()->GetRenderer());

	pPauseBackGround->Render(CGame::GetInst()->GetRenderer());
	pContinueButton->Render(CGame::GetInst()->GetRenderer());

	//Draw screen
	SDL_RenderPresent(CGame::GetInst()->GetRenderer());

}

void CPauseState::Shutdown()
{
	CAudioMgr::GetInst()->ToggleMusic();

	delete pPauseBackGround;
	delete pContinueButton;
}

