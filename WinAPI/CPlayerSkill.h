#pragma once
#include "CGameObject.h"
#include "CPlayer.h"
class CImage;

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

    SkillSel GetSkillSel() { return sel; }

private:
  

    CImage* m_SelBut;
    CImage* m_Blank;
    CAnimator* m_pAnimator;

private:
   

    SkillSel sel;
    bool m_bIsLiSp=false;
    bool m_bIsSpCal=false;

    float LiSpTimer=0;

    void Init() override;
    void Update() override;
    void Render() override;
    void Release() override;

    void AnimatorUpdate();

};

