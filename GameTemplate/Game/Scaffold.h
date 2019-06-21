#pragma once
#include "physics/PhysicsStaticObject.h"
//#include "character/CharacterController.h"

class Player;
class Stage;
class Scaffold
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="player"></param>
	Scaffold(CVector3 pos, CQuaternion rot, Player* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Scaffold();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	void AABB();

	/// <summary>
	/// �O�����ړ�
	/// </summary>
	void FrontMove();
	/// <summary>
	/// ���ړ�
	/// </summary>
	void BackMove();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	CVector3 GetScaPosition()
	{
		return m_position;
	}
	/// <summary>
	/// ����̃X�e�[�g��enum
	/// </summary>
	enum SState {
		State_FrontMove,
		State_BackMove,
		State_PlayerMove
	};
	/// <summary>
	/// ����̃X�e�[�g���Q�b�g
	/// </summary>
	/// <returns>���݂̃X�e�[�g</returns>
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
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();				//���W�B
	CVector3 m_aftermove;								//���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	Player* m_player = nullptr;							//�v���C���[
	PhysicsStaticObject m_phyStaticObject;				//�ÓI�����I�u�W�F�N�g
	int Hantei = 0;
	Stage* m_stage;
	bool syoutotuflag = false;
	float Speed = 5.0f;
};