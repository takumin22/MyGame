#pragma once
#include "character/CharacterController.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Stage;
class Player;
class Enemy
{
public:
	Enemy(CVector3 pos, CQuaternion rot, Player* player);
	~Enemy();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// エネミーの移動処理(右)
	/// </summary>
	void RigthMove();
	/// <summary>
	/// エネミーの移動処理(左)
	/// </summary>
	void LeftMove();
	/// <summary>
	/// ダメージ処理
	/// </summary>
	void Damage();
	void Search();
	/// <summary>
	/// 追跡処理
	/// </summary>
	void Tracking();
	/// <summary>
	/// エネミーのポジションを設定
	/// </summary>
	/// <param name="epos"></param>
	void SetEPosition(CVector3 epos)
	{
		m_position = epos;
	}
	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns></returns>
	CVector3 GetEPosition()
	{
		return m_position;
	}
	/// <summary>
	/// 死亡判定
	/// </summary>
	/// <returns>
	/// ture 死亡
	/// false　生存
	/// </returns>
	bool GetEnemyDeth() {
		return EnemyDeth;
	}
	void SetEnemyDeth(bool deth)
	{
		EnemyDeth = deth;
	}
private:
	enum EState {
		State_RigthMove,
		State_LeftMove,
		State_EDamage,
		State_Tracking
	};
	EState m_estate = State_LeftMove;
	CSoundSource m_damegese;
	SkinModel m_model;									//スキンモデル。
	//Animation m_animation;                      //アニメーション
	//AnimationClip  m_animationClip[3];          //アニメーションクリップ
	CVector3 m_position = CVector3::Zero();     //座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CVector3 m_up = CVector3::Zero();
	CMatrix m_mRot;
	int idoutime = 0;
	CQuaternion m_rotation = CQuaternion::Identity();  //回転。
	CharacterController m_charaCon;                  //キャラクターコントローラ
	Player* m_player = nullptr;
	Stage* m_enemylist[2];
	bool EnemyDeth = false; //死亡状態

};

