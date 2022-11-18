#pragma once
#include "CGameObject.h"
class CImage;
class CAnimator;

class CMonsterTurret : public CGameObject
{
public:
	CMonsterTurret();
	virtual ~CMonsterTurret();

private:
	CImage* m_MonImg;
	CAnimator* m_pAnimator;
	
	Vector m_vecDir;

	bool m_bIsShot;
	bool m_bOnGround;
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

