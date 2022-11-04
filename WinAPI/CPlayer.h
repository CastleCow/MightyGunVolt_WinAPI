#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;
enum class PlayerState {
	Dead,
	Idle,
	Move,
	Attack,
	Jump,
	Jump2,
	Fall,
};
class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	CAnimator* m_pAnimator;
	CImage* m_pImage;
	CImage* m_pImageRV;

	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	PlayerState State;
	bool m_bIsMove;

	float m_fSpeed = 200.0f;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
	void CreateMissile();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};