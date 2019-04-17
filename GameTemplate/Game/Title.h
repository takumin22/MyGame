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
private:
	Sprite m_sprite;			//�^�C�g���̃X�v���C�g�f�[�^
	CSoundSource m_titlebgm;    //�^�C�g��BGM
	CSoundSource m_decisionse;  //���艹
	bool StratFlag = false;		//�X�^�[�g�t���O
};