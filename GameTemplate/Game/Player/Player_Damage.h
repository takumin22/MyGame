#pragma once
#include "Player_State.h"
class Player_Damage : public Player_State
{
public:
	Player_Damage(Player* pla, Player_StateMachine *psm);
	~Player_Damage();
	void Update();
private:
};

