#pragma once
#include "character/CharacterController.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"

class Stage;
class Player;
class EnemyFly
{
public:
	EnemyFly(CVector3 pos, CQuaternion rot, Player* player);
	~EnemyFly();
	//エネミーのステート
	enum EState {
		State_Move, //移動ステート
		State_EDamage,//ダメージステート
	};
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// エネミーの移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// ダメージ処理
	/// </summary>
	void Damage();
	/// <summary>
	/// エネミーのポジションを設定
	/// </summary>
	/// <param name="epos">設定したいポジション</param>
	void SetEPosition(CVector3 epos)
	{
		m_position = epos;
		m_charaCon.SetPosition(epos);
	}
	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns>取得したポジション</returns>
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
	/// <summary>
	/// 死亡判定を設定
	/// </summary>
	/// <param name="deth">設定したい死亡判定</param>
	void SetEnemyDeth(bool deth)
	{
		EnemyDeth = deth;
	}
	/// <summary>
	/// エネミーの状態をゲット
	/// </summary>
	/// <returns>エネミーの状態</returns>
	const EState GetEState()
	{
		return m_estate;
	}
private:
	EState m_estate = State_Move;						//初期ステート
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();				//座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_kari = CVector3::Zero();
	CVector3 m_kari1 = CVector3::Zero();
	CVector3 m_scale = CVector3::One();					//拡大率。
	CVector3 m_up = CVector3::Zero();					//上方向
	CVector3 m_front = CVector3::Zero();
	CMatrix m_mRot;
	int idoutime = 0;									//移動時間
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	CharacterController m_charaCon;						//キャラクターコントローラ
	Player* m_player = nullptr;							//プレイヤー
	bool EnemyDeth = false;								//死亡状態
	int AnimPlayTime = 0;								//アニメーションの再生時間
	bool punchflag = false;
	Effekseer::Effect* m_enemyEffect = nullptr;
	Effekseer::Handle m_enemyEffectHandle = -1;

};

