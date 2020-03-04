#include "CGame.h"
#include "CObjMgr.h"
#include "CImgMgr.h"
#include "CStateMgr.h"
#include "CAudioMgr.h"
#include "CInput.h"


IMPLEMENT_SINGLETON(CGame)

bool CGame::s_bDebug = false;

CGame::CGame()
	:m_pWindow(nullptr),
	m_pRenderer(nullptr),
	m_pStateMgr(nullptr),
	m_bRunning(false),
	m_hp(3)
{

}

bool CGame::Init()
{
	bool bResult = false;

	//Create SDL
	bResult = InitSDL();
	if (bResult == false)
		return false;

	//Create Input
	bResult = CInput::GetInst()->Init();
	if (bResult == false)
		return false;

	//Create ObjMgr
	bResult = CObjMgr::GetInst()->Init();
	if (bResult == false)
		return false;

	//Create ImgMgr
	bResult = CImgMgr::GetInst()->Init();
	if (bResult == false)
		return false;

	//Create AudioMgr
	bResult = CAudioMgr::GetInst()->Init();
	if (bResult == false)
		return false;

	

	//Load Image
	bResult = LoadImages();
	if (bResult == false)
		return false;

	bResult = LoadSound();
	if (bResult == false)
		return false;
	




	//Create StateMgr
	m_pStateMgr = new CStateMgr;
	bResult = m_pStateMgr->Init();
	if (bResult == false)
		return false;

	//Set title state
	m_pStateMgr->SetState(CStateMgr::STATE_TITLE);

	m_bRunning = true;
	return true;
}

void CGame::Update(double dDt)
{
	m_pStateMgr->Update(dDt);
}

void CGame::Render()
{
	m_pStateMgr->Render();


}

void CGame::Shutdown()
{
	//Destroy StateMgr
	if (m_pStateMgr != nullptr)
	{
		m_pStateMgr->Shutdown();
		delete m_pStateMgr;
		m_pStateMgr = nullptr;
	}

	//Destro AudioMgr
	CAudioMgr::GetInst()->Shutdown();
	CAudioMgr::GetInst()->DestroyInst();

	//Desroy ImgMgr
	CImgMgr::GetInst()->Shutdown();
	CImgMgr::GetInst()->DestroyInst();

	//Desroy ObjMgr
	CObjMgr::GetInst()->Shutdown();
	CObjMgr::GetInst()->DestroyInst();

	//Destroy Input
	CInput::GetInst()->DestroyInst();

	//Destroy SDL
	ShutdownSDL();
}

void CGame::HandleEvenets()
{
	m_bRunning = CInput::GetInst()->HandleEvents();
}

bool CGame::InitSDL()
{
	//Attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL init success" << endl;
		//Init the window
		m_pWindow = SDL_CreateWindow("Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if (m_pWindow != 0) // Window init success
		{
			cout << "window creation success" << endl;

			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // Renderer init success
			{
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

				cout << "renderer creation success" << endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				cout << "renderer creation fail" << endl;
				SDL_DestroyWindow(m_pWindow);
				SDL_Quit();
				return false; // renderer init fail
			}
		}
		else
		{
			cout << "window creation fail" << endl;
			SDL_Quit();
			return false; // window init fail
		}

		//Init Image system
		int iImgInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
		int iResult = IMG_Init(iImgInitFlags);
		if ((iResult & iImgInitFlags) == iImgInitFlags)
		{
			cout << "IMG_Init success" << endl;
		}
		else
		{
			cout << "IMG_Init fail" << endl;
			SDL_DestroyRenderer(m_pRenderer);
			SDL_DestroyWindow(m_pWindow);
			SDL_Quit();
			return false;
		}

		//Font init
		if (TTF_Init() == 0)
		{
			cout << "TTF_Init success!" << endl;
			
			m_pFont = TTF_OpenFont("assets/LTYPE.TTF", 18); // 18 is our desired font size.
			if (m_pFont == nullptr)
			{
				cout << "TTF_OpenFont Error" << endl;
				return false;
			}
		}
		else
		{
			cout << "TTF_Init fail!" << endl;
			IMG_Quit();
			SDL_DestroyRenderer(m_pRenderer);
			SDL_DestroyWindow(m_pWindow);
			SDL_Quit();
			return false;
		}
	}
	else
	{
		cout << "SDL init fail" << endl;
		return false; //SDL init fail
	}

	return true;
}

void CGame::ShutdownSDL()
{
	cout << "cleaning game" << endl;
	TTF_CloseFont(m_pFont);
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}



//Load all assets that is required for game
bool CGame::LoadImages()
{
	bool bResult = true;

	bResult = CImgMgr::GetInst()->AddImg("assets/Mario.png", "Mario", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/Enemy.png", "Enemy", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/Cannon.png", "Cannon", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/Bullets.png", "Bullets", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/Tiles.png", "Tiles", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/BackGround.png", "BackGround", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/BackGround2.png", "BackGround2", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/UI.png", "UI", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/Title.jpg", "Title", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/newGameButton.png", "StartButton", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/ContinueButton2.png", "ContinueButton", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/Lose.jpg", "Lose", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/Flag.png", "Flag", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/Coin.png", "Coin", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/GoldMushroom.png", "GoldMushroom", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/CaveTiles.png", "CaveTiles", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/Background3.png", "Background3", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/marioWin.jpg", "Win", m_pRenderer);
	if (bResult == false)
		return false;

	bResult = CImgMgr::GetInst()->AddImg("assets/mariopause1.png", "PauseBackground", m_pRenderer);
	if (bResult == false)
		return false;

	return bResult;
}

bool CGame::LoadSound()
{
	bool bResult = true;
	
	bResult = CAudioMgr::GetInst()->LoadMusic("assets/Title.mp3", "Title");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadMusic("assets/Game1.mp3", "Game1");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadMusic("assets/Game3.mp3", "Game2");
	if (bResult == false)
		return false;
	
	bResult = CAudioMgr::GetInst()->LoadMusic("assets/game4.mp3", "Game4");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/JumpSFX.wav", "Jump");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/Missile.wav", "Missile");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/Bullet.wav", "Bullet");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/Stomp.wav", "Stomp");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/Lose.wav", "Lose");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/Win.wav", "Win");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/GetBullet.wav", "GetBullet");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/GetCoin.wav", "GetCoin");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/StageClear.wav", "StageClear");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/marioHurt.wav", "Hurt");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/sm64_fly_guy_dead.wav", "Koopa");
	if (bResult == false)
		return false;

	bResult = CAudioMgr::GetInst()->LoadSound("assets/sm64_pause.wav", "Pause");
	if (bResult == false)
		return false;

	return bResult;
}