#pragma once

#include "IScene.h"
#include "Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Fade.h"

class Title : public IScene
{
public:
	Title();
	~Title();
	//�I�[�o�[���C�h�����֐��ɂ�override�C���q�����Ă���ƍK���ɂȂ��B
	void Update() override;
	//�I�[�o�[���C�h�����֐��ɂ�override�C���q�����Ă���ƍK���ɂȂ��B
	

	//�^�C�v�~�X�������Ƃ��ɃR���p�C���G���[�ɂȂ��ċ����Ă����B
	void Draw() override;
private:
	Sprite m_sprite;
	CSoundSource m_titlebgm;    //�^�C�g��BGM
	CSoundSource m_decisionse;  //���艹
	Font m_font;
	bool StratFlag = false;
};