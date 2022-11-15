#pragma once
#include "CGameObject.h"
class CSparkCaliver :
    public CGameObject
{
public:
    CSparkCaliver();
    virtual ~CSparkCaliver();


private:
    CImage* m_SparkCal;
    CImage* m_Blank;
    CAnimator* m_pAnimator;

private:
    Vector m_vecLookDir;

    bool m_bIsSpCal = false;

    float Timer = 0;

    void Init() override;
    void Update() override;
    void Render() override;
    void Release() override;

    void AnimatorUpdate();

    void OnCollisionEnter(CCollider* pOtherCollider) override;
    void OnCollisionStay(CCollider* pOtherCollider) override;
    void OnCollisionExit(CCollider* pOtherCollider) override;
     
public:
    void SetDir(Vector a) { m_vecLookDir = a; };
};

