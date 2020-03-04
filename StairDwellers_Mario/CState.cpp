#include "CState.h"

#include "CGame.h"
#include "CStateMgr.h"
#include "CLoseState.h"
#include "CObject.h"


CState::CState()
{
}


CState::~CState()
{
}

void CState::Update(double dDt)
{

}

void CState::DeleteObjectsInScene()
{
	list<CObject*>::iterator iterBegin = m_listDeleteObjectList.begin();
	list<CObject*>::iterator iterEnd = m_listDeleteObjectList.end();

	for (; iterBegin != iterEnd; ++iterBegin)
	{
		(*iterBegin)->SetDelete(true);
	}
	m_listDeleteObjectList.clear();
}