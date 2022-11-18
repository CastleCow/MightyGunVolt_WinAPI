#pragma once
#include "CGameObject.h"
class CGotoNextArea :
    public CGameObject
{
public:
	CGotoNextArea();
	virtual ~CGotoNextArea();

	void SetScene(GroupScene nextScene) { this->nextScene = nextScene;	}
	void SetPHP(float a) { PHP = a; }
	float GetPHP() { return PHP; }
	
private:
	GroupScene nextScene;
	
	float PHP=0;
	
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

