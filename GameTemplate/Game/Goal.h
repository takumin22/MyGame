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
	Goal();
	~Goal();
	/// <summary>
	/// �S�[���擾����
	/// </summary>
	void GoalGet();
	void Update();
	void Draw();
	/// <summary>
	/// �S�[���t���O���擾 
	/// </summary>
	/// <returns>true�Ȃ�S�[�����Ă���</returns>
	bool GetGFlag()
	{
		return GetFlag;
	}
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();     //���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();  //��]�B
	Player* m_player = nullptr;			//�v���C���[
	bool GetFlag = false;              //�S�[���t���O
	Stage* m_stage;
};

