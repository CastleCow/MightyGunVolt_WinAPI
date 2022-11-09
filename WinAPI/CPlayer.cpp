#include "framework.h"
#include "CPlayer.h"

#include "WinAPI.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

#include "CMissile.h"

#define RVFIRST 785
#define NEXTSLICE 49

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"플레이어";

	m_pImage = nullptr;
	m_pImageRV = nullptr;
	State = PlayerState::Idle;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(1, 0);

	m_bIsMove = false;
	m_bIsAttack = false;
	m_bIsDead = false;
	m_bIsJump = false;

	gState = Ground::Air;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_pImage = RESOURCE->LoadImg(L"Player", L"Image\\Player\\Player-GV transpBG.png");
	m_pImageRV = RESOURCE->LoadImg(L"PlayerRV", L"Image\\Player\\Player-GV transpBG_RV.png");
	 
	m_pAnimator = new CAnimator;
	//INTRO		2
	m_pAnimator->CreateAnimation(L"IntroRight", m_pImage,		Vector(1.f,	10.f),		Vector(47.f, 47.f), Vector(49.f, 0.f), 0.3f, 2);
	m_pAnimator->CreateAnimation(L"IntroLeft", m_pImageRV,		Vector(785.f, 10.f),	Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.3f, 2);
	//INTROIDLE	2
	m_pAnimator->CreateAnimation(L"IntroIdleRight", m_pImage, Vector(99.f, 10.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.3f, 2);
	m_pAnimator->CreateAnimation(L"IntroIdleLeft", m_pImageRV,  Vector(687.f, 10.f),	Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.3f, 2);
	//IDLE		2
	m_pAnimator->CreateAnimation(L"IdleRight", m_pImage, Vector(197.f, 10.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.4f, 2);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_pImageRV,	Vector(589.f, 10.f),	Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.4f, 2);
	//WEAKIDLE	3
	m_pAnimator->CreateAnimation(L"WeakIdleRight", m_pImage, Vector(295.f, 10.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.4f, 3);
	m_pAnimator->CreateAnimation(L"WeakIdleLeft", m_pImageRV, Vector(491.f, 10.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.4f, 3);
	//SHOT		2
	m_pAnimator->CreateAnimation(L"IdleShotRight", m_pImage, Vector(442.f, 10.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"IdleShotLeft", m_pImageRV, Vector(344.f, 10.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 2);
	//WALK		6
	m_pAnimator->CreateAnimation(L"MoveRight", m_pImage, Vector(540.f, 10.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 6);
	m_pAnimator->CreateAnimation(L"MoveLeft", m_pImageRV, Vector(246.f, 10.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 6);
	//WALKSHOT	6				   
	m_pAnimator->CreateAnimation(L"MoveShotRight", m_pImage, Vector(1.f, 117.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 6);
	m_pAnimator->CreateAnimation(L"MoveShotLeft", m_pImageRV, Vector(785.f, 117.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 6);
	//JUMP		1
	m_pAnimator->CreateAnimation(L"JumpRight", m_pImage, Vector(1.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"JumpLeft", m_pImageRV, Vector(785.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 1);
	//JUMPLOOP	1
	m_pAnimator->CreateAnimation(L"JumpLoopRight", m_pImage, Vector(50.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"JumpLoopLeft", m_pImageRV, Vector(736.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 1);
	//JUMPSHOT	2
	m_pAnimator->CreateAnimation(L"JumpShotRight", m_pImage, Vector(99.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"JumpShotLeft", m_pImageRV, Vector(736.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"JumpLoopShotRight", m_pImage, Vector(99.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"JumpLoopShotLeft", m_pImageRV, Vector(736.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 2);
	//FALL		1
	m_pAnimator->CreateAnimation(L"FallRight", m_pImage, Vector(197.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"FallLeft", m_pImageRV, Vector(589.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 1);
	//FALLLOOP	1 
	m_pAnimator->CreateAnimation(L"FallLoopRight", m_pImage, Vector(99.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"FallLoopLeft", m_pImageRV, Vector(736.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 1);
	//FALLSHOT	2
	m_pAnimator->CreateAnimation(L"FallShotRight", m_pImage, Vector(99.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"FallShotLeft", m_pImageRV, Vector(736.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"FallLoopShotRight", m_pImage, Vector(99.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"FallLoopShotLeft", m_pImageRV, Vector(736.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 2);
	//HURT		3
	m_pAnimator->CreateAnimation(L"HurtRight", m_pImage, Vector(1.f, 444.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 3);
	m_pAnimator->CreateAnimation(L"HurtLeft", m_pImageRV, Vector(832.f, 444.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 3);
	//Skill		2
	m_pAnimator->CreateAnimation(L"SkillRight", m_pImage, Vector(1.f, 553.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"SkillLeft", m_pImageRV, Vector(832.f, 553.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 2);
	//SkillLoop	4
	m_pAnimator->CreateAnimation(L"SkillLoopRight", m_pImage, Vector(99.f, 553.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 4);
	m_pAnimator->CreateAnimation(L"SkillLoopLeft", m_pImageRV, Vector(687.f, 553.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 4);
	//DIE		6 
	m_pAnimator->CreateAnimation(L"DieRight", m_pImage, Vector(1.f, 766.f), Vector(79.f, 63.f), Vector(81.f, 0.f), 0.5f, 6);//80,829
	m_pAnimator->CreateAnimation(L"DieLeft", m_pImageRV, Vector(832.f, 766.f), Vector(79.f, 63.f), Vector(-81.f, 0.f), 0.5f, 6);

	m_pAnimator->Play(L"IntroRight", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(30, 32), Vector(0, 0));
}

void CPlayer::Update()
{
	m_bIsMove = false;
	IntroTimer += DT;
	if(IntroTimer>2.f)
	{
	Timer += DT;
	JumpTimer += DT;
		if(State != PlayerState::Dead)
		{
			//좌우 이동
			if (BUTTONSTAY(VK_LEFT))
			{
				Move(VK_LEFT);
			}
			else if (BUTTONSTAY(VK_RIGHT))
			{
				Move(VK_RIGHT);
			}
			else
			{
				Idle();
			}
			if (BUTTONSTAY('X'))//점프
			{
				Jump();
			}

			if (BUTTONSTAY(VK_UP))
			{
				if (gState != Ground::Ceiling)
					m_vecPos.y -= m_fSpeed * DT;
				//m_bIsMove = true;
				//m_vecMoveDir.y = +1;
			}
			else if (BUTTONSTAY(VK_DOWN))
			{
				if (gState != Ground::Ground)
					m_vecPos.y += m_fSpeed * DT;
				//m_bIsMove = true;
				//m_vecMoveDir.y = -1;
			}
			if (JumpTimer > 5.f)
				m_bIsJump = false;

			if (Timer > .5f)
				m_bIsAttack = false;
			if (BUTTONDOWN('Z'))//공격
			{
				Attack();
			}
			if (BUTTONDOWN('C'))
			{
				Skill();
			}
			if(gState==Ground::Air&&m_bIsJump!=true)
				Fall();
		}
		else if (State == PlayerState::Dead)
		{
			//체인지씬-리트라이 
			Dead();
		}
	}
	
	/*if ()
	{

	}*/
	AnimatorUpdate();
}

void CPlayer::Render()
{
}

void CPlayer::Release()
{
}

void CPlayer::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;
	if(IntroTimer<1.f)
		m_pAnimator->Play(L"IntroRight", false);
	else if (2.f> IntroTimer&&IntroTimer>1.f)
	{
		m_pAnimator->Play(L"IntroIdleRight", false);
	}
	else
	{
		wstring str = L"";
		switch ((int)State)
		{
		case (int)PlayerState::Move:	str += L"Move"; break;
		case (int)PlayerState::Idle:
		{
			if (m_HP < 5)
				str += L"Weak";
			str += L"Idle";
		}
		break;
		case (int)PlayerState::Dead: str += L"Die"; break;
		case (int)PlayerState::Jump:
		{
			str += L"Jump";
			if (JumpTimer > 0.2f)
				str += L"Loop";
			break;
		}
		case (int)PlayerState::Fall:
		{
			str += L"Fall";
			
			break;
		}
		}
		if (m_bIsAttack == true)str += L"Shot";
		else str += L"";

		if (m_vecLookDir.x > 0) str += L"Right";
		else if (m_vecLookDir.x < 0) str += L"Left";

		
		m_pAnimator->Play(str, false);
	}
}

void CPlayer::CreateMissile()
{
	Logger::Debug(L"미사일 생성");

	CMissile* pMissile = new CMissile();
	pMissile->SetPos(m_vecPos);
	pMissile->SetDir(m_vecLookDir);
	ADDOBJECT(pMissile);
	
	
}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	//적의 탄환과 부딫쳤을때
	
	//적과 부딫쳤을때
	if (pOtherCollider->GetObjName() == L"몬스터")
	{
		if (m_HP <= 0)
		{
			State = PlayerState::Dead;
		}
		m_HP--;

	}

	gState = Ground::Air;
	if (pOtherCollider->GetObjName() == L"땅")
	{
		Logger::Debug(L"땅과 플레이어와 충돌중");
		if (pOtherCollider->GetPos().y < m_vecPos.y)
			gState = Ground::Ceiling;
		else if (pOtherCollider->GetPos().y > m_vecPos.y)
			gState = Ground::Ground;
		
	}
	if (pOtherCollider->GetObjName() == L"벽")
	{
		Logger::Debug(L"벽과 플레이어와 충돌중");
		if (pOtherCollider->GetPos().x < m_vecPos.x)
			m_vecPos.x+=m_fSpeed*DT;
		else if (pOtherCollider->GetPos().x > m_vecPos.x)
			m_vecPos.x-=m_fSpeed*DT;
	}
	
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	gState = Ground::Air;
	if (pOtherCollider->GetObjName() == L"땅")
	{
		Logger::Debug(L"땅과 플레이어와 충돌중");
		if (pOtherCollider->GetPos().y < m_vecPos.y)
			gState = Ground::Ceiling;
		else if (pOtherCollider->GetPos().y > m_vecPos.y)
			gState = Ground::Ground;
	}
	if (pOtherCollider->GetObjName() == L"벽")
	{
		Logger::Debug(L"벽과 플레이어와 충돌중");
		//if(pOtherCollider->GetPos().x)
		if (pOtherCollider->GetPos().x < m_vecPos.x)
			m_vecPos.x += m_fSpeed * DT;
		else if (pOtherCollider->GetPos().x > m_vecPos.x)
			m_vecPos.x -= m_fSpeed * DT;
	}
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"땅")
	{
		Logger::Debug(L"땅과 플레이어와 충돌");
		if (pOtherCollider->GetPos().y < m_vecPos.y)
			gState = Ground::Air;
		else if (pOtherCollider->GetPos().y > m_vecPos.y)
			gState = Ground::Air;
	}
	
}

void CPlayer::Idle()
{
	State = PlayerState::Idle;
}

void CPlayer::Move(const int key)
{
	if (VK_RIGHT == key)
	{
		State = PlayerState::Move;
		m_vecPos.x += m_fSpeed * DT;
		m_bIsMove = true;
		m_vecMoveDir.x = +1;
	}
	else if (VK_LEFT == key)
	{
		State = PlayerState::Move;

		m_vecPos.x -= m_fSpeed * DT;
		m_bIsMove = true;
		m_vecMoveDir.x = -1;
	}
}

void CPlayer::Jump()
{
	State = PlayerState::Jump;
	float Speed = m_fSpeed;
	Speed -= m_fSpeed * DT;
	m_vecPos.y -= (Speed)*DT;
	JumpTimer = 0;
}

void CPlayer::Fall()
{
	State = PlayerState::Fall;
	if (gState == Ground::Air)
	{
		float Speed = m_fSpeed;
		Speed += m_fSpeed * DT;
		m_vecPos.y += (Speed)*DT;
	}
}

void CPlayer::Attack()
{
	m_bIsAttack = true;
	CreateMissile();
	Timer = 0;
}

void CPlayer::Skill()
{
	State = PlayerState::Skill;
}

void CPlayer::Dead()
{
	m_bIsDead = true;
	Timer = 0;
}

void CPlayer::Reset()
{
	State = PlayerState::Idle;
	m_bIsMove = false;
	m_bIsAttack = false;
	m_bIsDead = false;
	m_HP = 20;
}