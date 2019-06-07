#include "stdafx.h"
#include "Player_Attack.h"
#include "Player.h"


Player_Attack::Player_Attack(Player* pla, Player_StateMachine * psm) : Player_State(pla, psm)
{
}


Player_Attack::~Player_Attack()
{
}

void Player_Attack::Update()
{
	m_player->SetAnimation(PlState::EnAnimationClip::enAnimationClip_attack);
}