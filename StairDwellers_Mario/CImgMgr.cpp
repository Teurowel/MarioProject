#include "CImgMgr.h"

IMPLEMENT_SINGLETON(CImgMgr)

CImgMgr::CImgMgr()
{

}

bool CImgMgr::Init()
{
	return true;
}

void CImgMgr::Shutdown()
{
	map<const char*, SDL_Texture*>::iterator iterBegin = m_mapImg.begin();
	map<const char*, SDL_Texture*>::iterator iterEnd = m_mapImg.end();

	for (; iterBegin != iterEnd; ++iterBegin)
	{
		SDL_DestroyTexture(iterBegin->second);
	}
	m_mapImg.clear();
}

//Add Image to map
bool CImgMgr::AddImg(const char* szImagePath, const char* szImageKey, SDL_Renderer* pRenderer)
{
	//Create surface, texture
	SDL_Surface* pSurface = IMG_Load(szImagePath);
	if (pSurface == nullptr)
	{
		cout << szImagePath << "Image Load Failed" << endl;
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (pTexture == nullptr)
	{
		cout << szImagePath << "Create Texture Failed" << endl;
		return false;
	}
	//After making texture, we don't need surface anymore
	SDL_FreeSurface(pSurface);  

	//Create variable that will hold return value of insert function
	pair<map<const char*, SDL_Texture*>::iterator, bool> ret;

	//Insert texture to map
	//ret = m_mapImg.insert(pair<const char*, SDL_Texture*>(szImageKey, pTexture));
	ret = m_mapImg.insert(make_pair(szImageKey, pTexture));
	
	//if the same key value already exited,
	if (ret.second == false)
	{
		cout << szImageKey << " already exists" << endl;
		SDL_DestroyTexture(pTexture);
		return true;
	}

	return true;
}

//Find texture and return it
SDL_Texture* CImgMgr::GetImg(const char* szImageKey) const
{
	map<const char*, SDL_Texture*>::const_iterator iter;

	//Find element with key value
	iter = m_mapImg.find(szImageKey);

	//If there was no element,
	if (iter == m_mapImg.end())
		return nullptr;
	
	//return texture
	return iter->second;
}