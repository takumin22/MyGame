#include "stdafx.h"
#include "Stage.h"
#include "Enemy.h"
#include"Game.h"
#include "Player.h"
#include "Scaffold.h"
#include "TurnScaffold.h"
#include "level/Level.h"
#include "Spring.h"
#include "Coin.h"
#include "Goal.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Stage::Stage(int No)
{

	m_edamegese.Init(L"Assets/sound/damage.wav");
	m_hakkense.Init(L"Assets/sound/hakken.wav");
	m_coinse.Init(L"Assets/sound/coinGet.wav");

	if (No == 0) {
		m_level.Init(L"Assets/level/level00.tkl", [&](LevelObjectData& objData)->bool {
			if (objData.EqualName(L"unityChan") == true) {
				//�v���C���[
				g_game->GetPlayer()->SetPosition(objData.position);
				return true;
			}
			else if (objData.EqualName(L"kkk") == true) {
				//�G�l�~�[
				auto enemy = new Enemy(objData.position, objData.rotation, g_game->GetPlayer());
				m_enemyList.push_back(enemy);
				g_game->GetPlayer()->SetEnemy(StageNo++, enemy);
				return true;
			}
			else if (objData.EqualName(L"Spring") == true) {
				//�o�l
				auto spring = new Spring(objData.position, objData.rotation, g_game->GetPlayer());
				m_springList.push_back(spring);

				g_game->GetPlayer()->SetSpring(StageNo1++, spring);
				return true;
			}
			else if (objData.EqualName(L"karasiba") == true) {

				auto scaffold = new Scaffold(objData.position, objData.rotation, g_game->GetPlayer());
				m_sacaffoldList.push_back(scaffold);
				g_game->GetPlayer()->SetScaffold(StageNo2++, scaffold);
				return true;
			}
			else if (objData.EqualName(L"turnasiba") == true) {
				auto turnscaffold = new TurnScaffold(objData.position, objData.rotation, g_game->GetPlayer());
				m_turnscaffold.push_back(turnscaffold);
				g_game->GetPlayer()->SetTurnScaffold(StageNo3++, turnscaffold);
				return true;
			}
			else if (objData.EqualName(L"Coin") == true) {
				//�R�C��
				auto coin = new Coin(objData.position, objData.rotation, g_game->GetPlayer());
				m_coinList.push_back(coin);
				g_game->GetPlayer()->SetCoin(StageNo4++, coin);
				return true;
			}
			else if (objData.EqualName(L"fence_gate") == true) {
				//�Q�[�g
				auto gate = new Gate(objData.position, objData.rotation, g_game->GetPlayer(),this);
				m_gateList.push_back(gate);
				return true;
			}
			return false;
		});
	}
	else  if (No == 1) {
		m_level.Init(L"Assets/level/level01.tkl", [&](LevelObjectData& objData)->bool {
			if (objData.EqualName(L"unityChan") == true) {
				//�v���C���[
				g_game->GetPlayer()->SetPosition(objData.position);
				return true;
			}
			return false;
		});
	}
}


Stage::~Stage()
{
	//�G�l�~�[�j��
	for (auto& enemy : m_enemyList) {
		delete enemy;
	}
	for (auto& scaffold : m_sacaffoldList) {
		delete scaffold;
	}
	for (auto& gate : m_gateList)
	{
		delete gate;
	}
	//�o�l�̕`��B
	for (auto& spring : m_springList) {
		delete spring;
	}
	for (auto& turnscaffold : m_turnscaffold) {
		delete turnscaffold;
	}
	for (auto& coin : m_coinList) {
		delete coin;
	}
	Score = 0;
	EnemyCount = 0;
	CoinCount = 0;
	StageNo = 0;
	StageNo1 = 0;
	StageNo2 = 0;
	StageNo3 = 0;
	StageNo4 = 0;
	StageNo5 = 0;
}

void Stage::StageMove()
{
}

void Stage::StageSE()
{

	m_hakkense.Play(false);
}

void Stage::Draw()
{
	m_level.Draw();
	//����
	for (auto& scaffold : m_sacaffoldList) {
		scaffold->Draw();
	}
	for (auto& gate : m_gateList)
	{
		gate->Draw();
	}
	//�G�l�~�[��`��B
	for (auto& enemy : m_enemyList) {
		enemy->Draw();
	}
	if (EnemyCount >= 2) {
	
	
		if (SEflag == true) {
			m_hakkense.Play(false);
				SEflag = false;
		}
		//�o�l�̕`��B
		for (auto& spring : m_springList) {
			spring->Draw();
		}
	}
	for (auto& turnscaffold : m_turnscaffold) {
		turnscaffold->Draw();
	}
	for (auto& coin : m_coinList) {
		coin->Draw();
	}
}

void Stage::Update()
{
	//�o�l�̍X�V�B
	if (EnemyCount >= 2) {
		for (auto& spring : m_springList) {
			spring->Update();
		}
	}
	for (auto& scaffold : m_sacaffoldList) {
		scaffold->Update();
	}
	for (auto& gate : m_gateList)
	{
		gate->Update();
	}
	//�G�l�~�[���X�V�B
	for (auto& enemy : m_enemyList) {
		enemy->Update();
		if (enemy->GetEnemyDeth() == true) 
		{
			Score += 10;
			EnemyCount++;
			m_edamegese.Play(false);
			delete enemy;
			m_enemyList.erase(std::remove(m_enemyList.begin(), m_enemyList.end(), enemy)
				, m_enemyList.end());
		}
	}
	for (auto& coin : m_coinList) {
		coin->Update();
		if (coin->GetCoinGet() == true) 
		{
			//�R�C���̉���炷
			m_coinse.Play(false);
			Score += 100;
			delete coin;
			CoinCount++;
			m_coinList.erase(std::remove(m_coinList.begin(), m_coinList.end(), coin)
				, m_coinList.end());
		}
	}
	for (auto& turnscaffold : m_turnscaffold) {
		turnscaffold->Update();
	}
}