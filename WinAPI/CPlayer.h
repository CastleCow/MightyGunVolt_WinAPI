#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;
class CPlayerSkill;
class CLightningSphere;
class CSparkCaliver;
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

	
private:
	CAnimator* m_pAnimator;
	CImage* m_pImage;
	CImage* m_pImageRV;

	CPlayerSkill* skillOn;
	CLightningSphere* LiSp;
	CSparkCaliver* SpCal;

	Vector m_vecReset;
	PlayerState State;
	Ground gState;
	bool m_bIsMove;
	bool m_bIsJump;
	bool m_bIsDJump;
	bool m_bIsDead;
	bool m_bIsAttack;
	bool m_bIsSkillSel=false;

	float m_fSpeed = 200.0f;
	float m_fFallSpeed = 200.0f;
	float m_HP=20;
	float Timer = 0;
	float JumpTimer = 0;
	float IntroTimer = 0;
	float Mp = 6;
protected:
	Vector m_vecMoveDir;
	Vector m_vecLookDir;
private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
	void CreateMissile();
	void SparkCaliber();
	void LightningSphere();
	void SkillTurnOn();

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

public:
	float GetHP() { return m_HP; }
	void SetHP(float a) { m_HP = a; }
	float GetMp() { return Mp; }
	void SetMp(float a) { Mp = a; }
	void SetState(PlayerState State) { this->State = State; }
	void SetResetPos(Vector a) { m_vecReset = a; }

};