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

	static int StageNo = 0;
	static int StageNo1 = 0;
	static int StageNo2 = 0;
	static int StageNo3 = 0;
	static int StageNo4 = 0;
	static int StageNo5 = 0;
	if (No == 0) {
		m_level.Init(L"Assets/level/level00.tkl", [&](LevelObjectData& objData)->bool {
			if (objData.EqualName(L"unityChan") == true) {
				//プレイヤー
				g_game->GetPlayer()->SetPosition(objData.position);
				return true;
			}
			else if (objData.EqualName(L"kkk") == true) {
				//エネミー
				auto enemy = new Enemy(objData.position, objData.rotation, g_game->GetPlayer());
				m_enemyList.push_back(enemy);
				g_game->GetPlayer()->SetEnemy(StageNo++, enemy);
				return true;
			}
			else if (objData.EqualName(L"Spring") == true) {
				//バネ
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
				//コイン
				auto coin = new Coin(objData.position, objData.rotation, g_game->GetPlayer());
				m_coinList.push_back(coin);
				g_game->GetPlayer()->SetCoin(StageNo4++, coin);
				return true;
			}
			else if (objData.EqualName(L"fence_gate") == true) {
				//ゲート
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
				//プレイヤー
				g_game->GetPlayer()->SetPosition(objData.position);
				return true;
			}
			else if (objData.EqualName(L"Dammy") == true) {
				//エネミー
				auto enemy = new Enemy(objData.position, objData.rotation, g_game->GetPlayer());
				m_enemyList.push_back(enemy);
				g_game->GetPlayer()->SetEnemy( StageNo5++, enemy);
				return true;
			}
			//else if (objData.EqualName(L"Spring") == true) {
			//	//バネ
			//	auto spring = new Spring(objData.position, objData.rotation, g_game->GetPlayer());
			//	m_springList.push_back(spring);
			//	g_game->GetPlayer()->SetSpring(StageNo1++, spring);
			//	return true;
			//}
			//else if (objData.EqualName(L"karasiba") == true) {
			//	//移動する足場
			//	auto scaffold = new Scaffold(objData.position, objData.rotation, g_game->GetPlayer());
			//	m_sacaffoldList.push_back(scaffold);
			//	g_game->GetPlayer()->SetScaffold(StageNo2++, scaffold);
			//	return true;
			//}
			else if (objData.EqualName(L"turnasiba") == true) {
				auto turnscaffold = new TurnScaffold(objData.position, objData.rotation, g_game->GetPlayer());
				m_turnscaffold.push_back(turnscaffold);
				g_game->GetPlayer()->SetTurnScaffold(StageNo3++, turnscaffold);
				return true;
			}
			else if (objData.EqualName(L"Coin") == true) {
				//コイン
				auto coin = new Coin(objData.position, objData.rotation, g_game->GetPlayer());
				m_coinList.push_back(coin);
				g_game->GetPlayer()->SetCoin(StageNo4++, coin);
				return true;
			}
			return false;
		});
	}
}


Stage::~Stage()
{
	//エネミー破棄
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
	//バネの描画。
	for (auto& spring : m_springList) {
		delete spring;
	}
	for (auto& turnscaffold : m_turnscaffold) {
		delete turnscaffold;
	}
	for (auto& coin : m_coinList) {
		delete coin;
	}
}

void Stage::StageMove()
{
}

void Stage::Draw()
{
	m_level.Draw();
	//足場
	for (auto& scaffold : m_sacaffoldList) {
		scaffold->Draw();
	}
	for (auto& gate : m_gateList)
	{
		gate->Draw();
	}
	//エネミーを描画。
	for (auto& enemy : m_enemyList) {
		enemy->Draw();
	}
	if (EnemyCount >= 2) {

		//バネの描画。
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

	//バネの更新。
	if (EnemyCount == 2) {
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
	//エネミーを更新。
	for (auto& enemy : m_enemyList) {
		enemy->Update();
		if (enemy->GetEnemyDeth() == true) 
		{
			EnemyCount++;
			delete enemy;
			m_enemyList.erase(std::remove(m_enemyList.begin(), m_enemyList.end(), enemy)
				, m_enemyList.end());
		}
	}
	for (auto& coin : m_coinList) {
		coin->Update();
		if (coin->GetCoinGet() == true) 
		{
			
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