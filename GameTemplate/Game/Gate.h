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
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	PhysicsStaticObject m_phyStaticObject;      //�ÓI�����I�u�W�F�N�g
	Player* m_player = nullptr;
	bool GateFlag = false;
	Stage* m_stage;
};

