#pragma once
//#include "Stage.h"
class Player;
class Stage;
/// <summary>
/// 
/// </summary>
class Goal
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Goal();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Goal();
	/// <summary>
	/// �S�[���擾����
	/// </summary>
	void GoalGet();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �S�[���t���O���擾 
	/// </summary>
	/// <returns>true�Ȃ�S�[�����Ă���</returns>
	bool GetGFlag()
	{
		return GetFlag;
	}
	void SetGoalFlag(bool flag)
	{
		GetFlag = flag;
	}
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	Player* m_player = nullptr;							//�v���C���[
	bool GetFlag = false;								//�S�[���t���O
	Stage* m_stage;										//�X�e�[�W
	Effekseer::Effect* m_starEffect = nullptr;
	Effekseer::Handle m_starEffectHandle = -1;
	bool flag = false;
	float srot = 2.0f;
	int StarTime = 0;
};

