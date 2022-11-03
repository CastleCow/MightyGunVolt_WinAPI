#pragma once
#include "CComponent.h"

class CCollisionManager;
class CGameObject;

enum class ColliderType { Rect, Circle };

class CCollider : public CComponent
{
	friend CCollisionManager;
	friend CGameObject;
public:
	CCollider();
	virtual ~CCollider();

private:
	static UINT s_uiID;		// ��� �浹ü�� �����ϴ� ID ��
	UINT m_uiID;			// �浹ü�� ���� ID ��
	UINT m_uiCollisionCount;// �浹���� �浹ü ����

	ColliderType m_type;	// �浹ü�� Ÿ��
	Vector m_vecPos;		// �浹ü�� ��ġ
	Vector m_vecOffsetPos;	// �浹ü�� ������(������)
	Vector m_vecScale;		// �浹ü�� ũ��

private:
	void SetType(ColliderType type);
	void SetPos(Vector pos);
	void SetOffsetPos(Vector offset);
	void SetScale(Vector scale);

public:
	ColliderType GetType();
	wstring GetObjName();
	UINT GetID();
	Vector GetPos();
	Vector GetOffsetPos();
	Vector GetScale();

private:
	void Init() override;
	void Update() override;
	void PhysicsUpdate() override;	// �浹ü�� ����ó��
	void Render() override;
	void Release() override;

	// �浹 ���� �Լ�
private:
	void OnCollisionEnter(CCollider* pOtherCollider);	// �浹����
	void OnCollisionStay(CCollider* pOtherCollider);	// �浹��
	void OnCollisionExit(CCollider* pOtherCollider);	// �浹Ż��
};

