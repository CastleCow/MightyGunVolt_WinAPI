#pragma once
#include "CGameObject.h"
#include "CPlayer.h"
class CImage;
class  CLightningSphere;
class CSparkCaliver;
enum class SkillSel {
    Idle,
    LightningSphere,
    SparkCaliber,
    VolticChain,
    QudosBoost,

};

class CPlayerSkill :
    public CGameObject
{
public:
    CPlayerSkill();
    virtual ~CPlayerSkill();


private:
    CLightningSphere*   LiSp;
    CSparkCaliver*      SpCal;


    CImage* m_SelBut;
    CImage* m_Blank;
    CAnimator* m_pAnimator;

private:
    Vector m_vecLookDir;

    SkillSel sel;
    bool m_bIsLiSp=false;
    bool m_bIsSpCal=false;

    float LiSpTimer=0;

    void Init() override;
    void Update() override;
    void Render() override;
    void Release() override;

    void AnimatorUpdate();

   void OnCollisionEnter(CCollider* pOtherCollider) override;
    void OnCollisionStay(CCollider* pOtherCollider) override;
    void OnCollisionExit(CCollider* pOtherCollider) override;

    void SparkCaliber();
    void LightningSphere();

public:
    void SetDir(Vector a) { m_vecLookDir = a; };
};

