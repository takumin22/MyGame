#pragma once
#include "physics/PhysicsStaticObject.h"
class Player;
class TurnScaffold
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="player"></param>
	TurnScaffold(CVector3 pos, CQuaternion rot, Player* player);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TurnScaffold();
	/// <summary>
	/// 
	/// </summary>
	void AABB();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	bool Getflag()
	{
		return syoutotuflag;
	}
	CVector3 GetmoveSpeed()
	{
		return m_moveSpeed;
	}
	CQuaternion kari()
	{
		return aa;
	}
private:
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();				//座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	PhysicsStaticObject m_phyStaticObject;				//静的物理オブジェクト
	Player* m_player = nullptr;							//プレイヤー
	bool Hantei = false; //判定用のフラグ
	bool syoutotuflag = false;
	CQuaternion aa;
};

