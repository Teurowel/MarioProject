#ifndef _CSTATE_H_
#define _CSTATE_H_

#include <list>

class CObject;
class CState
{
private :
	std::list<CObject*> m_listDeleteObjectList;

public:
	CState();
	virtual ~CState();

public :
	virtual bool Init() = 0;
	virtual void Update(double dDt); // Having at least one 'pure virtual' method like this, makes a class abtract.
	virtual void Render() = 0;     // Meaning we cannot create objects of the class.
	virtual void Shutdown() = 0;

protected :
	void SetDeleteObjectsInScene(CObject* pObject) { m_listDeleteObjectList.push_back(pObject); }
	void DeleteObjectsInScene();
};

#endif