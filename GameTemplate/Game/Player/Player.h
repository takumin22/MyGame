#pragma once
#include "character/CharacterController.h"
#include "graphics/ShadowMap.h"
#include "HP.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "level/Level.h"
#include "Player_StateMachine.h"
#include "PlState.h"
#include "Sprite.h"

class Enemy;
class Spring;
class Scaffold;
class Stage;
class TurnScaffold;
class Coin;
class RedCoin;
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
	/// 攻撃
	/// </summary>
	void Attack();
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
	void TurnScafflod();
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
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	void SetMoveSpeed(CVector3 move)
	{
		m_moveSpeed = move;
	}
	CVector3 GetAttackPos()
	{
		return m_attackPos;
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
	/// <summary>
	/// エネミーのインスタンスをセット
	/// </summary>
	/// <param name="N"></param>
	/// <param name="enemy"></param>
	void SetEnemy(int N, Enemy* enemy)
	{
		m_enemy.push_back(enemy);
	}
	/// <summary>
	/// ジャンプ台のインスタンスをセット
	/// </summary>
	/// <param name="N"></param>
	/// <param name="spring"></param>
	void SetSpring(int N, Spring* spring)
	{
		m_spring.push_back(spring);
	}
	/// <summary>
	/// 足場のインスタンスをセット
	/// </summary>
	/// <param name="N"></param>
	/// <param name="scaffold"></param>
	void SetScaffold(int N, Scaffold* scaffold)
	{
		m_scaffold[N] = scaffold;
	}
	/// <summary>
	/// 回る足場のインスタンスをセット
	/// </summary>
	/// <param name="N"></param>
	/// <param name="turnscaffold"></param>
	void SetTurnScaffold(int N, TurnScaffold* turnscaffold)
	{
		m_turnscaffold.push_back(turnscaffold);
	}
	/// <summary>
	/// コインのインスタンスをセット
	/// </summary>
	/// <param name="N"></param>
	/// <param name="coin"></param>
	void SetCoin(int N, Coin* coin)
	{
		m_coin[N] = coin;
	}
	void SetRedCoin(int N, RedCoin*redcoin)
	{
		m_redcoin.push_back(redcoin);
	}
	//アニメーションのステートのセッター。
	void SetAnimation(PlState::EnAnimationClip state)
	{
		m_animation.Play(state, 0.2f);
	}
	const CharacterController& GetCharaCon()
	{
		return m_charaCon;
	}
	CQuaternion getk()
	{
		return ki;
	}
private:
	SkinModel m_model;									//スキンモデル。
	Animation m_animation;								//アニメーション。
	AnimationClip m_animationClips[PlState::EnAnimationClip::enAnimationClip_Num];//アニメーションクリップ。
	CVector3 m_position = CVector3::Zero();             //座標。
	CVector3 m_oldposition = CVector3::Zero();			//スタート位置保存用
	CVector3 kk = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();   //回転。
	CMatrix m_mRot;										//方向
	CVector3 m_rite = CVector3::Zero();
	CVector3 m_up = CVector3::Zero();					//上方向
	CVector3 m_forward = CVector3::Zero();				//前方向
	CVector3 ambientColor = { 0.6f, 0.6f, 0.6f };		//環境光のカラー
	CVector3 m_attackPos = CVector3::Zero();
	CharacterController m_charaCon;						//キャラクターコントローラ
	bool DamageFlag = false;
	int Time = 0;
	int DamageCount = 0;								//ダメージ量のカウント
	int Zanki = 4;										//残機
	bool posflag = false;
	Sprite m_sprite;
    std::vector<Enemy*> m_enemy;									//エネミー
	std::vector<Spring*> m_spring;								//ジャンプ台
	std::vector<RedCoin*> m_redcoin;
	Coin* m_coin[100];									//コイン
	HP m_hp;											//HP
	Player_StateMachine m_stMa;
	Scaffold* m_scaffold[2];							//動く足場
	std::vector<TurnScaffold*> m_turnscaffold;					//回転する足場
	CSoundSource m_spjumpse;							//ジャンプ台に乗った時の音
	float m_deltatime = 1.0f / 30.0f;                   //1フレームの経過時間
	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
	CQuaternion ki;
	float ka;
};

