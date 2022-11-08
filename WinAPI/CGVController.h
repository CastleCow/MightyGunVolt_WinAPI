#pragma once
class CPlayer;
class CGVController
{
public:
	CGVController();
	virtual ~CGVController();

	void Idle(CPlayer* p);
	void Move(CPlayer* p);
	void Jump(CPlayer* p);
	void Fall(CPlayer* p);
	void Attack(CPlayer* p);
	void Skill(CPlayer* p);
};

