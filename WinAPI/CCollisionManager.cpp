#include "framework.h"
#include "CCollisionManager.h"

#include "CSceneManager.h"
#include "CGameObject.h"
#include "CScene.h"
#include "CCollider.h"

CCollisionManager::CCollisionManager()
{
	m_arrLayer[0][0] = { 0 };
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Init()
{
	CheckLayer(Layer::Monster, Layer::Missile);
	CheckLayer(Layer::Monster, Layer::Player);
	CheckLayer(Layer::Tile, Layer::Player);
}

void CCollisionManager::Update()
{
	for (int left = 0; left < (int)Layer::Size; left++)
	{
		for (int right = left; right < (int)Layer::Size; right++)
		{
			if (m_arrLayer[left][right])
			{
				// �浹 Ȯ�� ����
				CollisionUpdate((Layer)left, (Layer)right);
			}
		}
	}
}

void CCollisionManager::Release()
{
}

void CCollisionManager::CollisionUpdate(Layer leftLayer, Layer rightLayer)
{
	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& leftListObj = pCurScene->m_listObj[(int)leftLayer];
	const list<CGameObject*>& rightListObj = pCurScene->m_listObj[(int)rightLayer];

	for (CGameObject* pLeftObj : leftListObj)
	{
		// �浹ü ������Ʈ�� ���� ��� ����
		if (nullptr == pLeftObj->GetCollider())
			continue;

		for (CGameObject* pRightObj : rightListObj)
		{
			// �浹ü ������Ʈ�� ���� ��� ����
			if (nullptr == pRightObj->GetCollider())
				continue;

			// �ڱ� �ڽŰ��� �浹�� ����
			if (pLeftObj == pRightObj)
				continue;

			// �浹ü�� �浹ü�� ID Ȯ��
			CCollider* pLeftCollider = pLeftObj->GetCollider();
			CCollider* pRightCollider = pRightObj->GetCollider();
			UINT64 id = CollisionID(pLeftCollider->GetID(), pRightCollider->GetID());

			// �浹 ������ ������ ���, �浹���� ���� ���·� ����
			if (m_umapPrevCollision.find(id) == m_umapPrevCollision.end())
				m_umapPrevCollision.insert(make_pair(id, false));
			
			// �浹ó�� Ȯ��
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// Prev O, Cur O
				if (m_umapPrevCollision[id])
				{
					// �浹ü �� �ϳ��� ���������� ��� �浹 ����
					if (pLeftObj->GetReserveDelete() || pRightObj->GetReserveDelete())
					{
						pLeftCollider->OnCollisionExit(pRightCollider);
						pRightCollider->OnCollisionExit(pLeftCollider);
						m_umapPrevCollision[id] = false;
					}
					else
					{
						pLeftCollider->OnCollisionStay(pRightCollider);
						pRightCollider->OnCollisionStay(pLeftCollider);
						m_umapPrevCollision[id] = true;
					}
				}
				// Prev X, Cur O
				else
				{
					// �浹ü �� �ϳ��� ���������� ��� �浹��Ű�� ����
					if (pLeftObj->GetReserveDelete() || pRightObj->GetReserveDelete())
					{
						// �ƹ��͵� ���� ����
					}
					else
					{
						pLeftCollider->OnCollisionEnter(pRightCollider);
						pRightCollider->OnCollisionEnter(pLeftCollider);
						m_umapPrevCollision[id] = true;
					}
				}
			}
			else
			{
				// Prev O, Cur X
				if (m_umapPrevCollision[id])
				{
					pLeftCollider->OnCollisionExit(pRightCollider);
					pRightCollider->OnCollisionExit(pLeftCollider);
					m_umapPrevCollision[id] = false;
				}
				// Prev X, Cur X
				else
				{
					m_umapPrevCollision[id] = false;
				}
			}
		}
	}
}

bool CCollisionManager::IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider)
{
	ColliderType leftType = pLeftCollider->GetType();
	ColliderType rightType = pRightCollider->GetType();
	
	if (leftType == ColliderType::Rect && rightType == ColliderType::Rect)
	{
		return RectCollision(
			pLeftCollider->GetPos(),
			pLeftCollider->GetScale(), 
			pRightCollider->GetPos(),
			pRightCollider->GetScale()
		);
	}
	else if (leftType == ColliderType::Circle && rightType == ColliderType::Circle)
	{
		return CircleCollision(
			pLeftCollider->GetPos(),
			pLeftCollider->GetScale().x,
			pRightCollider->GetPos(),
			pRightCollider->GetScale().x
		);
	}
	else if (leftType == ColliderType::Rect && rightType == ColliderType::Circle)
	{
		return RectCircleCollision(
			pLeftCollider->GetPos(),
			pLeftCollider->GetScale(),
			pRightCollider->GetPos(),
			pRightCollider->GetScale().x
		);
	}
	else if (leftType == ColliderType::Circle && rightType == ColliderType::Rect)
	{
		return RectCircleCollision(
			pRightCollider->GetPos(),
			pRightCollider->GetScale(),
			pLeftCollider->GetPos(),
			pLeftCollider->GetScale().x
		);
	}
	else
	{
		return false;
	}
}

bool CCollisionManager::RectCollision(Vector leftPos, Vector leftScale, Vector rightPos, Vector rightScale)
{
	// �簢 �浹 : �簢���� �������� �Ÿ��� ũ������ �ݺ��� ���� ��� �浹�Ѵ�
	if (abs(leftPos.x - rightPos.x) < (leftScale.x + rightScale.x) / 2.f
		&& abs(leftPos.y - rightPos.y) < (leftScale.y + rightScale.y) / 2.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCollisionManager::CircleCollision(Vector leftPos, float leftScale, Vector rightPos, float rightScale)
{
	// �� �浹 : ���� �������� �Ÿ����� �������� �պ��� ���� ��� �浹�Ѵ�
	if (pow(leftPos.x - rightPos.x, 2) + pow(leftPos.y - rightPos.y, 2)
		< pow(leftScale + rightScale, 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCollisionManager::RectCircleCollision(Vector rectPos, Vector rectScale, Vector circlePos, float circleScale)
{
	int totalPoint, xPoint, yPoint;
	// �簢 �� �浹 : �簢���� �߽����� ���� ��� ������ �ִ��Ŀ� ���� �ٸ��� ó��
	/*	totalPoint (xPoint, yPoint)

		-4 (-1,-1) | -3 ( 0,-1) | -2 (+1,-1)
		-----------+------------+-----------
		-1 (-1, 0) |  0 ( 0, 0) | +1 (+1, 0)
		-----------+------------+-----------
		+2 (-1,+1) | +3 ( 0,+1) | +4 (+1,+1)
	*/
	if (circlePos.x < rectPos.x - rectScale.x * 0.5f)
		xPoint = -1;
	else if (circlePos.x > rectPos.x + rectScale.x * 0.5f)
		xPoint = 1;
	else
		xPoint = 0;

	if (circlePos.y < rectPos.y - rectScale.y * 0.5f)
		yPoint = -1;
	else if (circlePos.y > rectPos.y + rectScale.y * 0.5f)
		yPoint = 1;
	else
		yPoint = 0;

	totalPoint = 3 * yPoint + xPoint;

	switch (totalPoint)
	{
	// �簢�� �ȿ� ���� ���� ��� : �׻� �浹
	case 0:
		return true;
		break;
	// �¿쿡 ���� ���� ��� : �簢���� ���� ũ�� + ���� �������� �ѻ����� �Ÿ����� ������� �浹
	case -1:
	case +1:
		if (abs(rectPos.x - circlePos.x) < rectScale.x * 0.5f + circleScale)
			return true;
		break;
	// ���Ͽ� ���� ���� ��� : �簢���� ���� ũ�� + ���� �������� �ѻ����� �Ÿ����� ������� �浹
	case -3:
	case +3:
		if (abs(rectPos.y - circlePos.y) < rectScale.y * 0.5f + circleScale)
			return true;
		break;
	// �簢���� �밢���� ���� ���� ��� : �簢���� �ڳʰ� �� �ȿ� ���� ��� �浹
	case -4:
	case -2:
	case +2:
	case +4:
	{
		float cornerX = (xPoint < 0) ? rectPos.x - rectScale.x * 0.5f : rectPos.x + rectScale.x * 0.5f;
		float cornerY = (yPoint < 0) ? rectPos.y - rectScale.y * 0.5f : rectPos.y + rectScale.y * 0.5f;
		if (pow(cornerX - circlePos.x, 2) + pow(cornerY - circlePos.y, 2)
			< pow(circleScale, 2))
			return true;
		break;
	}
	}

	return false;
}

void CCollisionManager::CheckLayer(Layer left, Layer right)
{
	m_arrLayer[(int)left][(int)right] = true;
	m_arrLayer[(int)right][(int)left] = true;
}

void CCollisionManager::UnCheckLayer(Layer left, Layer right)
{
	m_arrLayer[(int)left][(int)right] = false;
	m_arrLayer[(int)right][(int)left] = false;
}

void CCollisionManager::ResetCheck()
{
	// memset(�����ּ�, ������ ������, ������ ũ��) : �޸� �ʱ�ȭ �Լ�
	memset(m_arrLayer, 0, sizeof(bool) * (int)Layer::Size * (int)Layer::Size);
	/*
	for (bool check : m_arrCheckLayer)
	{
		check = false;
	}
	*/
}

UINT64 CCollisionManager::CollisionID(UINT leftID, UINT rightID)
{
	UINT64 result = 0;
	if (leftID < rightID)
	{
		result |= (UINT64)leftID << 32;
		result |= rightID;
		return result;
	}
	else
	{
		result |= (UINT64)rightID << 32;
		result |= leftID;
		return result;
	}
}
