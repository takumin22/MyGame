#pragma once
#include "character/CharacterController.h"
#include "graphics/ShadowMap.h"

class Enemy;
class Spring;
class Scaffold;
class TurnScaffold;
class Coin;

class Player
{
public:
	Player();
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
	void AABB();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	CVector3 GetForWard() {
		return m_forward;
	}
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(m_position);
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	CQuaternion GetRotation()
	{
		return m_rotation;
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
	enum EnAnimationClip {
		enAnimationClip_idle,	//待機アニメーション。
		enAnimationClip_run,	//走りアニメーション。
		enAnimationClip_walk,	//歩きアニメーション。
		enAnimationClip_jump,   //ジャンプアニメーション。
		enAnimationClip_damage,  //ダメージアニメーション
		enAnimationClip_godown,  //ダウンアニメーション
		enAnimationClip_toptojump,
		enAnimationClip_salute,
		enAnimationClip_Num,	//アニメーションクリップの総数。
	};

	enum PState {
		State_Idel, //基本ステート(歩)
		State_MoveRun,
		State_Jump,
		State_Damage,  //ダメージステート
		State_Scaffold, //足場上ステート
		State_Scaffold1,
		State_InvincibleCount, //無敵時間ステート
		State_SpringJump, //バネジャンプステート
		State_Return,    //復帰ステート
		State_Deth ,      //死亡ステート
		State_Goal
	};
	PState m_pstate = State_Idel;
	SkinModel m_model;									//スキンモデル。
	Animation m_animation;								//アニメーション。
	AnimationClip m_animationClips[enAnimationClip_Num];//アニメーションクリップ。
	CVector3 m_position = CVector3::Zero();             //座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();   //回転。
	CMatrix m_mRot;
	CVector3 m_rite = CVector3::Zero();
	CVector3 m_up = CVector3::Zero();
	CVector3 m_forward = CVector3::Zero();
	CharacterController m_charaCon;   //キャラクターコントローラ
	float m_moveSpeedWhenStartJump;
	int Time = 0;//無敵時間
	int DamageCount = 0;//ダメージ量のカウント
    Enemy* m_enemy[2]; //エネミー
	Spring* m_spring[1];//ジャンプ台
	Coin* m_coin[3];
	
	Scaffold* m_scaffold[2];//動く足場
	TurnScaffold* m_turnscaffold[4];//回転する足場
	bool kariflag = false;     //衝突フラグ
	bool kariflag1 = false;     //衝突フラグ1
	float k = 1.0f;
};

