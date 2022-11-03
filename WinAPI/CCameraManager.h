#pragma once

class CCore;
class CGameObject;

class CCameraManager : public SingleTon<CCameraManager>
{
	friend SingleTon<CCameraManager>;
	friend CCore;
private:
	CCameraManager();
	virtual ~CCameraManager();

private:
	Vector			m_vecLookAt;		// ī�޶� ���� �����ִ� ��ġ
	Vector			m_vecTargetPos;		// ī�޶��� ��ǥ ��ġ
	CGameObject*	m_pTargetObj;		// ī�޶� ������ ������Ʈ

	float			m_fTimeToTarget;	// ī�޶� ���������� ���µ� �����ð�

	float			m_fTargetBright;	// ī�޶��� ��ǥ ���
	float			m_fCurBright;		// ī�޶��� ���� ���
	float			m_fTimeToBright;	// ī�޶��� ��� ��ȭ �����ð�

public:
	Vector			GetLookAt();
	Vector			GetTargetPos();
	CGameObject*	GetTargetObj();

	// ������Ʈ�� ������ ��� ��ǥ��ġ�� ��ǥ ������Ʈ�� ��ġ�� ������
	void SetTargetPos(Vector targetPos, float timeToTarget = 0);	// ī�޶��� ��ǥ ��ġ ����
	void SetTargetObj(CGameObject* pTargetObj);						// ī�޶��� ��ǥ ������Ʈ ����

	Vector WorldToScreenPoint(Vector worldPoint);	// ������ġ->ȭ����ġ
	Vector ScreenToWorldPoint(Vector screenPoint);	// ȭ����ġ->������ġ

	void Scroll(Vector dir, float velocity);		// ī�޶� ��ũ��

	void FadeIn(float duration);		// �� ���� ȿ��
	void FadeOut(float duration);		// �� Ż�� ȿ��

private:
	void Init();
	void Update();
	void Render();
	void Release();

private:
	void MoveToTarget();
	void RenderEffect();
};

#define CAMERA	CCameraManager::GetInstance()