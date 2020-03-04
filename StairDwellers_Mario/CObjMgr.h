/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.11, 2019

//ObjMgr class is the singleton class that will handle all object in game
*//////////////////////////////////////////////////////////////////////

#ifndef _COBJMGR_H_
#define _COBJMGR_H_

#include "SingletonDefines.h"
#include <list>
#include "CObject.h"
#include "Enums.h"
using namespace std;

class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

private :
	list<CObject*> m_listObj[OBJ_END];

public :
	bool Init();
	void Update(double dDt);
	void Render(SDL_Renderer* pRenderer);
	void Shutdown();


public :
	void DeleteObjList(int iObjID);



	//Getter, setter
public :
	void AddObj(CObject* pObj, int iObjID);
	const list<CObject*>* GetObjList(int iObjID) const;
	CObject* GetObj(int iObjID, int iCnt = 0);
};

#endif