#pragma once

class CGameObject;

// ���������� ������Ʈ - ������Ʈ : 
// ���α׷��ֿ� �־� ��� ������ ������ ������ ������ ���
// ��ü�� ������ ��� ������ ����� ���������� �����ϴ� ������ ���
// ����� ��� ��� ����ϴ� �ڽĿ��� �ݵ�� ����� ���Ե�����
// ������Ʈ�� ��� �ʿ��� ��ü���� ���������� ���� �� ����
class CComponent
{
	friend CGameObject;
public:
	CComponent();
	virtual ~CComponent();

private:
	CGameObject* m_pOwner;

private:
	void SetOwner(CGameObject* pOwner);

public:
	CGameObject* GetOwner();

private:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void PhysicsUpdate(){};		// ����ó���� �ʿ��� ������Ʈ�� �������Ͽ� ���
	virtual void Render() = 0;
	virtual void Release() = 0;
};

