#include "framework.h"
#include "CPlayerSkill.h"

#include "WinAPI.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

#include "CMissile.h"

CPlayerSkill::CPlayerSkill()
{
	m_vecLookDir = Vector(0, 0);
	
	m_pAnimator = nullptr;

	m_LiSph = nullptr;
	m_SparkCal = nullptr;
	m_SparkCalRV = nullptr;
	m_Blank = nullptr;

	m_layer = Layer::Skill;
	sel = SkillSel::Idle;
	
	m_strName = L"½ºÅ³";

	LiSpTimer = 0;
}

CPlayerSkill::~CPlayerSkill()
{
}

void CPlayerSkill::Init()
{
	m_LiSph= RESOURCE->LoadImg(L"LiSp", L"Image\\Player\\LightSphereAniRo.png");
	m_SparkCal= RESOURCE->LoadImg(L"SpCal", L"Image\\Player\\SparkCaliber.png");
	m_SparkCalRV= RESOURCE->LoadImg(L"SpCal", L"Image\\Player\\SparkCaliberRV.png");
	m_Blank = RESOURCE->LoadImg(L"Blank", L"Image\\Player\\BlancBox.png");
	
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Idle", m_Blank, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 0.f), 0.1f, 1);
	
	m_pAnimator->CreateAnimation(L"SpCal1Right", m_SparkCal, Vector(200.f, 0.f), Vector(50.f, 162.f), Vector(0.f, 0.f), 0.1f, 1,false);
	m_pAnimator->CreateAnimation(L"SpCal2Right", m_SparkCal, Vector(150.f, 0.f), Vector(100.f, 162.f), Vector(0.f, 0.f), 0.1f, 1,false);
	m_pAnimator->CreateAnimation(L"SpCal3Right", m_SparkCal, Vector(100.f, 0.f), Vector(150.f, 162.f), Vector(0.f, 0.f), 0.1f, 1,false);
	m_pAnimator->CreateAnimation(L"SpCal4Right", m_SparkCal, Vector(50.f, 0.f), Vector(200.f, 162.f), Vector(0.f, 0.f), 0.1f, 1,false);
	m_pAnimator->CreateAnimation(L"SpCal5Right", m_SparkCal, Vector(0.f, 0.f), Vector(250.f, 162.f), Vector(0.f, 0.f), 0.1f, 1,false);

	m_pAnimator->CreateAnimation(L"SpCal1Left", m_SparkCalRV, Vector(0.f, 0.f), Vector(50.f, 162.f), Vector(0.f, 0.f), 0.1f, 1, false);
	m_pAnimator->CreateAnimation(L"SpCal2Left", m_SparkCalRV, Vector(0.f, 0.f), Vector(100.f, 162.f), Vector(0.f, 0.f), 0.1f, 1, false);
	m_pAnimator->CreateAnimation(L"SpCal3Left", m_SparkCalRV, Vector(0.f, 0.f), Vector(150.f, 162.f), Vector(0.f, 0.f), 0.1f, 1, false);
	m_pAnimator->CreateAnimation(L"SpCal4Left", m_SparkCalRV, Vector(0.f, 0.f), Vector(200.f, 162.f), Vector(0.f, 0.f), 0.1f, 1, false);
	m_pAnimator->CreateAnimation(L"SpCal5Left", m_SparkCalRV, Vector(0.f, 0.f), Vector(250.f, 162.f), Vector(0.f, 0.f), 0.1f, 1, false);
	
	m_pAnimator->CreateAnimation(L"LightnigSphere", m_LiSph, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.3f, 7);

	m_pAnimator->Play(L"Idle", false);
	AddComponent(m_pAnimator);
}

void CPlayerSkill::Update()
{
	LiSpTimer += DT;

	if (LiSpTimer > 3.f)
	{
		m_bIsLiSp = false;
		m_bIsSpCal = false;
		LiSpTimer = 0;
	}


	if (BUTTONDOWN(VK_LEFT))
	{
		LightningSphere();
	}
	
	if (BUTTONDOWN(VK_RIGHT))
	{
		SparkCaliber();
	}
	AnimatorUpdate();
}

void CPlayerSkill::Render()
{
}

void CPlayerSkill::Release()
{
}

void CPlayerSkill::AnimatorUpdate()
{
	wstring str = L"";
	switch (sel)
	{
	case SkillSel::Idle:
		str += L"Idle";
		break;
	case SkillSel::LightningSphere:
		str += L"LightnigSphere";
		break;
	case SkillSel::SparkCaliber:
	{
		float Timer =100* DT;
		str += L"SpCal";
		str += to_wstring((int)Timer+1);
		if (m_vecLookDir.x > 0) str += L"Right";
		else if (m_vecLookDir.x < 0) str += L"Left";

	}
		break;
	case SkillSel::VolticChain:
		break;
	case SkillSel::QudosBoost:
		break;
	default:
		break;
	}
	m_pAnimator->Play(str, false);
	
}

void CPlayerSkill::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CPlayerSkill::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPlayerSkill::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CPlayerSkill::SparkCaliber()
{
	sel = SkillSel::SparkCaliber;
	AddCollider(ColliderType::Rect, Vector(30, 32), Vector(0, 0));
	m_bIsLiSp = true;
}

void CPlayerSkill::LightningSphere()
{
	sel = SkillSel::LightningSphere;
	AddCollider(ColliderType::Circle, Vector(60, 60), Vector(0, 0));
	m_bIsSpCal = true;
}
