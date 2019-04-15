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
	void FrontMove();
	void BackMove();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	void SetScaPos(CVector3 spos)
	{
		m_position = spos;
	}
	CVector3 GetScaPosition()
	{
		return m_position;
	}
	CVector3 GetScaSpeed() {
		return m_moveSpeed;
	}
	enum SState {
		State_FrontMove,
		State_BackMove,
		State_PlayerMove
	};
	SState m_sstate = State_FrontMove;

private:

	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();     //座標。
	CVector3 m_aftermove;     //座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();  //回転。
	Player* m_player = nullptr;
	PhysicsStaticObject m_phyStaticObject;      //静的物理オブジェクト
	int Hantei = 0;
	Stage* m_stage;

};