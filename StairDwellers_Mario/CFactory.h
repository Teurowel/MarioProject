/*/////////////////////////////////////////////////////////////////////
Author : Doosung Jang
Last Updated : Jan.11, 2019

//Factory class is the class that will make object instance.
//Factory class is class template
*//////////////////////////////////////////////////////////////////////

#ifndef _CFACTORY_H_
#define _CFACTORY_H_

#include "CObject.h"

template<class T>
class CFactory
{
public :
	static CObject* CreateObj()
	{
		bool bResult = false;
		CObject* pObj = new T;
		bResult = pObj->Init();
		if (bResult == false)
			return nullptr;
		return pObj;
	}

	static CObject* CreateObj(int iXpos, int iYpos)
	{
		bool bResult = false;
		CObject* pObj = new T(iXpos, iYpos);
		bResult = pObj->Init();
		if (bResult == false)
			return nullptr;
		return pObj;
	}

	static CObject* CreateObj(int iXpos, int iYpos, int iSrcX, int iSrcY)
	{
		bool bResult = false;
		CObject* pObj = new T(iXpos, iYpos, iSrcX, iSrcY);
		bResult = pObj->Init();
		if (bResult == false)
			return nullptr;
		return pObj;
	}

	static CObject* CreateObj(const char* szImgKey, int iXpos, int iYpos, int iSrcX, int iSrcY)
	{
		bool bResult = false;
		CObject* pObj = new T(szImgKey, iXpos, iYpos, iSrcX, iSrcY);
		bResult = pObj->Init();
		if (bResult == false)
			return nullptr;
		return pObj;
	}

	static CObject* CreateObj(const char* szImgKey, int iXpos, int iYpos, int iSrcX, int iSrcY, const SDL_Rect& boundRect )
	{
		bool bResult = false;
		CObject* pObj = new T(szImgKey, iXpos, iYpos, iSrcX, iSrcY, boundRect);
		bResult = pObj->Init();
		if (bResult == false)
			return nullptr;
		return pObj;
	}

	static CObject* CreateObj(const char* szImgKey, const SDL_Rect& srcRect, const SDL_Rect& desRect)
	{
		bool bResult = false;
		CObject* pObj = new T(szImgKey, srcRect, desRect);
		bResult = pObj->Init();
		if (bResult == false)
			return nullptr;
		return pObj;
	}
};

#endif