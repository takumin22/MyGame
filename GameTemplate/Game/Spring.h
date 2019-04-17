#pragma once
#include "physics/PhysicsStaticObject.h"
class Player;
class Spring
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="player"></param>
	Spring(CVector3 pos, CQuaternion rot, Player* player);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Spring();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// バネの座標取得
	/// </summary>
	/// <returns>バネのポジション</returns>
	CVector3 GetSPosition()
	{
		return m_position;
	}

private:
	SkinModel m_model;									//モデルデータ
	CVector3 m_position = CVector3::Zero();				//座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	Player* m_player = nullptr;							//プレイヤー
	PhysicsStaticObject m_phyStaticObject;				//静的物理オブジェクト
};

