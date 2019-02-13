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
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();     //���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();  //��]�B
	PhysicsStaticObject m_phyStaticObject;      //�ÓI�����I�u�W�F�N�g
	Player* m_player = nullptr;
	int Hantei = 0;
};

