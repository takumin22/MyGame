#pragma once

#include "IScene.h"
#include "Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Scaffold.h"
#include "Goal.h"
#include "Stage.h"
#include "Coin.h"
#include "Sprite.h"
#include "PostEffect.h"
#include "Gate.h"
#include "HP.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "graphics/RenderTarget.h"


//これらは前方宣言でよい！
//struct PathPoint;
//class Enemy;
class Goal;
class Stage;
class Coin;

//ゲームクラス。
class Game : public IScene
{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	Game();
	/*!
	* @brief	デストラクタ
	*/
	~Game();
	/*!
	* @brief	更新。
	*/
	void Update() override;
	/*!
	* @brief	描画。
	*/
	void Draw() override;
	/// <summary>
	/// ゴール判定
	/// </summary>
	/// <returns>
	/// true ゴール
	/// false ゴールしていない
	/// </returns>
	bool GetGoal()
	{
		return Goal;
	}
	Player* GetPlayer()
	{
		return &m_player;
	}
	//Enemy* GetEnemy()
	//{
	//	return &m_enemy;
	//}

	Stage* GetStage()
	{
		return m_stage;
	}
	/// <summary>
	/// ステージナンバー
	/// </summary>
	/// <returns></returns>
	int GetNo()
	{
		return No;
	}
	void SetGetCoin(bool N) {
		CoinGetFlag = N;
	}
	/// <summary>
	/// メインレンダリングターゲットを取得。
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
private:
	enum GameState {
		State_Default,
		State_StageChange,
		State_TitleChange
};
	GameState m_gstate = State_Default;
	bool CoinGetFlag = false;
	int No = 0;
	Player m_player;						//プレイヤー
	//Enemy m_enemy;
	Goal m_goal;                            //ゴール
	Coin* m_coin;
	Stage* m_stage;                         //ステージ
	GameCamera m_gameCamera;				//ゲームカメラ。
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。
	Level m_level;							//レベルを初期化。
	HP m_hp;
	bool Goal = false;  //ゴール判定
	int GoalCount = 0;
	CSoundSource m_stagebgm;//ステージBGM
	CSoundSource m_coinse;//コインのSE
	Sprite m_goalsprite;
	PostEffect* m_postEffect;				//ポストエフェクト。
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
};

//グローバルなアクセスポイントをグローバル変数として提供する。
extern Game* g_game;
