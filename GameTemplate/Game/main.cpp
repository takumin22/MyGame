#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include <algorithm>
#include "Stage.h"
#include "Title.h"
#include "Sprite.h"
#include "graphics/Camera.h"
#include "graphics/ShadowMap.h"
#include "PostEffect.h"
#include "Fade.h"
///////////////////////////////////////////////////////////////////
//�N���X�̃C���X�^���X���O���[�o���ȗ̈�ɒu���ꍇ��
//���I�m�ۂ������ق����ǂ��B
//�Ȃ����H
//  ->�A�v���P�[�V�������N�������Ƃ��ɃR���X�g���N�^���Ă΂�邩��B
//    ->�Ȃ�̖�肪����H
//      ->�G���W���̏������̑O�ɃR���X�g���N�^���Ă΂��ƍ���I
///////////////////////////////////////////////////////////////////

IScene* g_currentScene = nullptr;
ShadowMap* g_shadowMap = nullptr;
Fade* g_fade = nullptr;
//Game* g_game = nullptr;
///////////////////////////////////////////////////////////////////
//�Q�[���̍X�V�����B
//���W�̍X�V�Ƃ��̏����͂����ŌĂяo���Ƃ悢�����H
///////////////////////////////////////////////////////////////////
void UpdateGame()
{
	
	//�Q�[���p�b�h�̍X�V�B	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//�����G���W���̍X�V�B
	g_physics.Update();
	//�t�F�[�h�̍X�V
	g_fade->Update();
	//���݂̃V�[���̍X�V�B
	g_currentScene->Update();
	
}
///////////////////////////////////////////////////////////////////
// �Q�[���̕`�揈���B
///////////////////////////////////////////////////////////////////
void RenderGame()
{
	
	

	//�`��J�n�B
	g_graphicsEngine->BegineRender();


	//�V���h�E�}�b�v�Ƀ����_�����O
	g_shadowMap->RenderToShadowMap();


	//���݂̃V�[���̕`��B
	g_currentScene->Draw();
	//�t�F�[�h�̕`��
	g_fade->Draw();
	
	g_graphicsEngine->EffectUpdate();
	//�`��I���B
	g_graphicsEngine->EndRender();
}

///////////////////////////////////////////////////////////////////
// �Q�[���̏I�������B
///////////////////////////////////////////////////////////////////
void TermnateGame()
{


}
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���G���W���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	////�^�C�g���V�[���̍쐬�B
	CSoundEngine sound;
	sound.Init();
	g_currentScene = new Title;
	g_fade = new Fade;
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�T�E���h�̍X�V
		sound.Update();
		//�Q�[���̍X�V�B
		UpdateGame();
	
		//�Q�[���̕`�揈��.
		RenderGame();

		
	}
	//�Q�[���̏I������
	TermnateGame();
}