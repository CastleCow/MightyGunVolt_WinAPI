#include "framework.h"
#include "CPlayerSkill.h"

#include "WinAPI.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

#include "CLightningSphere.h"
#include "CSparkCaliver.h"


CPlayerSkill::CPlayerSkill()
{
	m_vecLookDir= Vector(0, 0);
	
	m_pAnimator = nullptr;

	LiSp		= nullptr;
	SpCal		= nullptr;
	m_SelBut	= nullptr;
	m_Blank		= nullptr;

	m_layer		= Layer::Skill;
	sel			= SkillSel::Idle;
	
	m_strName	= L"스킬";

	LiSpTimer	= 0;
}

CPlayerSkill::~CPlayerSkill()
{
}

void CPlayerSkill::Init()
{
	
	
	m_SelBut= RESOURCE->LoadImg(L"SkillButton", L"Image\\Player\\SkillButton.png");
	m_Blank = RESOURCE->LoadImg(L"Blank", L"Image\\Player\\BlancBox.png");
	
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Idle", m_Blank, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"Button", m_SelBut, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 0.f), 0.1f, 1);
		
	/*m_pAnimator->CreateAnimation(L"SpCalButton", m_SelBut, Vector(0.f, 0.f), Vector(32.f, 32.f), Vector(0.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"LiSphButton", m_SelBut, Vector(32.f, 0.f), Vector(32.f, 32.f), Vector(0.f, 0.f), 0.1f, 1);
	*/
	

	m_pAnimator->Play(L"Idle", false);
	AddComponent(m_pAnimator);
}

void CPlayerSkill::Update()
{
	LiSpTimer += DT;

	if (LiSpTimer > 1.f)
	{
		sel = SkillSel::Idle;
		
		LiSpTimer = 0;
		
		DELETEOBJECT(this);
	}
	

	if (BUTTONDOWN(VK_LEFT))
	{
		sel = SkillSel::LightningSphere;
		LightningSphere();
	}
	
	if (BUTTONDOWN(VK_RIGHT))
	{
		sel = SkillSel::SparkCaliber;
		SparkCaliber();
	}
	if (SpCal != nullptr)
	{
		if (m_vecLookDir.x > 0)
		SpCal->SetPos(Vector(m_vecPos.x + 150, m_vecPos.y));
		else if (m_vecLookDir.x < 0)
		SpCal->SetPos(Vector(m_vecPos.x - 150, m_vecPos.y));
	}
	if (LiSp != nullptr)
	{
		LiSp->SetPos(m_vecPos);

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
	/*switch (sel)
	{
	case SkillSel::Idle:
		str += L"Idle";
		
		break;
	default:
		str += L"Button";
		break;
	}*/
	str += L"Button";
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
	Logger::Debug(L"스킬생성");

	//CSparkCaliver* SpCal = new CSparkCaliver();
	SpCal = new CSparkCaliver();
	
	SpCal->SetPos(Vector(m_vecPos.x + 100, m_vecPos.y));
	SpCal->SetDir(m_vecLookDir);
	ADDOBJECT(SpCal);
	
}

void CPlayerSkill::LightningSphere()
{
	sel = SkillSel::LightningSphere;
	Logger::Debug(L"스킬생성");

	//CLightningSphere* LiSp = new CLightningSphere();
	LiSp = new CLightningSphere();
	LiSp->SetPos(m_vecPos);
	
	ADDOBJECT(LiSp);
	
}
