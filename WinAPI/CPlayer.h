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
	Skill,
};
enum class Ground {
	Ceiling,
	Air,
	Ground
};
class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

	float GetHP() { return m_HP; }
	void SetHP(float a) { m_HP = a; }
	void SetState(PlayerState State) { this->State = State; }
private:
	CAnimator* m_pAnimator;
	CImage* m_pImage;
	CImage* m_pImageRV;

	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	PlayerState State;
	Ground gState;
	bool m_bIsMove;
	bool m_bIsJump;
	bool m_bIsDead;
	bool m_bIsAttack;

	float m_fSpeed = 200.0f;
	float m_HP=20;
	float Timer = 0;
	float JumpTimer = 0;
	float IntroTimer = 0;
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


	void Idle();
	void Move(const int key);
	void Jump();
	void Fall();
	void Attack();
	void Skill();
	void Dead();
	void Reset();
};