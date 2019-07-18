#pragma once

#include "IScene.h"
#include "Player/Player.h"
#include "level/Level.h"
#include "Title.h"
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
#include "Gameover.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "graphics/RenderTarget.h"
#include"sky.h"
#include "Pose.h"
#include "GameCler.h"
#include "CheckPoint.h"

//これらは前方宣言でよい！
//struct PathPoint;
//class Enemy;
class Goal;
class Stage;
class Coin;
class sky;
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
	/// ゲームのステートのenum
	/// </summary>
	enum GameState {
		State_Default,		//デフォルト状態
		State_StageChange,	//ステージ遷移中]
		State_Pose,
		State_TitleChange,	//タイトル遷移中
		State_GameClear,
		State_GameOver		//ゲームオーバー
	};

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
	/// <summary>
	/// プレイヤーのインスタンスのゲット
	/// </summary>
	/// <returns>プレイヤーのインスタンス</returns>
	Player* GetPlayer()
	{
		return &m_player;
	}
	Goal* Getgoal()
	{
		return &m_goal;
	}
	CheckPoint* GetPoint()
	{
		return &m_point;
	}
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
		return 	StageNo;
	}
	int GetTimeScore()
	{
		return TimeScore;
	}
	/// <summary>
	/// ゲームのステートをゲット
	/// </summary>
	/// <returns>現在のステート</returns>
	const GameState GetState()
	{
		return m_gstate;
	}
	bool Contenyu()
	{
		return continuityflug;
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
	void GameFont();
private:

	GameState m_gstate = State_Default;
	int StageNo = 1;
	Player m_player;						//プレイヤー
	Pose m_pose;
	Goal m_goal;                            //ゴール
	CheckPoint m_point;
	Coin* m_coin;                           //コイン
	Stage* m_stage;                         //ステージ
	sky*	m_cubemap;					//キューブマップクラスのポインター
	GameCamera m_gameCamera;				//ゲームカメラ。
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。
	Level m_level;							//レベルを初期化。
	GameCler m_cler;						//ゲームクリア
	Gameover m_over;						//ゲームオーバー
	HP m_hp;								//プレイヤーのHP
	bool Goal = false;						//ゴール判定
	int GoalCount = 0;						//ゴール画面への遷移までの時間
	CSoundSource m_stagebgm;				//ステージBGM
	CSoundSource m_coinse;					//コインのSE
	CSoundSource m_kirakirase;				//ゴール出現時のSE
	CSoundSource m_posese;
	bool SEflag = true;						//SEを鳴らすためのフラグ
	bool flag = false;
	bool continuityflug = false;
	Sprite m_goalsprite;		
	Font m_font;					//フォント
	Timer m_time;					//タイマー
	Title m_title;
	int GAMETIME = 200;				//残り時間
	int Score = 0;
	int TimeScore = 0;				//タイムのスコア
	int taim = 0;						//経過時間
	bool ChangeFlag = false;
	wchar_t toubatu[256];
	float m_fontscale = 0.7f;
	PostEffect* m_postEffect;				//ポストエフェクト。
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。

};

//グローバルなアクセスポイントをグローバル変数として提供する。
extern Game* g_game;
