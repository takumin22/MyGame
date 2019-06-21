#pragma once
#include "physics/PhysicsStaticObject.h"
//#include "character/CharacterController.h"

class Player;
class Stage;
class Scaffold
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="player"></param>
	Scaffold(CVector3 pos, CQuaternion rot, Player* player);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Scaffold();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void AABB();

	/// <summary>
	/// 前方向移動
	/// </summary>
	void FrontMove();
	/// <summary>
	/// 後ろ移動
	/// </summary>
	void BackMove();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	CVector3 GetScaPosition()
	{
		return m_position;
	}
	/// <summary>
	/// 足場のステートのenum
	/// </summary>
	enum SState {
		State_FrontMove,
		State_BackMove,
		State_PlayerMove
	};
	/// <summary>
	/// 足場のステートをゲット
	/// </summary>
	/// <returns>現在のステート</returns>
	const SState GetState() 
	{
		return m_sstate;
	}
	bool Getflag()
	{
		return syoutotuflag;
	}
	float GetSpeed()
	{
		return Speed;
	}
private:
	SState m_sstate = State_FrontMove;					//
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();				//座標。
	CVector3 m_aftermove;								//座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	Player* m_player = nullptr;							//プレイヤー
	PhysicsStaticObject m_phyStaticObject;				//静的物理オブジェクト
	int Hantei = 0;
	Stage* m_stage;
	bool syoutotuflag = false;
	float Speed = 5.0f;
};