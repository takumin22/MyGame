#pragma once
class PlState
{
public:
	/// <summary>
	/// �A�j���[�V������enum
	/// </summary>
	enum EnAnimationClip {
		enAnimationClip_idle,		//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,		//����A�j���[�V�����B
		enAnimationClip_walk,		//�����A�j���[�V�����B
		enAnimationClip_attack,		//�����A�j���[�V�����B
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
		State_Attack,				//�U����ԁB
		State_Damage,				//�_���[�W���
		State_InvincibleCount,		//���G���ԏ��
		State_SpringJump,			//�o�l�W�����v���
		State_Return,				//���A���
		State_Deth,				//���S���
		State_Goal					//�S�[�������
	};
};

