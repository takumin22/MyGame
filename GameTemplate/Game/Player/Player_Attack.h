#pragma once
#include "Player_State.h"
class Player_Attack : public Player_State
{
public:
	Player_Attack(Player* pla, Player_StateMachine *psm);
	~Player_Attack();
	void Update();
private:
};