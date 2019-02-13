#pragma once
#include "physics/PhysicsStaticObject.h"
class Player;
class TurnScaffold
{
public:
	TurnScaffold(CVector3 pos, CQuaternion rot, Player* player);
	~TurnScaffold();
	void Update();
	void Draw();
private:
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();     //座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();  //回転。
	PhysicsStaticObject m_phyStaticObject;      //静的物理オブジェクト
	Player* m_player = nullptr;
	int Hantei = 0;
};

