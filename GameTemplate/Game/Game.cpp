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
	m_stage = new Stage(StageNo++);
	m_goalsprite.Init(L"Resource/sprite/kari.dds", 1280, 720);
	m_gameCamera.SetPlayer(&m_player);	
	m_goal.SetPlayer(&m_player);
	m_stagebgm.Init(L"Assets/sound/stagebgm.wav");
	m_kirakirase.Init(L"Assets/sound/kirakira.wav");
	m_kirakirase.SetVolume(0.4f);
	m_stagebgm.SetVolume(0.5f);
	m_time.TimerStart();
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
	
	delete m_stage;
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
		//�v���C���[�̍X�V�B
		m_player.Update();
		//�J�����̍X�V
		m_gameCamera.Update();
		m_hp.Update();
		m_stage->Update();
		m_stagebgm.Play(true);
		if ( m_goal.GetGFlag() == false && m_stage->GetEnemyCount() == 0 ) {
			
			//�S�[�����X�V
			m_goal.Update();	
		}
		if (m_player.GetZanki() <= 0 || m_time.GetAllSeconds() >= GAMETIME) {
		
			m_gstate = State_GameOver;
		}
		if (m_goal.GetGFlag() == true)
		{
			GoalCount++;
			Goal = true;
			if (StageNo <= 1 && GoalCount >= 120.0f) {

				if (g_pad[0].IsPress(enButtonA) == true) {
					m_gstate = State_StageChange /*State_TitleChange*/;
				}
				if (g_pad[0].IsPress(enButtonB) == true)
				{
					m_gstate = State_TitleChange;
				}
			}
			if (StageNo > 1 && StageNo <= 2 && GoalCount >= 120.0f) {

				if (g_pad[0].IsPress(enButtonA) == true) {
				
					m_gstate = State_TitleChange;
				}
			}
		}
		break;
	case State_StageChange:
		//���݂̃X�e�[�W�������Ď��̃X�e�[�W���Ă�
		m_goal.SetGoalFlag(false);
		delete m_stage;
		m_stage = new Stage(StageNo++);
		Goal = false;
		GoalCount = 0;
		m_gstate = State_Default;
		break;
	case State_TitleChange:
		StageNo = 0;
		g_currentScene = new Title;
		delete this;
		break;
	case State_GameOver:
		m_over.Update();

		if (g_pad[0].IsTrigger(enButtonA))
		{
			
			m_gstate = State_TitleChange;
		}
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
	m_font.BeginDraw();	//�t�H���g�̕`��J�n�B

	////�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget,m_mainRenderTarget.GetViewport());
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.0f, 0.7f, 1.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);

	//�v���C���[�̕`��B
	m_player.Draw();
	//�X�e�[�W�̕`��
	m_stage->Draw();
	m_hp.Draw();

	if (m_goal.GetGFlag() == false && m_stage->GetEnemyCount() == 0) {
		//�S�[����\��
		if (SEflag == true) {
			m_kirakirase.Play(false);
			SEflag = false;
		}
		m_goal.Draw();
	}
	m_postEffect->Draw();
	//�������Ԃ̃^�C�}�[�����b�v�ŃX�g�b�v������B
	m_time.TimerStop();
	if (m_goal.GetGFlag() == false) {
		swprintf_s(toubatu, L"�R�C�� %d", m_stage->GetCoinCount());
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -FRAME_BUFFER_W / 2.0f,FRAME_BUFFER_H / 2.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,1.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"�X�R�A %d", m_stage->GetScore());
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -FRAME_BUFFER_W / 2.0f,300.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,1.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
		
		//�b�̌v�Z������
		 taim = (int)m_time.GetAllSeconds() % 201;
		swprintf_s(toubatu, L"�c�莞��%d�b", (GAMETIME - taim));		//�\���p�Ƀf�[�^�����H
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -200.0f,FRAME_BUFFER_H / 2.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
	}


	if (m_goal.GetGFlag() == true && GoalCount >= 120.0f) {
		m_goalsprite.Draw();
		TimeScore = GAMETIME - taim;
		swprintf_s(toubatu, L"�X�R�A %d", m_stage->GetScore());
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -200.0f , 100.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"�^�C���X�R�A %d", TimeScore);
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -300.0f , 30.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"���v�X�R�A %d", m_stage->GetScore() + TimeScore);
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -250.0f , -50.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
	}
	//�^�C�}�[���ĊJ������
	m_time.TimerRestart();
	//�����\���̏I��
	m_font.EndDraw();
	if (m_gstate == State_GameOver) {

		m_over.Draw();
	}
	
}