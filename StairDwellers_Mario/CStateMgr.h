#ifndef _CSTATEMGR_H_
#define _CSTATEMGR_H_

#include <vector>
using namespace std;

class CState;
class CStateMgr
{
public :
	enum StateList { STATE_TITLE, STATE_GAME1, STATE_GAME2, STATE_GAME3, STATE_LOSE, STATE_WIN, STATE_PAUSE, STATE_NULL };

private:
	vector<CState*> m_vecStates;
	StateList m_eCurrentState;
	StateList m_ePrevState;
	StateList m_eRequestedState;

public:
	CStateMgr();
	~CStateMgr();

public:
	bool Init();
	void Update(double dDt);
	void Render();
	void PushState(CState* pState);	
	void PopState();
	void Shutdown();


public :
	vector<CState*>& GetStates() { return m_vecStates; }
	

	void SetState(StateList eState) { m_eRequestedState = eState; }

private :
	void ChangeState(CState* pState);
};

#endif
