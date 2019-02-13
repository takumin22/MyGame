#pragma once
#include "physics/PhysicsStaticObject.h"
//#include "character/CharacterController.h"

class Player;
class Stage;
class Scaffold
{
public:
	Scaffold(CVector3 pos, CQuaternion rot, Player* player);
	~Scaffold();
	void Update();
	void FrontMove();
	void BackMove();
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

	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();     //���W�B
	CVector3 m_aftermove;     //���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();  //��]�B
	Player* m_player = nullptr;
	PhysicsStaticObject m_phyStaticObject;      //�ÓI�����I�u�W�F�N�g
	int Hantei = 0;
	Stage* m_stage;
	Scaffold* m_scaffold[2];

};