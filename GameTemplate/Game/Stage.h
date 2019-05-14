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
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="No">ステージのナンバー</param>
	Stage(int No);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Stage();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	void StageMove();
	void StageSE();
	/// <summary>
	/// ステージを設定
	/// </summary>
	/// <param name="StageNo">ステージのナンバー</param>
	void SetCount(int StageNo)
	{
		StageCount = StageNo;
	}
	int GetCount()
	{
		return StageCount;
	}
	/// <summary>
	/// コインカウントを取得
	/// </summary>
	/// <returns>コインの取得数</returns>
	int GetCoinCount()
	{
		return CoinCount;
	}
	/// <summary>
	/// エネミーカウントをゲット
	/// </summary>
	/// <returns>エネミーを倒した数</returns>
	int GetEnemyCount()
	{
		return EnemyCount;
	}
	/// <summary>
	/// スコアをゲット
	/// </summary>
	/// <returns>現在のスコア</returns>
	int GetScore() 
	{
		return Score;
	}
private:

	int StageCount = 0;
	Level m_level;								//レベルを初期化。
	std::vector< Enemy* > m_enemyList;			//エネミーのリスト。
	std::vector< Scaffold*> m_sacaffoldList;	//足場のリスト。
	std::vector< Goal*> m_goalList;
	std::vector< Spring*> m_springList;			//バネリスト
	std::vector< Coin*> m_coinList;				//コインのリスト
	std::vector<TurnScaffold*> m_turnscaffold;	//回転足場のリスト
	std::vector<Gate*> m_gateList;				//ゲートのリスト
	CSoundSource m_edamegese;					//エネミーのダメージSE
	CSoundSource m_hakkense;					//ジャンプ台出現時のSE
	CSoundSource m_coinse;						//コインの取得SE
	int CoinCount = 0;							//取得コイン数
	int EnemyCount = 0;							//倒したエネミー数
	bool SEflag = true;							//SEを鳴らすかのフラグ
	int Score = 0;								//スコア
	int StageNo = 0;
	int StageNo1 = 0;
	int StageNo2 = 0;
	int StageNo3 = 0;
	int StageNo4 = 0;
	int StageNo5 = 0;
};

