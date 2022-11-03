#pragma once
#include "WinAPI.h"

class CCore;
class CGameObject;

class CEventManager : public SingleTon<CEventManager>
{
	friend SingleTon<CEventManager>;
	friend CCore;
private:
	CEventManager();
	virtual ~CEventManager();

	queue<CGameObject*> m_queueAddObject;		// AddObject �̺�Ʈ ����
	queue<CGameObject*> m_queueDeleteObject;	// DeleteObject �̺�Ʈ ����
	pair<GroupScene, float>* m_pChangeScene;	// ChangeScene �̺�Ʈ ����
	//list<GroupScene> m_listChangeScene;			// ChangeScene �̺�Ʈ ����

	void Init();
	void Update();
	void Release();

public:
	void EventAddObject(CGameObject* pObj);						// ���������ӿ� �߰��� ������Ʈ �̺�Ʈ �߰�
	void EventDeleteObject(CGameObject* pObj);					// ���� ������ ������Ʈ �̺�Ʈ �߰�
	void EventChangeScene(GroupScene scene, float delay = 0);	// ����ȯ �̺�Ʈ �߰�

private:
	void ProgressAddObject();					// ������ �ʱ⿡ �߰��� ������Ʈ�� �߰�
	void ProgressDeleteObject();				// ���� ������ ������Ʈ�� ǥ��, ���� ������ ǥ�õ� ������Ʈ�� ����
	void ProgressChangeScene();					// ���������� ����� ����ȯ �̺�Ʈ ����
};

#define EVENT							CEventManager::GetInstance()
#define ADDOBJECT(pObj)					CEventManager::GetInstance()->EventAddObject(pObj)
#define DELETEOBJECT(pObj)				CEventManager::GetInstance()->EventDeleteObject(pObj)
#define CHANGESCENE(scene)				CEventManager::GetInstance()->EventChangeScene(scene)
#define DELAYCHANGESCENE(scene, delay)	CEventManager::GetInstance()->EventChangeScene(scene, delay)