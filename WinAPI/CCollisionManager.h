#pragma once
#include "WinAPI.h"

class CCore;
class CCollider;

class CCollisionManager : public SingleTon<CCollisionManager>
{
	friend SingleTon<CCollisionManager>;
	friend CCore;
private:
	CCollisionManager();
	virtual ~CCollisionManager();

	bool m_arrLayer[(int)Layer::Size][(int)Layer::Size];	// �浹�� Ȯ���� ���̾� ����
	unordered_map<UINT64, bool> m_umapPrevCollision;	// �浹ü���� ���� �浹 ����

private:
	void Init();
	void Update();
	void Release();

private:
	void CollisionUpdate(Layer leftLayer, Layer rightLayer);
	bool IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider);
	bool RectCollision(Vector leftPos, Vector leftScale, Vector rightPos, Vector rightScale);
	bool CircleCollision(Vector leftPos, float leftScale, Vector rightPos, float rightScale);
	bool RectCircleCollision(Vector rectPos, Vector rectScale, Vector circlePos, float circleScale);

	void CheckLayer(Layer left, Layer right);
	void UnCheckLayer(Layer left, Layer right);
	void ResetCheck();

	UINT64 CollisionID(UINT leftID, UINT rightID);
};

#define COLLISION	CCollisionManager::GetInstance()