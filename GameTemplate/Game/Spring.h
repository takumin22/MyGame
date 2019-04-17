#pragma once
#include "physics/PhysicsStaticObject.h"
class Player;
class Spring
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="player"></param>
	Spring(CVector3 pos, CQuaternion rot, Player* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Spring();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �o�l�̍��W�擾
	/// </summary>
	/// <returns>�o�l�̃|�W�V����</returns>
	CVector3 GetSPosition()
	{
		return m_position;
	}

private:
	SkinModel m_model;									//���f���f�[�^
	CVector3 m_position = CVector3::Zero();				//���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	Player* m_player = nullptr;							//�v���C���[
	PhysicsStaticObject m_phyStaticObject;				//�ÓI�����I�u�W�F�N�g
};

