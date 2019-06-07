#include "stdafx.h"
#include "Player_StateMachine.h"


Player_StateMachine::Player_StateMachine(Player * pl) : 
	m_plMove(pl, this),m_plAttack(pl,this), m_plDamage(pl, this),m_plDeth(pl,this)
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
	switch (state)
	{
	case PlState::PState::State_Idel:
		m_ips = &m_plMove;
		break;
	case PlState::PState::State_Damage:
		m_ips = &m_plDamage;
		break;
	case PlState::PState::State_Deth:
		m_ips = &m_plDeth;
		break;
	case PlState::PState::State_Attack:
		m_ips = &m_plAttack;
		break;
	}
}