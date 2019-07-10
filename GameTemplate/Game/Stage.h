#pragma once


#include "Enemy.h"
#include "Player/Player.h"
#include "Scaffold.h"
#include "TurnScaffold.h"
#include "IScene.h"
#include "level/Level.h"
#include "Spring.h"
#include "Coin.h"
#include "Goal.h"
#include "Gate.h"
#include "EnemyFly.h"
class Game;
class Enemy;
class EnemyFly;
class Stage 
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="No">�X�e�[�W�̃i���o�[</param>
	Stage(int No);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Stage();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	void StageSE();
	/// <summary>
	/// �R�C���J�E���g���擾
	/// </summary>
	/// <returns>�R�C���̎擾��</returns>
	int GetCoinCount()
	{
		return CoinCount;
	}
	/// <summary>
	/// �G�l�~�[�J�E���g���Q�b�g
	/// </summary>
	/// <returns>�G�l�~�[��|������</returns>
	int GetEnemyCount()
	{
		return EnemyCount;
	}
	int GetRedCoinCount()
	{
		return RedCoinCount;
	}
	/// <summary>
	/// �X�R�A���Q�b�g
	/// </summary>
	/// <returns>���݂̃X�R�A</returns>
	int GetScore() 
	{
		return Score;
	}

private:

	int StageCount = 0;
	Level m_level;								//���x�����������B
	Goal* m_goal;
	std::vector< Enemy* > m_enemyList;			//�G�l�~�[�̃��X�g�B
	std::vector< Scaffold*> m_sacaffoldList;	//����̃��X�g�B
	std::vector< Goal*> m_goalList;
	std::vector< Spring*> m_springList;			//�o�l���X�g
	std::vector< Coin*> m_coinList;				//�R�C���̃��X�g
	std::vector<TurnScaffold*> m_turnscaffold;	//��]����̃��X�g
	std::vector<Gate*> m_gateList;				//�Q�[�g�̃��X�g
	std::vector<RedCoin*> m_rcoinList;			//���b�h�R�C���̃��X�g
	std::vector<EnemyFly*> m_enemyflyList;
	CSoundSource m_edamegese;					//�G�l�~�[�̃_���[�WSE
	CSoundSource m_hakkense;					//�W�����v��o������SE
	CSoundSource m_coinse;						//�R�C���̎擾SE
	int CoinCount = 0;							//�擾�R�C����
	int RedCoinCount = 0;
	int EnemyCount = 0;							//�|�����G�l�~�[��
	bool SEflag = true;							//SE��炷���̃t���O
	int Score = 0;								//�X�R�A
	int StageNo = 0;
	int StageNo1 = 0;
	int StageNo2 = 0;
	int StageNo3 = 0;
	int StageNo4 = 0;
	int StageNo5 = 0;
	int StageNo6 = 0;
};

