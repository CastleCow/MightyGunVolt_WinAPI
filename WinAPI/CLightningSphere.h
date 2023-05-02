#pragma once
#include "CGameObject.h"
class CLightningSphere :
    public CGameObject
{
public:
    CLightningSphere();
    virtual ~CLightningSphere();

    void SetAngle(float a) { angle = a; }
private:
    CImage* m_LiSph;
    CImage* m_Blank;
    CAnimator* m_pAnimator;

private:
    Vector m_vecLookDir;

    bool m_bIsLiSp = false;
    

    float Timer = 0;
    float angle;

    void Init() override;
    void Update() override;
    void Render() override;
    void Release() override;

    void AnimatorUpdate();
    

    void OnCollisionEnter(CCollider* pOtherCollider) override;
    void OnCollisionStay(CCollider* pOtherCollider) override;
    void OnCollisionExit(CCollider* pOtherCollider) override;

};

