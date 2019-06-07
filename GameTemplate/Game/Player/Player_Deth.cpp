#include "stdafx.h"
#include "Player_Deth.h"
#include "Player.h"


Player_Deth::Player_Deth(Player* pla, Player_StateMachine * psm) : Player_State(pla, psm)
{
}


Player_Deth::~Player_Deth()
{
}

void Player_Deth::Update()
{
	m_player->SetAnimation(PlState::EnAnimationClip::enAnimationClip_godown);
}