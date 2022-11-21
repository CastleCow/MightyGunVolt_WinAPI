#pragma once
#include "CGameObject.h"
class CImage;
class CAnimator;
enum class BotState {
	Idle,
	Missile,
	Spark,
};
class CMonsterMissileBot : public CGameObject
{
public:
	CMonsterMissileBot();
	virtual ~CMonsterMissileBot();

private:
	CImage* m_MonImg;
	CAnimator* m_pAnimator;
	BotState BS;
	bool m_bIsHit;
	bool m_bIsShot;
	float m_fIsAttacked;
	float m_fHP;
	float m_fTimer;
private:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	void AnimatorUpdate();
	void CreateMissile();
};

