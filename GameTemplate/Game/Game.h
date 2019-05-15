#pragma once

#include "IScene.h"
#include "Player.h"
#include "level/Level.h"
#include "Title.h"
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
#include "Gameover.h"
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
	/// �Q�[���̃X�e�[�g��enum
	/// </summary>
	enum GameState {
		State_Default, //�f�t�H���g���
		State_StageChange,//�X�e�[�W�J�ڒ�
		State_TitleChange, //�^�C�g���J�ڒ�
		State_GameOver
	};

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
	/// <summary>
	/// �v���C���[�̃C���X�^���X�̃Q�b�g
	/// </summary>
	/// <returns>�v���C���[�̃C���X�^���X</returns>
	Player* GetPlayer()
	{
		return &m_player;
	}
	Goal* Getgoal()
	{
		return &m_goal;
	}

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
		return 	StageNo;
	}
	/// <summary>
	/// �Q�[���̃X�e�[�g���Q�b�g
	/// </summary>
	/// <returns>���݂̃X�e�[�g</returns>
	const GameState GetState()
	{
		return m_gstate;
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

	GameState m_gstate = State_Default;
	int StageNo = 0;
	Player m_player;						//�v���C���[
	Goal m_goal;                            //�S�[��
	Coin* m_coin;                           //�R�C��
	Stage* m_stage;                         //�X�e�[�W
	GameCamera m_gameCamera;				//�Q�[���J�����B
	RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	Level m_level;							//���x�����������B
	Gameover m_over;						//�Q�[���I�[�o�[
	HP m_hp;								//�v���C���[��HP
	bool Goal = false;						//�S�[������
	int GoalCount = 0;						//�S�[����ʂւ̑J�ڂ܂ł̎���
	CSoundSource m_stagebgm;				//�X�e�[�WBGM
	CSoundSource m_coinse;					//�R�C����SE
	CSoundSource m_kirakirase;				//�S�[���o������SE
	bool SEflag = true;						//SE��炷���߂̃t���O
	Sprite m_goalsprite;		
	//�S�[���̃X�v���C�g
	Sprite m_stagecrear;
	Font m_font;					//�t�H���g
	Timer m_time;					//�^�C�}�[
	Title m_title;
	int GAMETIME = 200;				//�c�莞��
	int TimeScore = 0;				//�^�C���̃X�R�A
	int taim = 0;						//�o�ߎ���
	bool ChangeFlag = false;
	wchar_t toubatu[256];
	PostEffect* m_postEffect;				//�|�X�g�G�t�F�N�g�B
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B

};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;
