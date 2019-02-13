#pragma once
#include "character/CharacterController.h"

class Player;
class Enemy
{
public:
	Enemy(CVector3 pos, CQuaternion rot, Player* player);
	~Enemy();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �G�l�~�[�̈ړ�����(�E)
	/// </summary>
	void RigthMove();
	/// <summary>
	/// �G�l�~�[�̈ړ�����(��)
	/// </summary>
	void LeftMove();
	/// <summary>
	/// �_���[�W����
	/// </summary>
	void Damage();
	void Search();
	/// <summary>
	/// �ǐՏ���
	/// </summary>
	void Tracking();
	/// <summary>
	/// �G�l�~�[�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="epos"></param>
	void SetEPosition(CVector3 epos)
	{
		m_position = epos;
	}
	/// <summary>
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	CVector3 GetEPosition()
	{
		return m_position;
	}
	/// <summary>
	/// ���S����
	/// </summary>
	/// <returns>
	/// ture ���S
	/// false�@����
	/// </returns>
	bool GetEnemyDeth() {
		return EnemyDeth;
	}
private:
	enum EState {
		State_RigthMove,
		State_LeftMove,
		State_EDamage,
		State_Tracking
	};
	EState m_estate = State_LeftMove;
	SkinModel m_model;									//�X�L�����f���B
	//Animation m_animation;                      //�A�j���[�V����
	//AnimationClip  m_animationClip[3];          //�A�j���[�V�����N���b�v
	CVector3 m_position = CVector3::Zero();     //���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();  //��]�B
	CharacterController m_charaCon;                  //�L�����N�^�[�R���g���[��
	Player* m_player = nullptr;

	bool EnemyDeth = false; //���S���
};

