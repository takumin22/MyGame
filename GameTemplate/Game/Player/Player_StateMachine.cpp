#include "stdafx.h"
#include "Player_StateMachine.h"


Player_StateMachine::Player_StateMachine(Player * pl) : 
	m_plMove(pl, this)
{
   Change(PlState::PState::State_Idel);
}


Player_StateMachine::~Player_StateMachine()
{
}

void Player_StateMachine::Start()
{
	
}
void Player_StateMachine::Update()
{
	m_ips->Update();
}

void Player_StateMachine::Change(PlState::PState state)
{
	switch (m_state)
	{
	case PlState::PState::State_Idel:
		m_ips = &m_plMove;
		break;
	}
}