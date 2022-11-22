#include "framework.h"
#include "CBossBullet.h"

#include"CImage.h"

CBossBullet::CBossBullet()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(1, 0);
	m_pAnimator = nullptr;
	m_fVelocity = 250;
	bulDelTime = 0;
	Dir[0] = { 0 };
	m_layer = Layer::BossBullet;
	m_strName = L"몬스터미사일";
	m_Image = nullptr;
	m_bIsDel = false;

}

CBossBullet::~CBossBullet()
{
}

void CBossBullet::Init()
{
	AddCollider(ColliderType::Circle, Vector(8, 8), Vector(0, 0),1.f);
	m_Image = RESOURCE->LoadImg(L"BossBullet", L"Image\\Monster\\BOSS_MWATER.png");
	m_pAnimator = new CAnimator();
	
	m_pAnimator->CreateAnimation(L"Water", m_Image, Vector(150.f*12.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.0f, 1);
	m_pAnimator->CreateAnimation(L"Icing", m_Image, Vector(150.f*13.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.0f, 1);

	m_pAnimator->Play(L"Water", false);
	AddComponent(m_pAnimator);
}

void CBossBullet::Update()
{
	if (m_bIsDel)
		DELETEOBJECT(this);
	
	if (bulenhace == false)
	{
		
		//if(59.f<(BOSSPOS - m_vecPos).Magnitude() &&(BOSSPOS-m_vecPos).Magnitude()<61.f)
		MoveCircle();
		
		this->SetLayer(Layer::BossBullet);
	}
	else
	{
		this->SetLayer(Layer::MonsterBullet);
	}
	
	m_vecPos += m_vecDir * m_fVelocity * DT;
	


	AnimatorUpdate();
}

void CBossBullet::Render()
{
}

void CBossBullet::Release()
{
	DELETEOBJECT(this);
}

void CBossBullet::AnimatorUpdate()
{
	wstring str = L"";

	if (bulenhace==false) str += L"Water";
	else str += L"Icing";


	m_pAnimator->Play(str, false);
}

void CBossBullet::MoveCircle()
{
	
	int totalPoint;
	float xPoint, yPoint;
	// 사각 원 충돌 : 사각형을 중심으로 원이 어느 영역에 있느냐에 따라 다르게 처리
	/*	totalPoint (xPoint, yPoint)

		-4 (-1,-1) | -3 ( 0,-1) | -2 (+1,-1)
		-----------+------------+-----------
		-1 (-1, 0) |  0 ( 0, 0) | +1 (+1, 0)
		-----------+------------+-----------
		+2 (-1,+1) | +3 ( 0,+1) | +4 (+1,+1)
	*/
if (m_vecPos.x < BOSSPOS.x - GAME->GetBossScale().x * 0.5f)
	xPoint = -1;
else if (m_vecPos.x > BOSSPOS.x + GAME->GetBossScale().x * 0.5f)
	xPoint = 1;
else
	xPoint = 0;

if (m_vecPos.y < BOSSPOS.y - GAME->GetBossScale().y * 0.5f)
	yPoint = -1;
else if (m_vecPos.y > BOSSPOS.y + GAME->GetBossScale().y * 0.5f)
	yPoint = 1;
else
	yPoint = 0;

totalPoint = 3 * yPoint + xPoint;
Vector dir;
if (29.f > (BOSSPOS - m_vecPos).Magnitude() &&
	(BOSSPOS - m_vecPos).Magnitude() <31.f)
{
	dir= (BOSSPOS - m_vecPos).Normalized();
	//dir= Vector(0,0);
}

switch (totalPoint)
	{
	// 사각형 안에 원이 있을 경우 : 항상 충돌
	case 0:
		m_vecDir = Vector(0,0)+dir;
		break;
	// 좌우에 원이 있을 경우 : 사각형의 가로 크기 + 원의 반지름이 둘사이의 거리보다 작은경우 충돌
	case -1:
		m_vecDir = Vector(0,-1)+dir;
		break;
	case +1:
		
		m_vecDir = Vector(0,1)+dir;
		break;
	// 상하에 원이 있을 경우 : 사각형의 세로 크기 + 원의 반지름이 둘사이의 거리보다 작은경우 충돌
	case -3:

		m_vecDir = Vector(1,0)+dir;
		break;
	case +3:
		
		m_vecDir = Vector(-1,0)+dir;
		break;
	// 사각형의 대각선에 원이 있을 경우 : 사각형의 코너가 원 안에 있을 경우 충돌
	case -4:
		m_vecDir = Vector(1,-1)+dir;
		break;
	case -2:
		m_vecDir = Vector(1,1) + dir;
		break;
	case +2:
		m_vecDir = Vector(-1,-1) + dir;
		break;
	case +4:
	{
		m_vecDir = Vector(-1,1) + dir;
		
		break;
	}
	}

	
	
	
	//Vector a = (BOSSPOS - m_vecPos).Magnitude();
	//xPoint = //(3600.f * (1 - (sin(10 * DT) * sin(10 * DT)) - (cos(10 * DT) * cos(10 * DT))) - (BOSSPOS.x * BOSSPOS.x) - (BOSSPOS.y * BOSSPOS.y) + 120.f * cos(10 * DT)) /-2*BOSSPOS.x ;
	//	(BOSSPOS.x - 30) * cos(10 * DT);
	//yPoint = //(3600.f * (1 - (sin(10 * DT) * sin(10 * DT)) -(cos(10 * DT) * cos(10 * DT))) - (BOSSPOS.x * BOSSPOS.x) - (BOSSPOS.y * BOSSPOS.y) + 120.f * sin(10 * DT)) / -2 * BOSSPOS.y;
	//	(BOSSPOS.y - 30) * sin(10 * DT);

	////m_vecDir = Vector(xPoint, yPoint).Normalized();
	//m_vecPos = Vector(xPoint, yPoint);

}

void CBossBullet::OnCollisionEnter(CCollider* pOtherCollider)
{
	Logger::Debug(L"미사일이 충돌체와 부딪혀 사라집니다.");
	if(bulenhace)
		DELETEOBJECT(this);
}

void CBossBullet::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CBossBullet::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
