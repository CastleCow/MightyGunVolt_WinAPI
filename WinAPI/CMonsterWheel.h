#pragma once
#include "CGameObject.h"
class CImage;
class CAnimator;

class CMonsterWheel : public CGameObject
{
public:
	CMonsterWheel();
	virtual ~CMonsterWheel();

private:
	CImage* m_MonImg;
	CAnimator* m_pAnimator;
	
	bool m_bIsHit;
	bool m_bOnGround;
	float m_fIsAttacked;
	float m_fHP;
	float m_fTimer;

	Vector m_vecDir;
private:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	void AnimatorUpdate();
	void Fall();
};

