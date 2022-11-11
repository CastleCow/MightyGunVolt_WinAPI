#include "framework.h"
#include "CNextMapTile.h"
#include"WinAPI.h"
CNextMapTile::CNextMapTile()
{
	m_strName = L"다음맵";
}

CNextMapTile::~CNextMapTile()
{
}

void CNextMapTile::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CNextMapTile::Update()
{
	CTile::Update();
}

void CNextMapTile::Render()
{
	CTile::Render();

	ComponentRender();
}

void CNextMapTile::Release()
{
	CTile::Release();
}

void CNextMapTile::OnCollisionEnter(CCollider* pOther)
{
	// 다음맵과 충돌했을 경우 처리
	Logger::Debug(L"다음맵으로 이동");

}

void CNextMapTile::OnCollisionStay(CCollider* pOther)
{
}

void CNextMapTile::OnCollisionExit(CCollider* pOther)
{
}
