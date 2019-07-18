#include "stdafx.h"
#include "HP.h"
#include "Player/Player.h"
#include "Game.h"

HP::HP()
{
	//HP用のデータを生成
	m_hp.Init(L"Resource/sprite/heart.dds", 60, 60);
	m_hp2.Init(L"Resource/sprite/heart.dds", 60, 60);
	m_hp3.Init(L"Resource/sprite/heart.dds", 60, 60);
	m_hp4.Init(L"Resource/sprite/heart.dds", 60, 60);
	//HPのデータを更新
	m_hp.Update(m_hppos, CQuaternion::Identity(), CVector3::One());
	m_hp2.Update(m_hppos2, CQuaternion::Identity(), CVector3::One());
	m_hp3.Update(m_hppos3, CQuaternion::Identity(), CVector3::One());
	m_hp4.Update(m_hppos4, CQuaternion::Identity(), CVector3::One());
}


HP::~HP()
{

}

void HP::Update()
{
	
}

void HP::Draw()
{
	//プレイヤーがダメージを受けたらHPを消す
	if (g_game->GetPlayer()->GetDCount() <= 3)
	{
		m_hp.Draw();
	}
	if (g_game->GetPlayer()->GetDCount() <= 2)
	{
		m_hp2.Draw();
	}
	if (g_game->GetPlayer()->GetDCount() <= 1)
	{
		m_hp3.Draw();
	}
	if (g_game->GetPlayer()->GetDCount() <= 0) {
		m_hp4.Draw();
	}
}