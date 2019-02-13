#pragma once
#include "physics/PhysicsStaticObject.h"
class Player;
class Spring
{
public:
	Spring(CVector3 pos, CQuaternion rot, Player* player);
	~Spring();
	void Draw();
	void Update();
	void SpringAnimation();
	void SpringJump();
	CVector3 GetSPosition()
	{
		return m_position;
	}

private:
	//enum EnAnimationClip {
	//	enAnimationClip_spring, //�o�l�A�j���[�V����
	//	enAnimationClip_Num, //�A�j���[�V��������

	//};
	SkinModel m_model;
	Animation m_animation;
//	AnimationClip m_animationClips[enAnimationClip_Num];
	CVector3 m_position = CVector3::Zero();     //���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();  //��]�B
	Player* m_player = nullptr;
	PhysicsStaticObject m_phyStaticObject;      //�ÓI�����I�u�W�F�N�g
};

