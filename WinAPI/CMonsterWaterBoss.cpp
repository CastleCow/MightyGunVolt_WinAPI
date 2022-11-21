#include "framework.h"
#include "CMonsterWaterBoss.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CBossBullet.h"
#include "CDeadExplo.h"
CMonsterWaterBoss::CMonsterWaterBoss()
{
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
	m_strName = L"몬스터";
	m_MonImg = nullptr;
	m_pAnimator = nullptr;
	m_bIsHit = false;
	m_fIsAttacked;
	bulletCount = 0.f;
	m_fHP=50;
	patNum = 0;
}

CMonsterWaterBoss::~CMonsterWaterBoss()
{
}

void CMonsterWaterBoss::Init()
{
	srand(time(NULL));
	GAME->SetBossScale(m_vecScale);
	m_MonImg = RESOURCE->LoadImg(L"No.2Cyro",L"Image\\Monster\\BOSS_MWATER.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"EntryRight", m_MonImg, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,2);
	m_pAnimator->CreateAnimation(L"EntryLeft", m_MonImg, Vector(0.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,2);
	
	m_pAnimator->CreateAnimation(L"IdleRight", m_MonImg, Vector(300.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_MonImg,  Vector(300.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3);
	
	m_pAnimator->CreateAnimation(L"JumpRight", m_MonImg, Vector(750.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"JumpLeft", m_MonImg,  Vector(750.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"FallRight", m_MonImg, Vector(1050.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"FallLeft", m_MonImg,  Vector(1050.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);

	m_pAnimator->CreateAnimation(L"SummonRight", m_MonImg, Vector(1200.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 4);
	m_pAnimator->CreateAnimation(L"SummonLeft", m_MonImg,  Vector(1200.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 4);

	m_pAnimator->CreateAnimation(L"BattingRight", m_MonImg, Vector(0.f, 250.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 5);
	m_pAnimator->CreateAnimation(L"BattingLeft", m_MonImg,  Vector(0.f, 400.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 5);

	m_pAnimator->CreateAnimation(L"HammerJumpRight", m_MonImg, Vector(750.f, 250.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);
	m_pAnimator->CreateAnimation(L"HammerJumpLeft", m_MonImg,  Vector(750.f, 400.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);
	m_pAnimator->CreateAnimation(L"HammerFallRight", m_MonImg, Vector(1050.f, 250.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);
	m_pAnimator->CreateAnimation(L"HammerFallLeft", m_MonImg,  Vector(1050.f, 400.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);

	m_pAnimator->CreateAnimation(L"HitRight", m_MonImg, Vector(1350.f, 250.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"HitLeft", m_MonImg,  Vector(1350.f, 400.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);

	m_pAnimator->CreateAnimation(L"FinshRight", m_MonImg, Vector(0.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3,false);
	m_pAnimator->CreateAnimation(L"FinshLeft",  m_MonImg, Vector(0.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3,false);

	m_pAnimator->CreateAnimation(L"FinshLoopRight", m_MonImg, Vector(450.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"FinshLoopLeft", m_MonImg,  Vector(450.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"FinshLoopEndRight", m_MonImg, Vector(150.f*11.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);
	m_pAnimator->CreateAnimation(L"FinshLoopEndLeft", m_MonImg,  Vector(150.f*11.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);

	AddComponent(m_pAnimator);
	m_pAnimator->Play(L"EntryLeft", false);
	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0),2.f);
	
	
}

void CMonsterWaterBoss::Update()
{
	GAME->SetBossPos(m_vecPos);

	CountBullet();
	patNum = rand() % 3;
	Vector metoP = m_vecPos - PLAYERPOS;


	if (bulletCount < 1.f)
	{
		State = BossState::Pattern1;
	}
	else if (m_fHP < 15.f)
	{
		State = BossState::Pattern4;
	}
	else if (m_fHP < 0.f)
		State = BossState::Dead;


	switch (State)
	{
	case BossState::Dead:
		CDeadExplo* expl = new CDeadExplo;
		expl->SetPos(m_vecPos);
		if (expl == nullptr)
			DELETEOBJECT(this);
		break;
	case BossState::Idle:
	{

	}
		break;
	case BossState::Pattern1:
	{
		Pattern1();
	}
		break;
	case BossState::Pattern2:
	{
		Pattern2();
	}break;
	case BossState::Pattern3:
	{
		Pattern3();
	}
		break;
	case BossState::Pattern4:
	{
		Pattern4();
	}
		break;

	default:
		break;
	}
	

	/*if (m_fIsAttacked > 0)
	{
		m_fIsAttacked -= 10*DT;
		m_vecPos += metoP.Normalized() * 150 * DT;
	}
	else if (m_bIsHit)
	{
		if (m_fTimer > 0)
		{
			m_fTimer -= DT;
			m_vecPos += metoP.Normalized() * 200 * DT;

		}
		else
		{
			m_bIsHit = false;
		}
	}
	else if(metoP.x<200&&
		metoP.y<200)
	m_vecPos -=metoP.Normalized() * 100 * DT;
*/

	if (m_fHP <= 0)
		DELETEOBJECT(this);
	AnimatorUpdate();
}

void CMonsterWaterBoss::Render()
{
	

}

void CMonsterWaterBoss::Release()
{
}

void CMonsterWaterBoss::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 충돌진입");
		m_bIsHit = true;
		m_fTimer = 2.f;
	}
	else if (pOtherCollider->GetObjName() == L"미사일")
	{
		Logger::Debug(L"몬스터가 미사일과 충돌진입");
		m_fIsAttacked++;
		m_fHP--;
	}
}

void CMonsterWaterBoss::OnCollisionStay(CCollider* pOtherCollider)
{
	gState = Ground::Air;
	if (pOtherCollider->GetObjName() == L"땅")
	{
		Logger::Debug(L"땅과 플레이어와 충돌중");
		if (pOtherCollider->GetPos().y < m_vecPos.y)
			gState = Ground::Ceiling;
		else if (pOtherCollider->GetPos().y > m_vecPos.y)
		{
			gState = Ground::Ground;
			if (m_vecPos.y > pOtherCollider->GetPos().y - pOtherCollider->GetScale().y + 4)
				m_vecPos.y = pOtherCollider->GetPos().y - pOtherCollider->GetScale().y + 4;
		}
	}
}

void CMonsterWaterBoss::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 충돌해제");
	}
	else if (pOtherCollider->GetObjName() == L"미사일")
	{
		Logger::Debug(L"몬스터가 미사일과 충돌해제");
	}
}

void CMonsterWaterBoss::AnimatorUpdate()
{
	wstring str=L"";
	switch (State)
	{
	case BossState::Dead:
		break;
	case BossState::Idle:
	{

	}
	break;
	case BossState::Pattern1:
	{

	}
	break;
	case BossState::Pattern2:
	{

	}break;
	case BossState::Pattern3:
	{

	}
	break;
	case BossState::Pattern4:
	{

	}
	break;

	default:
		break;
	}
	if (m_vecPos.x <= PLAYERPOS.x)
		str += L"Right";
	else str += L"Left";

	m_pAnimator->Play(str, false);
}

void CMonsterWaterBoss::CreateBullet()
{
	Bul1 = new CBossBullet;
	Bul1->SetPos(Vector(m_vecPos.x-20,m_vecPos.y));
	ADDOBJECT(Bul1);
	bulletCount++;
	
	Bul2 = new CBossBullet;
	Bul2->SetPos(Vector(m_vecPos.x-20,m_vecPos.y-20));
	ADDOBJECT(Bul2);
	bulletCount++;
	
	Bul3 = new CBossBullet;
	Bul3->SetPos(Vector(m_vecPos.x-20,m_vecPos.y+20));
	ADDOBJECT(Bul3);
	bulletCount++;
	
	Bul4 = new CBossBullet;
	Bul4->SetPos(Vector(m_vecPos.x+20,m_vecPos.y));
	ADDOBJECT(Bul4);
	bulletCount++;
	
	Bul5 = new CBossBullet;
	Bul5->SetPos(Vector(m_vecPos.x+20,m_vecPos.y-20));
	ADDOBJECT(Bul5);
	bulletCount++;
	
	Bul6 = new CBossBullet;
	Bul6->SetPos(Vector(m_vecPos.x+20,m_vecPos.y+20));
	ADDOBJECT(Bul6);
	bulletCount++;

}
void CMonsterWaterBoss::CountBullet()
{
	if(bulletCount>0)
	{
		if (Bul1 == nullptr)
			bulletCount--;
		else if (Bul2 == nullptr)
		 	bulletCount--;
		else if (Bul3 == nullptr)
		 	bulletCount--;
		else if (Bul4 == nullptr)
		 	bulletCount--;
		else if (Bul5 == nullptr)
		 	bulletCount--;
		else if (Bul6 == nullptr)
			bulletCount--;
	}
}

void CMonsterWaterBoss::Pattern1()
{

}
void CMonsterWaterBoss::Pattern2() 
{

}
void CMonsterWaterBoss::Pattern3()
{

}
void CMonsterWaterBoss::Pattern4()
{
	if (m_vecPos.x != WINSIZEX * 0.5f && m_vecPos.y != WINSIZEY * 0.5f)
	{
		m_vecPos += Vector(WINSIZEX * 0.5f - m_vecPos.x, WINSIZEY * 0.5f - m_vecPos.y).Normalized()*50.f * DT;

	}
}