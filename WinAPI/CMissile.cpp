#include "framework.h"
#include "CMissile.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include"CImage.h"
CMissile::CMissile()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(0, 0);
	m_fVelocity = 250;
	bulDelTime = 0;
	m_layer = Layer::Missile;
	m_strName = L"�̻���";
	m_Image = nullptr;
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
	AddCollider(ColliderType::Circle, Vector(8, 8), Vector(0, 0));
	m_Image = RESOURCE->LoadImg(L"Bullet", L"Image\\Player\\GV_BULLET.png");
	m_ImageRV = RESOURCE->LoadImg(L"Bullet", L"Image\\Player\\GV_BULLETRV.png");

}

void CMissile::Update()
{
	m_vecPos += m_vecDir * m_fVelocity * DT;

	bulDelTime += DT;
	if (bulDelTime > 2.0f) { 
		DELETEOBJECT(this);
		
	}

	
	// ȭ������� ������� ����
	/*if (m_vecPos.x < 0 ||
		m_vecPos.x > WINSIZEX ||
		m_vecPos.y < 0 ||
		m_vecPos.y > WINSIZEY)
		DELETEOBJECT(this);*/
}

void CMissile::Render()
{
	RENDER->FrameCircle(
		m_vecPos.x,
		m_vecPos.y,
		m_vecScale.x);
	if(m_vecDir.x>0)
	RENDER->Image(m_Image, m_vecPos.x , m_vecPos.y , (m_vecPos.x) + m_Image->GetWidth(), (m_vecPos.y) + m_Image->GetHeight());
	if(m_vecDir.x<0)	
	RENDER->Image(m_ImageRV, m_vecPos.x , m_vecPos.y , (m_vecPos.x) + m_ImageRV->GetWidth(), (m_vecPos.y) + m_ImageRV->GetHeight());


}

void CMissile::Release()
{
}

void CMissile::OnCollisionEnter(CCollider* pOtherCollider)
{

	Logger::Debug(L"�̻����� �浹ü�� �ε��� ������ϴ�.");
	DELETEOBJECT(this);
}

void CMissile::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CMissile::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
