#ifndef _CLEVELTRANSITION_H_
#define _CLEVELTRANSITION_H_

#include "CStaticObject.h"
#include "CStateMgr.h"

class CLevelTransition : public CStaticObject
{
private :
	CStateMgr::StateList m_eStateToChange;

	SDL_Rect m_DrawingRect;

	bool m_bTransitStart;
	double m_dTransitTime;
	double m_dMaxTransitTime;

	float m_fColPos;

public:
	CLevelTransition();
	CLevelTransition(int iXpos, int iYpos);
	CLevelTransition(const CLevelTransition & copy) {}
	CLevelTransition& operator=(const CLevelTransition & copy) {}
	virtual ~CLevelTransition() {}

	virtual bool Init();
	virtual void Update(double dDt);
	virtual void Render(SDL_Renderer* pRenderer);
	virtual void Shutdown();

public :
	void SetStateToChange(CStateMgr::StateList eStateToChange) { m_eStateToChange = eStateToChange; }
	bool GetIsTransitStart() const { return m_bTransitStart; }
};

#endif