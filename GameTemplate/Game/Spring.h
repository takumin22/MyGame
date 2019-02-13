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
	//	enAnimationClip_spring, //バネアニメーション
	//	enAnimationClip_Num, //アニメーション総数

	//};
	SkinModel m_model;
	Animation m_animation;
//	AnimationClip m_animationClips[enAnimationClip_Num];
	CVector3 m_position = CVector3::Zero();     //座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();  //回転。
	Player* m_player = nullptr;
	PhysicsStaticObject m_phyStaticObject;      //静的物理オブジェクト
};

