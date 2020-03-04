//For detecting memory leak
#if defined(DEBUG) | defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#endif

#include "CGame.h"
#include "CTimer.h"

int main(int argc, char* args[])
{
	//For detecting memory leak
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	bool bResult = false;

	//Create Game
	bResult = CGame::GetInst()->Init();	

	//Create Timer
	bResult = CTimer::GetInst()->Init();

	//if game init success
	if (bResult)
	{
		//Run the game
		while (CGame::GetInst()->GetRunning())
		{
			double dDeltaTime = CTimer::GetInst()->GetDeltaTime();

			CGame::GetInst()->HandleEvenets();
			CGame::GetInst()->Update(dDeltaTime); //second
			CGame::GetInst()->Render();
		}
	}

	//Shutdown Timer
	CTimer::GetInst()->Shutdown();
	CTimer::GetInst()->DestroyInst();

	//Shutdown Game
	CGame::GetInst()->Shutdown();
	CGame::GetInst()->DestroyInst();

	return 0;
}