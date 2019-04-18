#pragma once
#include "character/CharacterController.h"
#include "graphics/ShadowMap.h"
#include "HP.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Enemy;
class Spring;
class Scaffold;
class TurnScaffold;
class Coin;
class HP;

class Player
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// 回転
	/// </summary>
	void Turn();
	/// <summary>
	/// アニメーションコントロール
	/// </summary>
	void AnimationControl();
	/// <summary>
	/// ダメージ処理
	/// </summary>
	void Damage();
	/// <summary>
	/// バネジャンプの処理
	/// </summary>
	void SpringJump();
	/// <summary>
	/// プレイヤーの復帰処理
	/// </summary>
	void PlayerPosRetrun();
	/// <summary>
	/// 足場上の処理
	/// </summary>
	void Scafflod();
	/// <summary>
	/// 簡易的なAABB
	/// </summary>
	void AABB();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// プレイヤーの前方向
	/// </summary>
	/// <returns>現在の前方向</returns>
	CVector3 GetForWard() {
		return m_forward;
	}
	CVector3 GetUp() {
		return m_up;
	}
	CVector3 GetRite()
	{
		return m_rite;
	}
	/// <summary>
	/// プレイヤーのポジションを設定
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(m_position);
	}
	/// <summary>
	/// ダメージカウント数
	/// </summary>
	/// <returns></returns>
	int GetDCount() 
	{
		return DamageCount;
	}
	/// <summary>
	/// プレイヤーの残機をゲット
	/// </summary>
	/// <returns>プレイヤーの残機</returns>
	int GetZanki()
	{
		return Zanki;
	}
	/// <summary>
	/// プレイヤーのポジション
	/// </summary>
	/// <returns>現在のポジション</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetEnemy(int N, Enemy* enemy)
	{
		m_enemy[N] = enemy;
	}
	void SetSpring(int N, Spring* spring)
	{
		m_spring[N] = spring;
	}
	void SetScaffold(int N, Scaffold* scaffold)
	{
		m_scaffold[N] = scaffold;
	}
	void SetTurnScaffold(int N, TurnScaffold* turnscaffold)
	{
		m_turnscaffold[N] = turnscaffold;
	}
	void SetCoin(int N, Coin* coin)
	{
		m_coin[N] = coin;
	}
private:
	/// <summary>
	/// アニメーションのenum
	/// </summary>
	enum EnAnimationClip {
		enAnimationClip_idle,		//待機アニメーション。
		enAnimationClip_run,		//走りアニメーション。
		enAnimationClip_walk,		//歩きアニメーション。
		enAnimationClip_jump,		//ジャンプアニメーション。
		enAnimationClip_damage,		//ダメージアニメーション
		enAnimationClip_godown,		//ダウンアニメーション
		enAnimationClip_toptojump,
		enAnimationClip_salute,
		enAnimationClip_Num,		//アニメーションクリップの総数。
	};
	/// <summary>
	/// プレイヤーのステートのenum
	/// </summary>
	enum PState {
		State_Idel,					//基本状態(歩)
		State_MoveRun,				//ダッシ状態
		State_Jump,					//ジャンプ状態
		State_Damage,				//ダメージ状態
		State_Scaffold,				//足場上状態
		State_Scaffold1,
		State_InvincibleCount,		//無敵時間状態
		State_SpringJump,			//バネジャンプ状態
		State_Return,				//復帰状態
		State_Deth ,				//死亡状態
		State_Goal					//ゴール時状態
	};
	PState m_pstate = State_Idel;
	SkinModel m_model;									//スキンモデル。
	Animation m_animation;								//アニメーション。
	AnimationClip m_animationClips[enAnimationClip_Num];//アニメーションクリップ。
	CVector3 m_position = CVector3::Zero();             //座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();   //回転。
	CMatrix m_mRot;										//方向
	CVector3 m_rite = CVector3::Zero();
	CVector3 m_up = CVector3::Zero();					//上方向
	CVector3 m_forward = CVector3::Zero();				//前方向
	CVector3 ambientColor = { 0.6f, 0.6f, 0.6f };		//環境光のカラー
	CharacterController m_charaCon;						//キャラクターコントローラ
	float m_moveSpeedWhenStartJump;						//ジャンプ前の移動速度
	int Time = 0;										//無敵時間
	int DamageCount = 0;								//ダメージ量のカウント
	int Zanki = 4;										//残機
    Enemy* m_enemy[10];									//エネミー
	Spring* m_spring[10];								//ジャンプ台
	Coin* m_coin[100];									//コイン
	HP m_hp;											//HP
	Scaffold* m_scaffold[2];							//動く足場
	TurnScaffold* m_turnscaffold[10];					//回転する足場
	bool syoutotuflag = false;							//衝突フラグ
	bool syoutotuflag1 = false;							//衝突フラグ1
	CSoundSource m_spjumpse;							//ジャンプ台に乗った時の音
	float m_deltatime = 1.0f / 30.0f;                   //1フレームの経過時間
};

