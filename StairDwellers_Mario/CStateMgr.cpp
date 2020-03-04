#include "CStateMgr.h"

#include "CState.h"
#include "CTitleState.h"
#include "CGameState.h"
#include "CGameState2.h"
#include "CGameState3.h"
#include "CLoseState.h"
#include "CWinState.h"
#include "CPauseState.h"

CStateMgr::CStateMgr()
{
}


CStateMgr::~CStateMgr()
{
}

bool CStateMgr::Init()
{
	m_eCurrentState = STATE_NULL;

	return true;
}

void CStateMgr::Update(double dDt)
{
	if (!m_vecStates.empty())
		m_vecStates.back()->Update(dDt);

	if (m_eRequestedState != m_eCurrentState)
	{
		switch (m_eRequestedState)
		{
		case STATE_TITLE:
			ChangeState(new CTitleState);
			break;

		case STATE_GAME1:
			ChangeState(new CGameState);
			break;

		case STATE_GAME2:
			ChangeState(new CGameState2);
			break;

		case STATE_GAME3:
			ChangeState(new CGameState3);
			break;

		case STATE_LOSE:
			ChangeState(new CLoseState);
			break;

		case STATE_WIN:
			ChangeState(new CWinState);
			break;

		case STATE_PAUSE:
			PushState(new CPauseState);
			break;
		}
	}
}

void CStateMgr::Render()
{
	if (!m_vecStates.empty())
		m_vecStates.back()->Render();
}

void CStateMgr::PushState(CState * pState)
{
	pState->Init();
	m_vecStates.push_back(pState); // push_back() is a method of the vector type.
	m_ePrevState = m_eCurrentState;
	m_eCurrentState = m_eRequestedState;
	m_eRequestedState = STATE_NULL;
}

void CStateMgr::ChangeState(CState * pState)
{
	if (!m_vecStates.empty())
	{
		m_vecStates.back()->Shutdown();
		delete m_vecStates.back(); // De-allocating the state in the heap.
		m_vecStates.back() = nullptr; // Nullifying pointer to the de-allocated state.
		m_vecStates.pop_back(); // Removes the now-null pointer from the vector.
	}
	pState->Init();
	m_vecStates.push_back(pState);
	m_eCurrentState = m_eRequestedState;
	m_eRequestedState = STATE_NULL;
}

void CStateMgr::PopState()
{
	if (!m_vecStates.empty())
	{
		m_vecStates.back()->Shutdown();
		delete m_vecStates.back();
		m_vecStates.back() = nullptr;
		m_vecStates.pop_back();
		m_eCurrentState = m_ePrevState;
	}
}

void CStateMgr::Shutdown()
{
	while (!m_vecStates.empty()) // Because we can exit the game in the pause state with the window's 'X'.
	{						   // Ensures that ALL states left in the vector are cleaned up.
		m_vecStates.back()->Shutdown();
		delete m_vecStates.back();
		m_vecStates.back() = nullptr;
		m_vecStates.pop_back();
	}
}
