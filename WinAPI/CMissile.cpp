#include "framework.h"
#include "CMissile.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"

CMissile::CMissile()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
	m_layer = Layer::Missile;
	m_strName = L"�̻���";
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
	AddCollider(ColliderType::Circle, Vector(8, 8), Vector(0, 0));
}

void CMissile::Update()
{
	m_vecPos += m_vecDir * m_fVelocity * DT;

	// ȭ������� ������� ����
	if (m_vecPos.x < 0 ||
		m_vecPos.x > WINSIZEX ||
		m_vecPos.y < 0 ||
		m_vecPos.y > WINSIZEY)
		DELETEOBJECT(this);
}

void CMissile::Render()
{
	RENDER->FrameCircle(
		m_vecPos.x,
		m_vecPos.y,
		m_vecScale.x);
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
