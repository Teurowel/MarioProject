#include "CLevelTransition.h"

#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CGame.h"
#include "CStateMgr.h"
#include "CAudioMgr.h"
#include "CPlayer.h"

CLevelTransition::CLevelTransition()
{

}

CLevelTransition::CLevelTransition(int iXpos, int iYpos)
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = 149;
	m_srcRect.h = 479;

	m_desRect.x = iXpos;
	m_fPositionX = m_desRect.x;
	m_desRect.y = iYpos;
	m_desRect.w = int(149 * 0.4);
	m_desRect.h = int(479 * 0.74);

	m_DrawingRect = m_desRect;

	m_desRect.w = int(149 * 0.17);

	m_bTransitStart = false;
	m_dTransitTime = 0;
	m_dMaxTransitTime = 7;

	m_fColPos = 0.f;
}
bool CLevelTransition::Init()
{

	return true;
}

void CLevelTransition::Update(double dDt)
{
	CStaticObject::Update(dDt);
	m_DrawingRect.x = m_desRect.x;
	m_desRect.x = m_DrawingRect.x + 30;

	CObject* pPlayer = CObjMgr::GetInst()->GetObj(OBJ_PLAYER);
	const SDL_Rect* pPlayerRect = CObjMgr::GetInst()->GetObj(OBJ_PLAYER)->GetDesRect();

	if (m_bTransitStart == false)
	{
		//Player collision check
		SDL_Rect col;
		
		if (SDL_IntersectRect(pPlayerRect, &m_desRect, &col))
		{
			CAudioMgr::GetInst()->StopMusic();
			CAudioMgr::GetInst()->PlaySound("StageClear");
			m_bTransitStart = true;
			m_fColPos = pPlayerRect->y;
			((CPlayer*)pPlayer)->SetIsTransit(true);
		}
	}

	//start transit timer
	if (m_bTransitStart)
	{
		m_dTransitTime += dDt;


		//pull player down till reach the bottom of pole
		if (m_fColPos <= (m_desRect.y + m_desRect.h - pPlayerRect->h))
		{
			pPlayer->SetDestX(m_desRect.x);
			pPlayer->SetX(m_desRect.x);

			m_fColPos += 100 * dDt;
			pPlayer->SetDestY(m_fColPos);
			pPlayer->SetY(m_fColPos);
		}
		else
		{

		}

		if (m_dTransitTime >= m_dMaxTransitTime)
		{
			m_bTransitStart = false;
			((CPlayer*)pPlayer)->SetIsTransit(false);
			CGame::GetInst()->GetStateMgr()->SetState(m_eStateToChange);
			return;
		}
	}
}

void CLevelTransition::Render(SDL_Renderer * pRenderer)
{
	SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg("Flag"), &m_srcRect, &m_DrawingRect);
}

void CLevelTransition::Shutdown()
{

}
