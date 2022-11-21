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
enum class Ground {
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
	Ground gState;

	bool m_bIsHit;
	float m_fIsAttacked;
	float m_fHP;
	float m_fTimer;
	float m_deadTimer;
	float bulletCount;

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
����1 
źȯ�� 2�� �����϶� 
������ ��źȯ�� �����ϰ� 
���� �� ��ȯ �ִϸ��̼� ���� 6���� ��źȯ�� ������
�� źȯ�� ������ �߽����� �ð� �������� ȸ����
	
�ش繰źȯ�� �÷��̾� źȯ�� ƨ�ܳ�

���� 2 
�÷��̾ ���� źȯ�� ����ź���� �ٲ������ 

���� 3 
��ġ ��� ���� �� ������ ������� ���ϼӵ� 2�� ������3

�߾Ǳ� HP<MaxHP*0.3f
���� 4
�߾����� ���� 


*/