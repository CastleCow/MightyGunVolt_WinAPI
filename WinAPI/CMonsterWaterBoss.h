#pragma once
#include "CGameObject.h"
class CImage;
class CAnimator;
class CBossBullet;

enum class BossState {
	Dead,
	Idle,
	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4,

	Size,
};
enum class BossGround {
	Ceiling,
	Air,
	Ground
};

class CMonsterWaterBoss : public CGameObject
{
public:
	CMonsterWaterBoss();
	virtual ~CMonsterWaterBoss();

private:
	CImage* m_MonImg;
	CAnimator* m_pAnimator;

	CBossBullet* Bul1;
	CBossBullet* Bul2;
	CBossBullet* Bul3;
	CBossBullet* Bul4;
	CBossBullet* Bul5;
	CBossBullet* Bul6;


	BossState State;
	BossState PrevState;
	BossGround gState;

	bool m_bIsHit;
	bool m_bIsPatterning;
	bool m_bIsCrBul;
	float m_fIsAttacked;
	float m_fHP;
	float m_fTimer;
	float m_deadTimer;
	float m_fEntryTimer;
	
	float bulletCount;
	float m_fPatternTimer;
	int patNum;
private:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	void AnimatorUpdate();

	void Pattern1();
	void Pattern2();
	void Pattern3();
	void Pattern4();


	void CreateBullet();
	void CountBullet();
};

/*
패턴1 
탄환이 2개 이하일때 
기존의 물탄환을 삭제하고 
점프 후 소환 애니메이션 이후 6개의 물탄환을 생성함
물 탄환은 보스를 중심으로 시계 방향으로 회전함
	
해당물탄환은 플레이어 탄환을 튕겨넴

패턴 2 
플레이어를 향해 탄환을 얼음탄으로 바꿔사출함 

패턴 3 
망치 들고 점프 후 땅까지 내려찍기 낙하속도 2배 데미지3

발악기 HP<MaxHP*0.3f
패턴 4
중앙으로 점프 


*/