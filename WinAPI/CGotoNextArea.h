#pragma once
#include "CGameObject.h"
class CGotoNextArea :
    public CGameObject
{
public:
	CGotoNextArea();
	virtual ~CGotoNextArea();

	void SetScene(GroupScene nextScene) { this->nextScene = nextScene;	};
private:
	GroupScene nextScene;
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

