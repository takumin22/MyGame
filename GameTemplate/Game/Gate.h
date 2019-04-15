#pragma once
#include "physics/PhysicsStaticObject.h"
#include "Coin.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Player;
class Stage;
class Gate
{
public:
	Gate(CVector3 pos, CQuaternion rot, Player* player, Stage* stage);
	~Gate();
/// <summary>
/// �X�V
/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	void Open();
	/// <summary>
	/// �Q�[�g�̃I�[�v���t���O
	/// </summary>
	/// <param name="flag">
	/// ture �J��
	/// false �J�������~
	/// </param>
	void SetOpenFlag(bool flag)
	{
		GateFlag = flag;
	}


private:
	SkinModel m_model;
	CQuaternion m_rotation = CQuaternion::Identity();//��]
	CVector3 m_position = CVector3::Zero();             //���W
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	PhysicsStaticObject m_phyStaticObject;      //�ÓI�����I�u�W�F�N�g
	Player* m_player = nullptr;
	bool GateFlag = false;//�Q�[�g���J���ۂ̃t���O
	Stage* m_stage;
	int GateHantei = 0;
	CSoundSource m_opense;
};

