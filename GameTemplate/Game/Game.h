#pragma once

#include "IScene.h"
#include "Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Scaffold.h"
#include "Goal.h"
#include "Stage.h"
#include "Coin.h"
#include "Sprite.h"
#include "PostEffect.h"
#include "Gate.h"
#include "HP.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "graphics/RenderTarget.h"


//�����͑O���錾�ł悢�I
//struct PathPoint;
//class Enemy;
class Goal;
class Stage;
class Coin;

//�Q�[���N���X�B
class Game : public IScene
{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	Game();
	/*!
	* @brief	�f�X�g���N�^
	*/
	~Game();
	/*!
	* @brief	�X�V�B
	*/
	void Update() override;
	/*!
	* @brief	�`��B
	*/
	void Draw() override;
	/// <summary>
	/// �S�[������
	/// </summary>
	/// <returns>
	/// true �S�[��
	/// false �S�[�����Ă��Ȃ�
	/// </returns>
	bool GetGoal()
	{
		return Goal;
	}
	Player* GetPlayer()
	{
		return &m_player;
	}
	//Enemy* GetEnemy()
	//{
	//	return &m_enemy;
	//}

	Stage* GetStage()
	{
		return m_stage;
	}
	/// <summary>
	/// �X�e�[�W�i���o�[
	/// </summary>
	/// <returns></returns>
	int GetNo()
	{
		return No;
	}
	void SetGetCoin(bool N) {
		CoinGetFlag = N;
	}
	/// <summary>
	/// ���C�������_�����O�^�[�Q�b�g���擾�B
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
private:
	enum GameState {
		State_Default,
		State_StageChange,
		State_TitleChange
};
	GameState m_gstate = State_Default;
	bool CoinGetFlag = false;
	int No = 0;
	Player m_player;						//�v���C���[
	//Enemy m_enemy;
	Goal m_goal;                            //�S�[��
	Coin* m_coin;
	Stage* m_stage;                         //�X�e�[�W
	GameCamera m_gameCamera;				//�Q�[���J�����B
	RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	Level m_level;							//���x�����������B
	HP m_hp;
	bool Goal = false;  //�S�[������
	int GoalCount = 0;
	CSoundSource m_stagebgm;//�X�e�[�WBGM
	CSoundSource m_coinse;//�R�C����SE
	Sprite m_goalsprite;
	PostEffect* m_postEffect;				//�|�X�g�G�t�F�N�g�B
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;
