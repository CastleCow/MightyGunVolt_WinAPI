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
	m_strName = L"���͹̻���";
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
		MoveCircle();
	if (890.f > (BOSSPOS - m_vecPos).Magnitude() &&
		(BOSSPOS - m_vecPos).Magnitude() < 910.f)
	{
		m_vecPos += (BOSSPOS - m_vecPos).Normalized() * 10 * DT;
	}
		//if(29.f<(BOSSPOS - m_vecPos).Magnitude() &&(BOSSPOS-m_vecPos).Magnitude()<31.f)
		this->SetLayer(Layer::BossBullet);
	}
	else
	{
		this->SetLayer(Layer::MonsterBullet);
	}
	m_vecPos += m_vecDir * m_fVelocity * DT;
	/*bulDelTime += DT;
	if (bulDelTime > 3.0f) {
		DELETEOBJECT(this);

	}*/


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
	


	int totalPoint, xPoint, yPoint;
	// �簢 �� �浹 : �簢���� �߽����� ���� ��� ������ �ִ��Ŀ� ���� �ٸ��� ó��
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

switch (totalPoint)
	{
	// �簢�� �ȿ� ���� ���� ��� : �׻� �浹
	case 0:
		m_vecDir = Vector(0,0);
		break;
	// �¿쿡 ���� ���� ��� : �簢���� ���� ũ�� + ���� �������� �ѻ����� �Ÿ����� ������� �浹
	case -1:
		m_vecDir = Vector(0,-1);
		break;
	case +1:
		
		m_vecDir = Vector(0,1);
		break;
	// ���Ͽ� ���� ���� ��� : �簢���� ���� ũ�� + ���� �������� �ѻ����� �Ÿ����� ������� �浹
	case -3:

		m_vecDir = Vector(1,0);
		break;
	case +3:
		
		m_vecDir = Vector(-1,0);
		break;
	// �簢���� �밢���� ���� ���� ��� : �簢���� �ڳʰ� �� �ȿ� ���� ��� �浹
	case -4:
		m_vecDir = Vector(1,-1);
		break;
	case -2:
		m_vecDir = Vector(1,1);
		break;
	case +2:
		m_vecDir = Vector(-1,-1);
		break;
	case +4:
	{
		m_vecDir = Vector(-1,1);
		
		break;
	}
	}

	
}

void CBossBullet::OnCollisionEnter(CCollider* pOtherCollider)
{
	Logger::Debug(L"�̻����� �浹ü�� �ε��� ������ϴ�.");
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
