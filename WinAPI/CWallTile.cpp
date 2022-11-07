#include "framework.h"
#include "CWallTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"


CWallTile::CWallTile()
{
	m_strName = L"벽";
}

CWallTile::~CWallTile()
{
}

void CWallTile::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CWallTile::Update()
{
	CTile::Update();
}

void CWallTile::Render()
{
	CTile::Render();

	ComponentRender();
}

void CWallTile::Release()
{
	CTile::Release();
}

void CWallTile::OnCollisionEnter(CCollider* pOther)
{
	// 벽타일과 충돌했을 경우 처리
}

void CWallTile::OnCollisionStay(CCollider* pOther)
{
	// 벽타일과 충돌했을 경우 처리
}

void CWallTile::OnCollisionExit(CCollider* pOther)
{
	// 벽타일과 충돌했을 경우 처리
}
