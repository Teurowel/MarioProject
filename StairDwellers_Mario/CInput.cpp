#include "CInput.h"
#include "CGame.h"
#include "CStateMgr.h"

IMPLEMENT_SINGLETON(CInput)

CInput::CInput()
	:m_iMouseX(0), m_iMouseY(0),
	m_bMouseLeft(false)
{

}

bool CInput::Init()
{
	bool bResult = true;

	m_iKeystates = SDL_GetKeyboardState(nullptr);

	return true;
}

//If SDL_QUIT event occur, it will return false to change m_bRunning in Game class
bool CInput::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			/*switch (event.key.keysym.sym)
			{
			case 'w':
			case 'W':
				if (!m_bWPressed)
					m_bWPressed = true;
				break;
			case 's':
			case 'S':
				if (!m_bSPressed)
					m_bSPressed = true;
				break;
			case 'a':
			case 'A':
				if (!m_bAPressed)
					m_bAPressed = true;
				break;
			case 'd':
			case 'D':
				if (!m_bDPressed)
					m_bDPressed = true;
				break;
			}*/
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case 'p' :
			case 'P' :
				CGame::s_bDebug = !CGame::s_bDebug;
				break;

			case 'h':
			case 'H':
				CGame::GetInst()->GetStateMgr()->SetState(CStateMgr::STATE_PAUSE);
				break;
			//case 'w':
			//case 'W':
			//	m_bWPressed = false;
			//	break;
			//case 's':
			//case 'S':
			//	m_bSPressed = false;
			//	break;
			//case 'a':
			//case 'A':
			//	m_bAPressed = false;
			//	break;
			//case 'd':
			//case 'D':
			//	m_bDPressed = false;
			//	break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bMouseLeft = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bMouseLeft = false;
			break;

		case SDL_MOUSEMOTION :
			SDL_GetMouseState(&m_iMouseX, &m_iMouseY);
			break;

		case SDL_QUIT:
			return false;
			break;
		}
	}

	return true;
}

bool CInput::KeyDown(SDL_Scancode code)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[code] == 1)
			return true;
		else
			return false;
	}
	return false;
}