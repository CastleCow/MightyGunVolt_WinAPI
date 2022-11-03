#pragma once
#include "WinAPI.h"

class CEventManager;
class CCollisionManager;
class CScene;
class CComponent;
class CCollider;
enum class ColliderType;

// ���ӿ�����Ʈ : 
// �� ���� �����ϴ� ��ü, ex) ĳ����, �̻���, ����, ������, ��
// ���ӿ�����Ʈ�� ĸ��ȭ�Ͽ� �ൿ�� ǥ���� ������ ���
// �ٸ� ���ӿ�����Ʈ�� ���������� ������ �� ����
class CGameObject
{
	friend CEventManager;
	friend CCollisionManager;
	friend CScene;
	friend CCollider;
public:
	CGameObject();
	virtual ~CGameObject();

protected:
	Vector m_vecPos;	// ���ӿ�����Ʈ�� ��ġ
	Vector m_vecScale;	// ���ӿ�����Ʈ�� ũ��
	Layer m_layer;		// ���ӿ�����Ʈ�� ���̾�
	wstring m_strName;	// ���ӿ�����Ʈ�� �̸�

public:
	Vector GetPos();
	void SetPos(Vector pos);
	void SetPos(float x, float y);
	Vector GetScale();
	void SetScale(Vector scale);
	void SetScale(float x, float y);
	Layer GetLayer();
	void SetLayer(Layer layer);
	wstring GetName();
	void SetName(wstring name);

private:
	bool m_bReservedDelete;		// ���ӿ�����Ʈ�� ������������ ����
	bool m_bSafeToDelete;		// ���ӿ�����Ʈ�� �����ص� ���������� ����

	void SetReserveDelete();	// ���ӿ�����Ʈ ���� ����
	bool GetSafeToDelete();		// ���ӿ�����Ʈ ���� ���� ���� Ȯ��
	void SetSafeToDelete();		// ���ӿ�����Ʈ ���� ���� ���� ǥ��
public:
	bool GetReserveDelete();		// ���ӿ�����Ʈ�� ������������ Ȯ��

protected:
	list<CComponent*> m_listComponent;	// ������Ʈ���� ������ �ڷᱸ��

	void AddComponent(CComponent* component);		// ������Ʈ �߰�
	void RemoveComponent(CComponent* component);	// ������Ʈ ����

	void ComponentRender();

	// �浹 ������Ʈ
private:
	CCollider* m_pCollider;

protected:
	CCollider* GetCollider();
	void AddCollider(ColliderType type, Vector scale, Vector offsetPos);
	void RemoveCollider();

	virtual void OnCollisionEnter(CCollider* pOtherCollider) {};	// �浹üũ�� Ȯ���ϴ� ������Ʈ�� �������Ͽ� ���
	virtual void OnCollisionStay(CCollider* pOtherCollider) {};	// �浹üũ�� Ȯ���ϴ� ������Ʈ�� �������Ͽ� ���
	virtual void OnCollisionExit(CCollider* pOtherCollider) {};	// �浹üũ�� Ȯ���ϴ� ������Ʈ�� �������Ͽ� ���

protected:
	// ���ӿ�����Ʈ �θ� ���� �Լ��� :
	// ���ӿ�����Ʈ�� �ִ� ��� ������Ʈ���� ����
	virtual void GameObjectInit();
	virtual void GameObjectUpdate();
	virtual void GameObjectPhysicsUpdate();
	virtual void GameObjectRender();
	virtual void GameObjectRelease();

	// ���������Լ�:
	// �Լ��� �߻�ȭ�Ͽ� ��üȭ���� ���� ��� �ν��Ͻ� ������ ����
	// ���ӿ�����Ʈ�� ��ӹ޾� ���������Լ����� ��üȭ���� ���ӿ�����Ʈ�� �ϼ���Ŵ
	virtual void Init() = 0;		// �ʱ�ȭ
	virtual void Update() = 0;		// ���ӿ�����Ʈ�� �ൿ����
	virtual void Render() = 0;		// ���ӿ�����Ʈ�� ǥ������
	virtual void Release() = 0;		// ������
};
