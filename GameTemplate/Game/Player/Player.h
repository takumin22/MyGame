#pragma once
#include "character/CharacterController.h"
#include "graphics/ShadowMap.h"
#include "HP.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "level/Level.h"
#include "Player_StateMachine.h"
#include "PlState.h"

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
	/// �U��
	/// </summary>
	void Attack();
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
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	void SetMoveSpeed(CVector3 move)
	{
		m_moveSpeed = move;
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
	/// <summary>
	/// �G�l�~�[�̃C���X�^���X���Z�b�g
	/// </summary>
	/// <param name="N"></param>
	/// <param name="enemy"></param>
	void SetEnemy(int N, Enemy* enemy)
	{
		m_enemy[N] = enemy;
	}
	/// <summary>
	/// �W�����v��̃C���X�^���X���Z�b�g
	/// </summary>
	/// <param name="N"></param>
	/// <param name="spring"></param>
	void SetSpring(int N, Spring* spring)
	{
		m_spring[N] = spring;
	}
	/// <summary>
	/// ����̃C���X�^���X���Z�b�g
	/// </summary>
	/// <param name="N"></param>
	/// <param name="scaffold"></param>
	void SetScaffold(int N, Scaffold* scaffold)
	{
		m_scaffold[N] = scaffold;
	}
	/// <summary>
	/// ��鑫��̃C���X�^���X���Z�b�g
	/// </summary>
	/// <param name="N"></param>
	/// <param name="turnscaffold"></param>
	void SetTurnScaffold(int N, TurnScaffold* turnscaffold)
	{
		m_turnscaffold[N] = turnscaffold;
	}
	/// <summary>
	/// �R�C���̃C���X�^���X���Z�b�g
	/// </summary>
	/// <param name="N"></param>
	/// <param name="coin"></param>
	void SetCoin(int N, Coin* coin)
	{
		m_coin[N] = coin;
	}
	//�A�j���[�V�����̃X�e�[�g�̃Z�b�^�[�B
	void SetAnimation(PlState::EnAnimationClip state)
	{
		m_animation.Play(state, 0.2f);
	}
	const CharacterController& GetCharaCon()
	{
		return m_charaCon;
	}
private:
	SkinModel m_model;									//�X�L�����f���B
	Animation m_animation;								//�A�j���[�V�����B
	AnimationClip m_animationClips[PlState::EnAnimationClip::enAnimationClip_Num];//�A�j���[�V�����N���b�v�B
	CVector3 m_position = CVector3::Zero();             //���W�B
	CVector3 m_oldposition = CVector3::Zero();			//�X�^�[�g�ʒu�ۑ��p
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();   //��]�B
	CMatrix m_mRot;										//����
	CVector3 m_rite = CVector3::Zero();
	CVector3 m_up = CVector3::Zero();					//�����
	CVector3 m_forward = CVector3::Zero();				//�O����
	CVector3 ambientColor = { 0.6f, 0.6f, 0.6f };		//�����̃J���[
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[��
	bool DamageFlag = false;
	int Time = 0;
	int DamageCount = 0;								//�_���[�W�ʂ̃J�E���g
	int Zanki = 4;										//�c�@
	int armboneNo = -1;
    Enemy* m_enemy[10];									//�G�l�~�[
	Spring* m_spring[10];								//�W�����v��
	Coin* m_coin[100];									//�R�C��
	HP m_hp;											//HP
	Player_StateMachine m_stMa;
	Scaffold* m_scaffold[2];							//��������
	TurnScaffold* m_turnscaffold[10];					//��]���鑫��
	CSoundSource m_spjumpse;							//�W�����v��ɏ�������̉�
	float m_deltatime = 1.0f / 30.0f;                   //1�t���[���̌o�ߎ���
	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
	Level m_level;
};
