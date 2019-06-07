#pragma once
#include "Player_State.h"
class Player_Deth : public Player_State
{
public:
	Player_Deth(Player* pla, Player_StateMachine *psm);
	~Player_Deth();
	void Update();
private:
};

