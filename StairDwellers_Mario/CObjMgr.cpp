#include "CObjMgr.h"
#include "CDynamicObject.h"
#include "CInput.h"
#include "CGame.h"
#include "CObject.h"
#include <iostream>
using namespace std;

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{

}

bool CObjMgr::Init()
{
	return true;
}

//Iterate through all list and call update 
void CObjMgr::Update(double dDt)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		list<CObject*>::iterator iterBegin = m_listObj[i].begin();
		list<CObject*>::iterator iterEnd = m_listObj[i].end();
		for (; iterBegin != iterEnd;)
		{
			if ((*iterBegin)->GetDelete() == true)
			{
				(*iterBegin)->Shutdown();
				delete (*iterBegin);
				iterBegin = m_listObj[i].erase(iterBegin);
				continue;
			}

			(*iterBegin)->Update(dDt);
			++iterBegin;
		}
	}
}

//Iterate through all list and call render
void CObjMgr::Render(SDL_Renderer* pRenderer)
{
#if defined(DEBUG) || defined(_DEBUG)
	int Count = 0;
#endif

	for (int i = 0; i < OBJ_END; ++i)
	{
		list<CObject*>::iterator iterBegin = m_listObj[i].begin();
		list<CObject*>::iterator iterEnd = m_listObj[i].end();
		for (; iterBegin != iterEnd; ++iterBegin)
		{
			//just draw background and player
			if (i == OBJ_BACKGROUND || i == OBJ_UI || i == OBJ_FONT || i == H1 || i == H2 || i == H3)
			{
				(*iterBegin)->Render(pRenderer);
			}
			//other objects need to be checked if object is in inside our screen
			else
			{
				if (((*iterBegin)->GetDesRect()->x + (*iterBegin)->GetDesRect()->w) > 0 &&
					(*iterBegin)->GetDesRect()->x < CGame::SCREEN_WIDTH)
				{

					(*iterBegin)->Render(pRenderer);

#if defined(DEBUG) || defined(_DEBUG)
					++Count;

					//Render collision box
					if (CGame::s_bDebug)
					{
						if (i == OBJ_PLAYER || i == OBJ_ENEMY || i == OBJ_GROUNDTILE || i == OBJ_BULLET || i == OBJ_ETC )
						{
							const SDL_Rect* colRect = (*iterBegin)->GetDesRect();

							SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
							SDL_RenderDrawLine(pRenderer, colRect->x, colRect->y, colRect->x + colRect->w, colRect->y);	//Left Top -> Right Top
							SDL_RenderDrawLine(pRenderer, colRect->x + colRect->w, colRect->y, colRect->x + colRect->w, colRect->y + colRect->h); //Right Top -> Right Bottom
							SDL_RenderDrawLine(pRenderer, colRect->x + colRect->w, colRect->y + colRect->h, colRect->x, colRect->y + colRect->h); //RIght Bottom -> Left Bottom
							SDL_RenderDrawLine(pRenderer, colRect->x, colRect->y + colRect->h, colRect->x, colRect->y); //Left Bottom -> Left TOp
						}
					}
#endif
				}
			}			
		}
	}

#if defined(DEBUG) || defined(_DEBUG)
	cout << "Render Count: " << Count << endl;
#endif
}

//Iterate through all list and call shutdown
void CObjMgr::Shutdown()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		list<CObject*>::iterator iterBegin = m_listObj[i].begin();
		list<CObject*>::iterator iterEnd = m_listObj[i].end();
		for (; iterBegin != iterEnd; ++iterBegin)
		{
			(*iterBegin)->Shutdown();
			delete (*iterBegin);
			(*iterBegin) = nullptr;
		}
		m_listObj[i].clear();
	}
}

void CObjMgr::DeleteObjList(int iObjID)
{
	//Check ObjID bound
	if (iObjID < 0 || iObjID >= OBJ_END)
		return;

	list<CObject*>::iterator iterBegin = m_listObj[iObjID].begin();
	list<CObject*>::iterator iterEnd = m_listObj[iObjID].end();
	for (; iterBegin != iterEnd; ++iterBegin)
	{
		(*iterBegin)->Shutdown();
		delete (*iterBegin);
		(*iterBegin) = nullptr;
	}
	m_listObj[iObjID].clear();
}

void CObjMgr::AddObj(CObject* pObj, int iObjID)
{
	//Check pObj
	if (pObj == nullptr)
		return;

	//Check ObjID bound
	if (iObjID < 0 || iObjID >= OBJ_END)
		return;	

	//Add Object to list
	m_listObj[iObjID].push_back(pObj);
}

const list<CObject*>* CObjMgr::GetObjList(int iObjID) const
{
	//Check ObjID bound
	if (iObjID < 0 || iObjID >= OBJ_END)
		return nullptr;

	return &m_listObj[iObjID];
}

CObject* CObjMgr::GetObj(int iObjID, int iCnt)
{
	//Check ObjID bound
	if (iObjID < 0 || iObjID >= OBJ_END)
		return nullptr;

	list<CObject*>::const_iterator iterBegin = m_listObj[iObjID].begin();

	for (int i = 0; i < iCnt; ++iterBegin)
	{

	}

	return (*iterBegin);

}