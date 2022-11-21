#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;
class CMonsterMissileBotMissile : public CGameObject
{
public:
	CMonsterMissileBotMissile();
	virtual ~CMonsterMissileBotMissile();

private:
	Vector m_vecDir;
	CAnimator* m_pAnimator;
	CImage* m_Image;
	CImage* m_ImageRV;
	float m_fVelocity;
	float bulDelTime;
	float Dir[2];

	bool bulenhace ;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();

	void OnCollisionEnter(CCollider* pOtherCollider) override;

public:
	void SetDir(Vector dir);
	void SetVelocity(float velocity);
	void SetBul(bool a) { bulenhace = a; }
	//int GetCount() { return count; }
};