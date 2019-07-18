#pragma once

#include "IScene.h"
#include "Player/Player.h"
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
#include"sky.h"
#include "Pose.h"
#include "GameCler.h"
#include "CheckPoint.h"

//�����͑O���錾�ł悢�I
//struct PathPoint;
//class Enemy;
class Goal;
class Stage;
class Coin;
class sky;
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
		State_Default,		//�f�t�H���g���
		State_StageChange,	//�X�e�[�W�J�ڒ�]
		State_Pose,
		State_TitleChange,	//�^�C�g���J�ڒ�
		State_GameClear,
		State_GameOver		//�Q�[���I�[�o�[
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
	CheckPoint* GetPoint()
	{
		return &m_point;
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
	int GetTimeScore()
	{
		return TimeScore;
	}
	/// <summary>
	/// �Q�[���̃X�e�[�g���Q�b�g
	/// </summary>
	/// <returns>���݂̃X�e�[�g</returns>
	const GameState GetState()
	{
		return m_gstate;
	}
	bool Contenyu()
	{
		return continuityflug;
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
	void GameFont();
private:

	GameState m_gstate = State_Default;
	int StageNo = 1;
	Player m_player;						//�v���C���[
	Pose m_pose;
	Goal m_goal;                            //�S�[��
	CheckPoint m_point;
	Coin* m_coin;                           //�R�C��
	Stage* m_stage;                         //�X�e�[�W
	sky*	m_cubemap;					//�L���[�u�}�b�v�N���X�̃|�C���^�[
	GameCamera m_gameCamera;				//�Q�[���J�����B
	RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	Level m_level;							//���x�����������B
	GameCler m_cler;						//�Q�[���N���A
	Gameover m_over;						//�Q�[���I�[�o�[
	HP m_hp;								//�v���C���[��HP
	bool Goal = false;						//�S�[������
	int GoalCount = 0;						//�S�[����ʂւ̑J�ڂ܂ł̎���
	CSoundSource m_stagebgm;				//�X�e�[�WBGM
	CSoundSource m_coinse;					//�R�C����SE
	CSoundSource m_kirakirase;				//�S�[���o������SE
	CSoundSource m_posese;
	bool SEflag = true;						//SE��炷���߂̃t���O
	bool flag = false;
	bool continuityflug = false;
	Sprite m_goalsprite;		
	Font m_font;					//�t�H���g
	Timer m_time;					//�^�C�}�[
	Title m_title;
	int GAMETIME = 200;				//�c�莞��
	int Score = 0;
	int TimeScore = 0;				//�^�C���̃X�R�A
	int taim = 0;						//�o�ߎ���
	bool ChangeFlag = false;
	wchar_t toubatu[256];
	float m_fontscale = 0.7f;
	PostEffect* m_postEffect;				//�|�X�g�G�t�F�N�g�B
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B

};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;
