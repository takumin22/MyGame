#pragma once
#include "physics/PhysicsStaticObject.h"
class Player;
class TurnScaffold
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="player"></param>
	TurnScaffold(CVector3 pos, CQuaternion rot, Player* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TurnScaffold();
	/// <summary>
	/// 
	/// </summary>
	void AABB();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
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
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();				//���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	PhysicsStaticObject m_phyStaticObject;				//�ÓI�����I�u�W�F�N�g
	Player* m_player = nullptr;							//�v���C���[
	bool Hantei = false; //����p�̃t���O
	bool syoutotuflag = false;
	CQuaternion aa;
};

