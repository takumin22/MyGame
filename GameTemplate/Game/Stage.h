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
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
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
	void StageSE();
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
	int GetScore() 
	{
		return Score;
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
	CSoundSource m_edamegese;//エネミーのダメージSE
	CSoundSource m_hakkense;//ジャンプ台出現時のSE
	int CoinCount = 0;//取得コイン数
	int EnemyCount = 0;//倒したエネミー数
	bool SEflag = true;
	int Score = 0;//スコア
};

