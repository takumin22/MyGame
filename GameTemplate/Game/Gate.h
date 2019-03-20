#pragma once
#include "physics/PhysicsStaticObject.h"
#include "Coin.h"

class Player;
class Stage;
class Gate
{
public:
	Gate(CVector3 pos, CQuaternion rot, Player* player, Stage* stage);
	~Gate();
	void Update();
	void Draw();
	void Open();
	void SetOpenFlag(bool flag)
	{
		GateFlag = flag;
	}


private:
	SkinModel m_model;
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_position = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	PhysicsStaticObject m_phyStaticObject;      //静的物理オブジェクト
	Player* m_player = nullptr;
	bool GateFlag = false;
	Stage* m_stage;
};

