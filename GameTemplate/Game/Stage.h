#pragma once


#include "Enemy.h"
#include "Player.h"
#include "Scaffold.h"
#include "TurnScaffold.h"
#include "IScene.h"
#include "level/Level.h"
#include "Spring.h"
#include "Coin.h"
#include "Goal.h"
#include "Gate.h"
class Game;
class Enemy;
class Stage 
{
public:
	Stage(int No);
	~Stage();
	void Update();
	void Draw();
	void StageMove();
	void SetCount(int StageNo)
	{
		StageCount = StageNo;
	}
	int GetCount()
	{
		return StageCount;
	}
	int GetCoinCount()
	{
		return CoinCount;
	}
	int GetEnemyCount()
	{
		return EnemyCount;
	}
	Scaffold* GetScaffold(int i)
	{
		return m_sacaffoldList[i];
	}
	Enemy* GetEnemyList(int j)
	{
		return m_enemyList[j];
	}
private:

	int StageCount = 0;
	Level m_level;							//レベルを初期化。
	std::vector< Enemy* > m_enemyList;		//エネミーのリスト。
	std::vector< Scaffold*> m_sacaffoldList; //足場のリスト。
	std::vector< Spring*> m_springList;   //バネリスト
	std::vector< Coin*> m_coinList; //コインのリスト
	std::vector<TurnScaffold*> m_turnscaffold; //回転足場のリスト
	std::vector<Gate*> m_gateList;  //ゲートのリスト

	int CoinCount = 0;
	int EnemyCount = 0;

};

