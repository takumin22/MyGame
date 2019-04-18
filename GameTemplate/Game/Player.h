#pragma once
#include "character/CharacterController.h"
#include "graphics/ShadowMap.h"
#include "HP.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Enemy;
class Spring;
class Scaffold;
class TurnScaffold;
class Coin;
class HP;

class Player
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// ��]
	/// </summary>
	void Turn();
	/// <summary>
	/// �A�j���[�V�����R���g���[��
	/// </summary>
	void AnimationControl();
	/// <summary>
	/// �_���[�W����
	/// </summary>
	void Damage();
	/// <summary>
	/// �o�l�W�����v�̏���
	/// </summary>
	void SpringJump();
	/// <summary>
	/// �v���C���[�̕��A����
	/// </summary>
	void PlayerPosRetrun();
	/// <summary>
	/// �����̏���
	/// </summary>
	void Scafflod();
	/// <summary>
	/// �ȈՓI��AABB
	/// </summary>
	void AABB();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �v���C���[�̑O����
	/// </summary>
	/// <returns>���݂̑O����</returns>
	CVector3 GetForWard() {
		return m_forward;
	}
	CVector3 GetUp() {
		return m_up;
	}
	CVector3 GetRite()
	{
		return m_rite;
	}
	/// <summary>
	/// �v���C���[�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(m_position);
	}
	/// <summary>
	/// �_���[�W�J�E���g��
	/// </summary>
	/// <returns></returns>
	int GetDCount() 
	{
		return DamageCount;
	}
	/// <summary>
	/// �v���C���[�̎c�@���Q�b�g
	/// </summary>
	/// <returns>�v���C���[�̎c�@</returns>
	int GetZanki()
	{
		return Zanki;
	}
	/// <summary>
	/// �v���C���[�̃|�W�V����
	/// </summary>
	/// <returns>���݂̃|�W�V����</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetEnemy(int N, Enemy* enemy)
	{
		m_enemy[N] = enemy;
	}
	void SetSpring(int N, Spring* spring)
	{
		m_spring[N] = spring;
	}
	void SetScaffold(int N, Scaffold* scaffold)
	{
		m_scaffold[N] = scaffold;
	}
	void SetTurnScaffold(int N, TurnScaffold* turnscaffold)
	{
		m_turnscaffold[N] = turnscaffold;
	}
	void SetCoin(int N, Coin* coin)
	{
		m_coin[N] = coin;
	}
private:
	/// <summary>
	/// �A�j���[�V������enum
	/// </summary>
	enum EnAnimationClip {
		enAnimationClip_idle,		//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,		//����A�j���[�V�����B
		enAnimationClip_walk,		//�����A�j���[�V�����B
		enAnimationClip_jump,		//�W�����v�A�j���[�V�����B
		enAnimationClip_damage,		//�_���[�W�A�j���[�V����
		enAnimationClip_godown,		//�_�E���A�j���[�V����
		enAnimationClip_toptojump,
		enAnimationClip_salute,
		enAnimationClip_Num,		//�A�j���[�V�����N���b�v�̑����B
	};
	/// <summary>
	/// �v���C���[�̃X�e�[�g��enum
	/// </summary>
	enum PState {
		State_Idel,					//��{���(��)
		State_MoveRun,				//�_�b�V���
		State_Jump,					//�W�����v���
		State_Damage,				//�_���[�W���
		State_Scaffold,				//�������
		State_Scaffold1,
		State_InvincibleCount,		//���G���ԏ��
		State_SpringJump,			//�o�l�W�����v���
		State_Return,				//���A���
		State_Deth ,				//���S���
		State_Goal					//�S�[�������
	};
	PState m_pstate = State_Idel;
	SkinModel m_model;									//�X�L�����f���B
	Animation m_animation;								//�A�j���[�V�����B
	AnimationClip m_animationClips[enAnimationClip_Num];//�A�j���[�V�����N���b�v�B
	CVector3 m_position = CVector3::Zero();             //���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();   //��]�B
	CMatrix m_mRot;										//����
	CVector3 m_rite = CVector3::Zero();
	CVector3 m_up = CVector3::Zero();					//�����
	CVector3 m_forward = CVector3::Zero();				//�O����
	CVector3 ambientColor = { 0.6f, 0.6f, 0.6f };		//�����̃J���[
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[��
	float m_moveSpeedWhenStartJump;						//�W�����v�O�̈ړ����x
	int Time = 0;										//���G����
	int DamageCount = 0;								//�_���[�W�ʂ̃J�E���g
	int Zanki = 4;										//�c�@
    Enemy* m_enemy[10];									//�G�l�~�[
	Spring* m_spring[10];								//�W�����v��
	Coin* m_coin[100];									//�R�C��
	HP m_hp;											//HP
	Scaffold* m_scaffold[2];							//��������
	TurnScaffold* m_turnscaffold[10];					//��]���鑫��
	bool syoutotuflag = false;							//�Փ˃t���O
	bool syoutotuflag1 = false;							//�Փ˃t���O1
	CSoundSource m_spjumpse;							//�W�����v��ɏ�������̉�
	float m_deltatime = 1.0f / 30.0f;                   //1�t���[���̌o�ߎ���
};

