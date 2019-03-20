#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "Scaffold.h"
#include "Goal.h"
#include "Stage.h"
#include "PostEffect.h"
#include "Coin.h"
#include "Title.h"
#include "graphics/ShadowMap.h"
#include "graphics/Camera.h"


Game* g_game = nullptr;

Game::Game()
{
	g_game = this;
	m_stage = new Stage(No++);
	//static int count = 0;
	m_goalsprite.Init(L"Resource/sprite/kari.dds", 1280, 720);
	m_gameCamera.SetPlayer(&m_player);
	m_goal.SetPlayer(&m_player);
	m_soundEngine.Init();		
	m_coinse.Init(L"Assets/sound/coinGet.wav");
	//���C���ƂȂ郌���_�����O�^�[�Q�b�g���쐬����B
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	m_postEffect = new PostEffect;
	//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
	//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������B
	m_postEffect->SetPost(m_mainRenderTarget.GetRenderTargetSRV());

}


Game::~Game()
{
	
	g_currentScene = new Title;
	//���I�Ɋm�ۂ����C���X�^���X��j���B

		delete &m_goal;
		if (m_frameBufferRenderTargetView != nullptr) {
			m_frameBufferRenderTargetView->Release();
		}
		if (m_frameBufferDepthStencilView != nullptr) {
			m_frameBufferDepthStencilView->Release();
		}
}

void Game::Update()
{
	
	switch (m_gstate)
	{
	case State_Default:
		m_soundEngine.Update();
		//�v���C���[�̍X�V�B
		m_player.Update();
		//�J�����̍X�V
		m_gameCamera.Update();
		m_stage->Update();
		if (m_goal.GetGFlag() == false) {
			//�S�[�����X�V
			m_goal.Update();	
		}
		if (CoinGetFlag == true) {
			//�R�C���̉���炷
			m_coinse.Play(false);
			CoinGetFlag = false;
		}
		if (m_goal.GetGFlag() == true)
		{
			GoalCount++;
			Goal = true;
			if (No <= 1 && GoalCount >= 120.0f) {

				if (g_pad[0].IsPress(enButtonA) == true) {

					m_gstate = State_StageChange;
				}
			}
			if (No > 1 && No <= 2 && GoalCount >= 120.0f) {

				if (g_pad[0].IsPress(enButtonA) == true) {
					m_gstate = State_TitleChange;
				}
			}
		}
		break;
	case State_StageChange:
		//���݂̃X�e�[�W�������Ď��̃X�e�[�W���Ă�
		delete m_stage;
		m_stage = new Stage(No++);

		m_goal.SetGFlag(false);
		Goal = false;
		GoalCount = 0;
		m_gstate = State_Default;
		break;
	case State_TitleChange:
		g_currentScene = new Title;
		delete this;
		break;
	}
}
void Game::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
{
	ChangeRenderTarget(
		d3dDeviceContext,
		renderTarget->GetRenderTargetView(),
		renderTarget->GetDepthStensilView(),
		viewport
	);
}
void Game::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
{
	ID3D11RenderTargetView* rtTbl[] = {
		renderTarget
	};
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}
void Game::Draw()
{
	////�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget,m_mainRenderTarget.GetViewport());
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);

	//g_graphicsEngine->ChangeBackBaffer();
	//�v���C���[�̕`��B
	m_player.Draw();
	//�X�e�[�W�̕`��
	m_stage->Draw();
	if (m_goal.GetGFlag() == true && GoalCount >= 120.0f) {
		m_goalsprite.Draw();

	}
	if (m_goal.GetGFlag() == false) {
		//�S�[����\��
		m_goal.Draw();
	}
	m_postEffect->Draw();
}