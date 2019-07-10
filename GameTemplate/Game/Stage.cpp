#include "stdafx.h"
#include "Stage.h"
#include "Enemy.h"
#include "EnemyFly.h"
#include"Game.h"
#include "Player/Player.h"
#include "Scaffold.h"
#include "TurnScaffold.h"
#include "level/Level.h"
#include "Spring.h"
#include "Coin.h"
#include "RedCoin.h"
#include "Goal.h"

Stage::Stage(int No)
{

	m_edamegese.Init(L"Assets/sound/damage.wav");
	m_hakkense.Init(L"Assets/sound/hakken.wav");
	m_coinse.Init(L"Assets/sound/coinGet.wav");

	if (No == 0) {
		m_level.Init(L"Assets/level/level00.tkl", [&](LevelObjectData& objData)->bool {
			if (objData.ForwardMatchName(L"Chara_4Hero") == true) {
				//プレイヤー
				g_game->GetPlayer()->SetPosition(objData.position);
				return true;
			}
			else if (objData.ForwardMatchName(L"kkk") == true) {
				//エネミー
				auto enemy = new Enemy(objData.position, objData.rotation, g_game->GetPlayer());
				m_enemyList.push_back(enemy);
				g_game->GetPlayer()->SetEnemy(StageNo++, enemy);
				return true;
			}
			else if (objData.ForwardMatchName(L"StoneMonster") == true) {
				//エネミー
				auto enemyfly = new EnemyFly(objData.position, objData.rotation, g_game->GetPlayer());
				m_enemyflyList.push_back(enemyfly);
				g_game->GetPlayer()->SetEnemyFly(StageNo6++, enemyfly);
				return true;
			}
			else if (objData.ForwardMatchName(L"Spring") == true) {
				//バネ
				auto spring = new Spring(objData.position, objData.rotation, g_game->GetPlayer());
				m_springList.push_back(spring);
				g_game->GetPlayer()->SetSpring(StageNo1++, spring);
				return true;
			}
			else if (objData.ForwardMatchName(L"karasiba") == true) {

				auto scaffold = new Scaffold(objData.position, objData.rotation, g_game->GetPlayer());
				m_sacaffoldList.push_back(scaffold);
				g_game->GetPlayer()->SetScaffold(StageNo2++, scaffold);
				return true;
			}
			else if (objData.ForwardMatchName(L"turnasiba") == true) {
				auto turnscaffold = new TurnScaffold(objData.position, objData.rotation, g_game->GetPlayer());
				m_turnscaffold.push_back(turnscaffold);
				g_game->GetPlayer()->SetTurnScaffold(StageNo3++, turnscaffold);
				return true;
			}
			else if (objData.ForwardMatchName(L"Coin") == true) {
				//コイン
				auto coin = new Coin(objData.position, objData.rotation, g_game->GetPlayer());
				m_coinList.push_back(coin);
				g_game->GetPlayer()->SetCoin(StageNo4++, coin);
				return true;
			}
			else if (objData.ForwardMatchName(L"RedCoin") == true) {
				//レッドコイン
				auto redcoin = new RedCoin(objData.position, objData.rotation, g_game->GetPlayer());
				m_rcoinList.push_back(redcoin);
				g_game->GetPlayer()->SetRedCoin(StageNo5++, redcoin);
				return true;
			}
			else if (objData.ForwardMatchName(L"star1") == true) {
				//星
				g_game->Getgoal()->SetPosition(objData.position);
				return true;
			}
			else if (objData.ForwardMatchName(L"fence_gate") == true) {
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
			if (objData.EqualName(L"Chara_4Hero") == true) {
				//プレイヤー
				g_game->GetPlayer()->SetPosition(objData.position);
				return true;
			}
			else if (objData.ForwardMatchName(L"kkk") == true) {
				//エネミー
				auto enemy = new Enemy(objData.position, objData.rotation, g_game->GetPlayer());
				m_enemyList.push_back(enemy);
				g_game->GetPlayer()->SetEnemy(StageNo++, enemy);
				return true;
			}
			else if (objData.ForwardMatchName(L"StoneMonster") == true) {
				//エネミー
				auto enemyfly = new EnemyFly(objData.position, objData.rotation, g_game->GetPlayer());
				m_enemyflyList.push_back(enemyfly);
				g_game->GetPlayer()->SetEnemyFly(StageNo6++, enemyfly);
				return true;
			}
			else if (objData.ForwardMatchName(L"Spring") == true) {
				//バネ
				auto spring = new Spring(objData.position, objData.rotation, g_game->GetPlayer());
				m_springList.push_back(spring);
				g_game->GetPlayer()->SetSpring(StageNo1++, spring);
				return true;
			}
			else if (objData.EqualName(L"star1") == true) {
				//星
				g_game->Getgoal()->SetPosition(objData.position);
				return true;
			}
			else if (objData.ForwardMatchName(L"turnasiba") == true) {
				auto turnscaffold = new TurnScaffold(objData.position, objData.rotation, g_game->GetPlayer());
				m_turnscaffold.push_back(turnscaffold);
				g_game->GetPlayer()->SetTurnScaffold(StageNo3++, turnscaffold);
				return true;
			}
			else if (objData.ForwardMatchName(L"Coin") == true) {
				//コイン
				auto coin = new Coin(objData.position, objData.rotation, g_game->GetPlayer());
				m_coinList.push_back(coin);
				g_game->GetPlayer()->SetCoin(StageNo4++, coin);
				return true;
			}
			else if (objData.ForwardMatchName(L"RedCoin") == true) {
				//レッドコイン
				auto redcoin = new RedCoin(objData.position, objData.rotation, g_game->GetPlayer());
				m_rcoinList.push_back(redcoin);
				g_game->GetPlayer()->SetRedCoin(StageNo5++, redcoin);
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
	//エネミー破棄
	for (auto& enemyfly : m_enemyflyList) {
		delete enemyfly;
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
	for (auto& redcoin : m_rcoinList) {
		delete redcoin;
	}
	for (auto& goal : m_goalList)
	{
		delete goal;
	}
	Score = 0;
	EnemyCount = 0;
	CoinCount = 0;
	RedCoinCount = 0;
	StageNo = 0;
	StageNo1 = 0;
	StageNo2 = 0;
	StageNo3 = 0;
	StageNo4 = 0;
	StageNo5 = 0;
	StageNo6 = 0;
}

void Stage::StageSE()
{

	m_hakkense.Play(false);
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
	//エネミー破棄
	for (auto& enemyfly : m_enemyflyList) {
		enemyfly->Draw();
	}
	if (EnemyCount >= 0) {
	
	
		if (SEflag == true) {
			m_hakkense.Play(false);
				SEflag = false;
		}
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
	for (auto& redcoin : m_rcoinList) {
		redcoin->Draw();
	}
}

void Stage::Update()
{

	//バネの更新。
	if (EnemyCount >= 0) {
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
			Score += 10;
			EnemyCount++;
			m_edamegese.Play(false);
			delete enemy;
			m_enemyList.erase(std::remove(m_enemyList.begin(), m_enemyList.end(), enemy)
				, m_enemyList.end());
		}
	}
	//エネミーを更新。
	for (auto& enemyfly : m_enemyflyList) {
		enemyfly->Update();
		if (enemyfly->GetEnemyDeth() == true)
		{
			Score += 10;
			EnemyCount++;
			m_edamegese.Play(false);
			delete enemyfly;
			m_enemyflyList.erase(std::remove(m_enemyflyList.begin(), m_enemyflyList.end(), enemyfly)
				, m_enemyflyList.end());
		}
	}
	for (auto& coin : m_coinList) {
		coin->Update();
		if (coin->GetCoinGet() == true) 
		{
			//コインの音を鳴らす
			m_coinse.Play(false);
			Score += 100;
			delete coin;
			CoinCount++;
			m_coinList.erase(std::remove(m_coinList.begin(), m_coinList.end(), coin)
				, m_coinList.end());
		}
	}
	for (auto& redcoin : m_rcoinList) {
		redcoin->Update();
		if (redcoin->GetCoinGet() == true)
		{
			//コインの音を鳴らす
			m_coinse.Play(false);
			Score += 100;
			delete redcoin;
			RedCoinCount++;
			m_rcoinList.erase(std::remove(m_rcoinList.begin(), m_rcoinList.end(), redcoin)
				, m_rcoinList.end());
		}
	}
	for (auto& turnscaffold : m_turnscaffold) {
		turnscaffold->Update();
	}
}