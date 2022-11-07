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
	m_pAnimator->CreateAnimation(L"IntroRight", m_pImage,		Vector(1.f,	10.f),		Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"IntroLeft", m_pImageRV,		Vector(785.f, 10.f),	Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 2);
	//INTROIDLE	2
	m_pAnimator->CreateAnimation(L"IntroIdleRight", m_pImage, Vector(99.f, 10.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"IntroIdleLeft", m_pImageRV,  Vector(687.f, 10.f),	Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 2);
	//IDLE		2
	m_pAnimator->CreateAnimation(L"IdleRight", m_pImage, Vector(197.f, 10.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.3f, 2);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_pImageRV,	Vector(589.f, 10.f),	Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.3f, 2);
	//WEAKIDLE	3
	m_pAnimator->CreateAnimation(L"WeakIdleRight", m_pImage, Vector(295.f, 10.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 3);
	m_pAnimator->CreateAnimation(L"WeakIdleLeft", m_pImageRV, Vector(491.f, 10.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 3);
	//SHOT		2
	m_pAnimator->CreateAnimation(L"ShotRight", m_pImage, Vector(442.f, 10.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"ShotLeft", m_pImageRV, Vector(344.f, 10.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 2);
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
	//FALL		1
	m_pAnimator->CreateAnimation(L"FallRight", m_pImage, Vector(197.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"FaLeftLL", m_pImageRV, Vector(589.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 1);
	//FALLLOOP	1 ※이하 미수정
	m_pAnimator->CreateAnimation(L"FallLoopRight", m_pImage, Vector(99.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"FallLoopLeft", m_pImageRV, Vector(736.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 1);
	//FALLSHOT	2
	m_pAnimator->CreateAnimation(L"FallShotRight", m_pImage, Vector(99.f, 226.f), Vector(47.f, 47.f), Vector(49.f, 0.f), 0.1f, 2);
	m_pAnimator->CreateAnimation(L"FallShotLeft", m_pImageRV, Vector(736.f, 226.f), Vector(47.f, 47.f), Vector(-49.f, 0.f), 0.1f, 2);
	//HURT		3
	
	//DIE		6 
	
	m_pAnimator->CreateAnimation(L"IdleUp", m_pImage,	Vector(8.f, 0.f), Vector(80.f, 70.f), Vector(80.f, 0.f), 0.1f, 7);
	
	m_pAnimator->CreateAnimation(L"MoveUp", m_pImageRV, Vector(0.f, 0.f), Vector(80.f, 75.f), Vector(84.f, 0.f), 0.05f, 16);
	
	
	m_pAnimator->Play(L"IdleRight", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(30, 32), Vector(0, 0));
}

void CPlayer::Update()
{
	m_bIsMove = false;

	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecPos.x -= m_fSpeed * DT;
		m_bIsMove = true;
		m_vecMoveDir.x = -1;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecPos.x += m_fSpeed * DT;
		m_bIsMove = true;
		m_vecMoveDir.x = +1;
	}
	else
	{
		m_vecMoveDir.x = 0;
	}

	if (BUTTONSTAY(VK_UP))
	{
		m_vecPos.y -= m_fSpeed * DT;
		m_bIsMove = true;
		m_vecMoveDir.y = +1;
	}
	else if (BUTTONSTAY(VK_DOWN))
	{
		m_vecPos.y += m_fSpeed * DT;
		m_bIsMove = true;
		m_vecMoveDir.y = -1;
	}
	else
	{
		m_vecMoveDir.y = 0;
	}

	if (BUTTONDOWN(VK_SPACE))
	{
		CreateMissile();
	}

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

	wstring str = L"";

	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	//if (m_vecLookDir.y > 0) str += L"Up";
	//else if (m_vecLookDir.y < 0) str += L"Down";

	m_pAnimator->Play(str, false);
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
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
}
