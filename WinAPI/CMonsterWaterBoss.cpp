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
	m_bIsPatterning = false;
	m_bIsCrBul = false;
	m_fIsAttacked;
	bulletCount = 0.f;
	m_fHP=30;
	patNum = 0;
	m_fPatternTimer = 4.f;
	m_fEntryTimer = 0.f;
	gState = BossGround::Air;
	Bul1=nullptr;
	Bul2=nullptr;
	Bul3=nullptr;
	Bul4=nullptr;
	Bul5=nullptr;
	Bul6=nullptr;
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
	m_pAnimator->CreateAnimation(L"EntryRight", m_MonImg, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.5f,2);
	m_pAnimator->CreateAnimation(L"EntryLeft", m_MonImg, Vector(0.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.5f,2);
	
	m_pAnimator->CreateAnimation(L"IdleRight", m_MonImg, Vector(300.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.4f, 3);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_MonImg,  Vector(300.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.4f, 3);

	m_pAnimator->CreateAnimation(L"JumpRight", m_MonImg, Vector(750.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2  ,false);
	m_pAnimator->CreateAnimation(L"JumpLeft", m_MonImg,  Vector(750.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);
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
	AddCollider(ColliderType::Rect, Vector(45, 45), Vector(0, 0),2.f);
	
	
}

void CMonsterWaterBoss::Update()
{
	m_fEntryTimer += DT;
	GAME->SetBossPos(m_vecPos);
	Vector metoP = PLAYERPOS - m_vecPos;
	CountBullet();
	float m_fFallSpeed = 200.0f;
	if (gState == BossGround::Air)
	{
		float Speed = m_fFallSpeed;
		Speed += m_fFallSpeed * DT;
		m_vecPos.y += (Speed)*DT;
	}
	if(m_fEntryTimer>2.f)
	{
		if (m_bIsPatterning)//패턴진행
		{
			if (m_fPatternTimer > 0)//패턴 시간 동안 패턴 행동만 함
			{
				m_fPatternTimer -= DT;
				switch (State)
				{
				case BossState::Dead:
				{
					CDeadExplo* expl = new CDeadExplo;
					expl->SetPos(m_vecPos);
					ADDOBJECT(expl);
					if (expl == nullptr)
						DELETEOBJECT(this);
					break;
				}
				case BossState::Idle:
				{
					if (m_fPatternTimer > 2.f)
					{
						m_vecPos += metoP.Normalized() * 20 * DT;
					}
					else
					{
						m_vecPos -= metoP.Normalized() * 20 * DT;
					}
					break;
				}
				case BossState::Pattern1:
				{
					Pattern1();
					break;
				}
				case BossState::Pattern2:
				{
					Pattern2();
					break;
				}
				case BossState::Pattern3:
				{
					Pattern3();
					break;
				}
				case BossState::Pattern4:
				{
					Pattern4();
					break;
				}

				default:
					break;
				}


			}
			else
			{
				m_bIsPatterning = false;
				State = BossState::Idle;

			}
		}
		//패턴선택
		else//패턴 선택
		{
			patNum = rand() % 4;
			if (patNum == 0)
			{
				Logger::Debug(L"패턴1");
				State = BossState::Pattern1;
				m_fPatternTimer = 3.f;
				m_bIsPatterning = true;
				m_bIsCrBul = false;
				if(Bul1!=nullptr)
				{
					Bul1->SetDelete(true);
					Bul2->SetDelete(true);
					Bul3->SetDelete(true);
					Bul4->SetDelete(true);
					Bul5->SetDelete(true);
					Bul6->SetDelete(true);
				}
			}
			else if (patNum == 1)
			{
				Logger::Debug(L"패턴2");
				State = BossState::Pattern2;
				m_fPatternTimer = 3.f;
				m_bIsPatterning = true;
			}
			else if (patNum == 2)
			{
				Logger::Debug(L"패턴3");
				State = BossState::Pattern3;
				m_fPatternTimer = 2.f;
				m_bIsPatterning = true;
			}
			else if (patNum == 3 && m_fHP < 10.f)
			{
				Logger::Debug(L"패턴4");
				State = BossState::Pattern4;
				m_fPatternTimer = 3.f;
				m_bIsPatterning = true;
			}
			else
			{
				Logger::Debug(L"아이들링");
				State = BossState::Idle;
				m_fPatternTimer = 3.f;
				m_bIsPatterning = true;
			}

		}
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
		m_fHP-=pOtherCollider->GetDamage();
	}
	else if (pOtherCollider->GetObjName() == L"스킬")
		m_fHP-=pOtherCollider->GetDamage();
}

void CMonsterWaterBoss::OnCollisionStay(CCollider* pOtherCollider)
{
	gState = BossGround::Air;
	if (pOtherCollider->GetObjName() == L"땅")
	{
		//Logger::Debug(L"땅과 플레이어와 충돌중");
		if (pOtherCollider->GetPos().y < m_vecPos.y)
			gState = BossGround::Ceiling;
		else if (pOtherCollider->GetPos().y > m_vecPos.y)
		{
			gState = BossGround::Ground;
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
	if (m_fEntryTimer < 2.f)
		str += L"Entry";
	else {
		switch (State)
		{
		case BossState::Dead:
			str += L"Hit";
			break;
		case BossState::Idle:
		{
			str += L"Idle";
		}
		break;
		case BossState::Pattern1:
		{
			if (2.f <= m_fPatternTimer &&
				m_fPatternTimer <= 3.f)
			{
				str += L"Jump";
			}
			//탄환 생성
			if (1.5f <= m_fPatternTimer &&
				m_fPatternTimer < 2.f)
			{
				str += L"Summon";
			}
			//내려오고 패턴 종료
			if (
				m_fPatternTimer < 1.5f)
			{
				str += L"Fall";
			}
		}
		break;
		case BossState::Pattern2:
		{
			if(m_fPatternTimer<=3.f)
			str += L"Batting";
		}
		break;
		case BossState::Pattern3:
		{
			if (1.f <= m_fPatternTimer && m_fPatternTimer <= 2.f)
			{
				str += L"HammerJump";
			}
			//조금 앞으로 해머링
			if (m_fPatternTimer < 1.f)
			{
				str += L"HammerFall";
			}
		}
		break;
		case BossState::Pattern4:
		{
			str += L"Entry";
		}
		break;

		default:
			str += L"Entry";
			break;
		}
	}
	if(str!=L"")
	{
		if (m_vecPos.x <= PLAYERPOS.x)
			str += L"Right";
		else str += L"Left";
	}

	m_pAnimator->Play(str, false);
	//m_pAnimator->Play(L"EntryLeft", false);
}

void CMonsterWaterBoss::CreateBullet()
{
	m_bIsCrBul = true;

	Bul1 = new CBossBullet;
	Bul1->SetPos(Vector(m_vecPos.x-60,m_vecPos.y));
	ADDOBJECT(Bul1);
	
	
	Bul2 = new CBossBullet;
	Bul2->SetPos(Vector(m_vecPos.x-50,m_vecPos.y-50));
	ADDOBJECT(Bul2);
	
	
	Bul3 = new CBossBullet;
	Bul3->SetPos(Vector(m_vecPos.x-50,m_vecPos.y+50));
	ADDOBJECT(Bul3);
	
	
	Bul4 = new CBossBullet;
	Bul4->SetPos(Vector(m_vecPos.x+60,m_vecPos.y));
	ADDOBJECT(Bul4);
	
	
	Bul5 = new CBossBullet;
	Bul5->SetPos(Vector(m_vecPos.x+50,m_vecPos.y-50));
	ADDOBJECT(Bul5);
	
	
	Bul6 = new CBossBullet;
	Bul6->SetPos(Vector(m_vecPos.x+50,m_vecPos.y+50));
	ADDOBJECT(Bul6);
	
	bulletCount = 6;
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

	{

		//높게 점프 후
		if (2.f < m_fPatternTimer &&
			m_fPatternTimer < 3.f)
		{
			m_vecPos.y -= 300 * DT;
			//m_pAnimator->Play(L"JumpLeft", false);
		}
		//탄환 생성
		if (1.5f < m_fPatternTimer &&
			m_fPatternTimer < 2.f &&
			m_bIsCrBul == false)
		{
			CreateBullet();
		}
		//내려오고 패턴 종료
		if (0.f < m_fPatternTimer &&
			m_fPatternTimer < 1.5f)
		{
			m_vecPos.y += 300 * DT;
			//m_pAnimator->Play(L"FallLeft", false);
		}
	}

}
void CMonsterWaterBoss::Pattern2() 
{
	//탄환이 2개 미만일경우 패턴 1실행
	if (bulletCount < 2)
	{
		m_fPatternTimer = 0.f;
	}//플레이어 위치 판단해 스테이지 중간기준 맞은편으로 이동함
	else
	{
		if (PLAYERPOS.x > WINSIZEX * 0.5f)
		{
			if (m_vecPos.x > WINSIZEX * 0.2f)
				m_vecPos.x -= 200 * DT;
		}
		else if (PLAYERPOS.x < WINSIZEX * 0.5f)
		{
			if (m_vecPos.x < WINSIZEX * 0.8f)
				m_vecPos.x += 200 * DT;
		}
		//2-3회 탄환을 아이싱으로 바꾸고 플레이어 향해 사출 
		m_fTimer += DT;
		int ran = rand() % 6;

		switch (ran)
		{
		case 0: {
			if (Bul1 != nullptr)
			{
				Bul1->SetBullet(true);
				Bul1->SetDir((PLAYERPOS - Bul1->GetPos()).Normalized());
				bulletCount--;
			}
			break;
		}
		case 1: {if (Bul2 != nullptr)
		{
			Bul2->SetBullet(true);
			Bul2->SetDir((PLAYERPOS - Bul2->GetPos()).Normalized()); bulletCount--;
		}
			  break;
		}
		case 2: {if (Bul3 != nullptr)
		{
			Bul3->SetBullet(true);
			Bul3->SetDir((PLAYERPOS - Bul3->GetPos()).Normalized());
			bulletCount--;
		}
			  break;
		}
		case 3: {if (Bul4 != nullptr)
		{
			Bul4->SetBullet(true);
			Bul4->SetDir((PLAYERPOS - Bul4->GetPos()).Normalized()); bulletCount--;
		}
			  break;
		}
		case 4: {if (Bul5 != nullptr)
		{
			Bul5->SetBullet(true);
			Bul5->SetDir((PLAYERPOS - Bul5->GetPos()).Normalized()); bulletCount--;
		}
			  break;
		}
		case 5: {if (Bul6 != nullptr)
		{
			Bul6->SetBullet(true);
			Bul6->SetDir((PLAYERPOS - Bul6->GetPos()).Normalized()); bulletCount--;
		}
			  break;
		}

		default:
			break;
		}

	}
	//패턴 종료
}
void CMonsterWaterBoss::Pattern3()
{
	//높이 날아올라서
	if(1.f<m_fPatternTimer &&m_fPatternTimer<2.f)
	{
		m_vecPos.y -= 300 * DT;
		m_vecPos.x += (PLAYERPOS - m_vecPos).Normalized().x * 200 * DT;
	}
	//조금 앞으로 해머링
	if(m_fPatternTimer<1.f)
	{
		m_vecPos.y += 300 * DT;
		m_vecPos.x += (PLAYERPOS - m_vecPos).Normalized().x * 20 * DT;
		
	}
	//패턴종료
}
void CMonsterWaterBoss::Pattern4()
{
	//탄환 없으면 패턴 1
	if (bulletCount < 6)
		m_fPatternTimer = 0.f;
	//맵중앙으로 날아오름
	//if(m_fPatternTimer>2.5f)
	if (m_vecPos.x != WINSIZEX * 0.5f && m_vecPos.y != WINSIZEY * 0.5f)
	{
		m_vecPos = Vector(WINSIZEX * 0.5f , WINSIZEY * 0.5f );
	}
	//빙글빙글 하면서 1초당 미사일 하나씩을 빔으로 바꿔서 주인공을 향해 쏨
	if(m_fPatternTimer<2.f)
	{

	}
}