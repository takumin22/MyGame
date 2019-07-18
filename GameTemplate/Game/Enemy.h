#pragma once
#include "character/CharacterController.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"

class Stage;
class Player;
class Enemy
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="player"></param>
	Enemy(CVector3 pos, CQuaternion rot, Player* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Enemy();
	//�G�l�~�[�̃X�e�[�g
	enum EState {
		State_Move, //�ړ��X�e�[�g
		State_EDamage,//�_���[�W�X�e�[�g
		State_Tracking//�ǐՃX�e�[�g

	};
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �G�l�~�[�̈ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �_���[�W����
	/// </summary>
	void Damage();

	void EnemyAnimation();
	/// <summary>
	/// �T������
	/// </summary>
	void Search();
	/// <summary>
	/// �ǐՏ���
	/// </summary>
	void Tracking();
	/// <summary>
	/// �G�l�~�[�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="epos">�ݒ肵�����|�W�V����</param>
	void SetEPosition(CVector3 epos)
	{
		m_position = epos;
		m_charaCon.SetPosition(epos);
	}
	/// <summary>
	/// �|�W�V�������擾
	/// </summary>
	/// <returns>�擾�����|�W�V����</returns>
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
	/// <summary>
	/// ���S�����ݒ�
	/// </summary>
	/// <param name="deth">�ݒ肵�������S����</param>
	void SetEnemyDeth(bool deth)
	{
		EnemyDeth = deth;
	}
/// <summary>
/// �G�l�~�[�̏�Ԃ��Q�b�g
/// </summary>
/// <returns>�G�l�~�[�̏��</returns>
	const EState GetEState()
	{
		return m_estate;
	}
private:
	/// <summary>
	/// �A�j���[�V������enum
	/// </summary>
	enum EnAnimationClip {
		enAnimationClip_walk,		//�����A�j���[�V�����B
		enAnimation_Damage,
		enAnimationClip_Num,		//�A�j���[�V�����N���b�v�̑����B
	};
	EState m_estate = State_Move;						//�����X�e�[�g
	SkinModel m_model;									//�X�L�����f���B
	Animation m_animation;								//�A�j���[�V�����B
	AnimationClip m_animationClips[enAnimationClip_Num];//�A�j���[�V�����N���b�v�B
	CVector3 m_position = CVector3::Zero();				//���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_kari = CVector3::Zero();
	CVector3 m_kari1 = CVector3::Zero();
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CVector3 m_up = CVector3::Zero();					//�����
	CVector3 m_front = CVector3::Zero();
	CSoundSource m_damagese;
	CMatrix m_mRot;
	int idoutime = 0;									//�ړ�����
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[��
	Player* m_player = nullptr;							//�v���C���[
	bool EnemyDeth = false;								//���S���
	int AnimPlayTime = 0;								//�A�j���[�V�����̍Đ�����
	int i = 1;
	bool punchflag = false;
	Effekseer::Effect* m_enemyEffect = nullptr;
	Effekseer::Handle m_enemyEffectHandle = -1;
	CVector3 toEnemyDir = CVector3::Zero();
};

