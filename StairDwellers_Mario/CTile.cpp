#include "CTile.h"
#include "CImgMgr.h"
#include "CGame.h"
#include "CObjMgr.h"
#include "CDynamicObject.h"
#include "CInput.h"

float CTile::s_fTileLeftOffset = TILE_SIZE * 10;
float CTile::s_fTileSpeed = 0;

CTile::CTile()
{
}

CTile::CTile(int iXpos, int iYpos)
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_fPositionX = iXpos;
	m_fPositionY = iYpos;

	m_desRect.x = iXpos;
	m_desRect.y = iYpos;
}

CTile::CTile(int iXpos, int iYpos, int iSrcX, int iSrcY)
{
	m_srcRect.x = iSrcX;
	m_srcRect.y = iSrcY;

	m_fPositionX = iXpos;
	m_fPositionY = iYpos;

	m_desRect.x = iXpos;
	m_desRect.y = iYpos;
}

CTile::CTile(const char* szImgKey, int iXpos, int iYpos, int iSrcX, int iSrcY)
	:m_szImgKey(szImgKey)
{
	m_srcRect.x = iSrcX;
	m_srcRect.y = iSrcY;

	m_fPositionX = iXpos;
	m_fPositionY = iYpos;

	m_desRect.x = iXpos;
	m_desRect.y = iYpos;
}

CTile::CTile(const char* szImgKey, int iXpos, int iYpos, int iSrcX, int iSrcY, const SDL_Rect& boundRect)
	:m_szImgKey(szImgKey)
{
	m_srcRect.x = iSrcX;
	m_srcRect.y = iSrcY;

	m_fPositionX = iXpos;
	m_fPositionY = iYpos;

	m_desRect.x = iXpos;
	m_desRect.y = iYpos;
}

bool CTile::Init()
{
	bool bResult = true;

	m_srcRect.w = TILE_SIZE;
	m_srcRect.h = TILE_SIZE;

	m_desRect.w = TILE_SIZE * 2;
	m_desRect.h = TILE_SIZE * 2;

	return bResult;
}

void CTile::Update(double dDt)
{
	CObject* pPlayer = CObjMgr::GetInst()->GetObj(OBJ_PLAYER);
	
	//if player goes to right, tile goes to left
	if (pPlayer->GetPositionX() > CGame::SCREEN_WIDTH * 0.5)
	{
		m_fPositionX -= ((CDynamicObject*)pPlayer)->GetVelocityX() * dDt;
		m_desRect.x = (int)m_fPositionX;

		if (((CDynamicObject*)pPlayer)->GetVelocityX() != 0)
			s_fTileSpeed = ((CDynamicObject*)pPlayer)->GetVelocityX() * dDt;
		else
			s_fTileSpeed = 0.f;
	}
	else
		s_fTileSpeed = 0.f;
	////ifp layer goes to left, tile goes to right
	//else if (pPlayer->GetPositionX() < s_fTileLeftOffset)
	//{
	//	m_fPositionX += -(((CDynamicObject*)pPlayer)->GetVelocityX() * dDt);
	//	m_desRect.x = (int)m_fPositionX;
	//}
}



void CTile::Render(SDL_Renderer * pRenderer)
{
	SDL_RenderCopy(pRenderer, CImgMgr::GetInst()->GetImg(m_szImgKey), &m_srcRect, &m_desRect);
}


void CTile::Shutdown()
{

}
