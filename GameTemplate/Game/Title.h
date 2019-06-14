#pragma once

#include "IScene.h"
#include "Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Fade.h"

class Title : public IScene
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Title();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Title();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	enum TitleState {
		State_GameState,
		State_StageSelect,
	};
private:
	Sprite m_sprite;			//�^�C�g���̃X�v���C�g�f�[�^
	Sprite m_titlelogo;
	Sprite m_yaji;
	CSoundSource m_titlebgm;    //�^�C�g��BGM
	CSoundSource m_decisionse;  //���艹
	CSoundSource m_cursorse;
	bool StratFlag = false;		//�X�^�[�g�t���O
	TitleState m_titlestate = State_GameState;
	CVector3 m_logopos = { 0.0f,400.0f,0.0f };
	CVector3 m_pos = { -250.0f,-180.0f,0.0f };				//���̃|�W�V����
	CQuaternion m_rot = CQuaternion::Identity();
};