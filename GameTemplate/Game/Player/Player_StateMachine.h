#pragma once
#include "Player_Move.h"
#include "PlState.h"
#include "Player_Damage.h"
#include "Player_Deth.h"
#include "Player_Attack.h"

class Player;
class Player_StateMachine
{
public:
	Player_StateMachine(Player* pl);
	~Player_StateMachine();
	void Start();
	void Change(PlState::PState state);
	void Update();

private:
	Player_Move m_plMove;
	Player_Attack m_plAttack;
	Player_Damage m_plDamage;
	Player_Deth m_plDeth;
	Player_State* m_ips = nullptr;
	PlState::PState  m_state = PlState::PState::State_Idel;
};

