#pragma once

#include "IScene.h"
#include "Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

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
	float m_toumei = 0.0f;									//�t�F�C�h�̓x����
	float m_faderate = 0.0f;
	CSoundSource m_titlebgm;
	CSoundSource m_decisionse;  //���艹
	Font m_font;
};