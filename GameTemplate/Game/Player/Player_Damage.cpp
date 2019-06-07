#include "stdafx.h"
#include "Player_Damage.h"
#include "Player.h"


Player_Damage::Player_Damage(Player* pla, Player_StateMachine * psm) : Player_State(pla, psm)
{
}


Player_Damage::~Player_Damage()
{
}

void Player_Damage::Update()
{
	m_player->SetAnimation(PlState::EnAnimationClip::enAnimationClip_damage);
}