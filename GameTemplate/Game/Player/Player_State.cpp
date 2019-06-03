#include "stdafx.h"
#include "Player_State.h"


Player_State::Player_State(Player* player, Player_StateMachine *psm)
{
	m_player = player;
	m_plstma = psm;
}


Player_State::~Player_State()
{

}
