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
	//���݂̃V�[���̍X�V�B
	g_currentScene->Update();
	//g_shadowMap->RegistShadowCaster(&);
	//�V���h�E�}�b�v���X�V�B
	//g_shadowMap->Update(
	//	{ 0.0f, 1000.0f, 0.0f },
	//	{0.0f,0.0f,0.0f}
	//);*/
}
///////////////////////////////////////////////////////////////////
// �Q�[���̕`�揈���B
///////////////////////////////////////////////////////////////////
void RenderGame()
{
	
	

	//�`��J�n�B
	g_graphicsEngine->BegineRender();
    
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;

	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);


	//�V���h�E�}�b�v�Ƀ����_�����O
	g_shadowMap->RenderToShadowMap();

	//���ɖ߂��B
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();


	//���݂̃V�[���̕`��B
	g_currentScene->Draw();

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
	g_currentScene = new Title;


	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�Q�[���̍X�V�B
		UpdateGame();
		//�Q�[���̕`�揈���B
		RenderGame();
		
	}
	//�Q�[���̏I������
	TermnateGame();
}