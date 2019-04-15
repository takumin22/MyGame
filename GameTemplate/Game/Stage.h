#pragma once


#include "Enemy.h"
#include "Player.h"
#include "Scaffold.h"
#include "TurnScaffold.h"
#include "IScene.h"
#include "level/Level.h"
#include "Spring.h"
#include "Coin.h"
#include "Goal.h"
#include "Gate.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
class Game;
class Enemy;
class Stage 
{
public:
	Stage(int No);
	~Stage();
	void Update();
	void Draw();
	void StageMove();
	void StageSE();
	void SetCount(int StageNo)
	{
		StageCount = StageNo;
	}
	int GetCount()
	{
		return StageCount;
	}
	int GetCoinCount()
	{
		return CoinCount;
	}
	int GetEnemyCount()
	{
		return EnemyCount;
	}
	int GetScore() 
	{
		return Score;
	}
	Scaffold* GetScaffold(int i)
	{
		return m_sacaffoldList[i];
	}
	Enemy* GetEnemyList(int j)
	{
		return m_enemyList[j];
	}
private:

	int StageCount = 0;
	Level m_level;							//���x�����������B
	std::vector< Enemy* > m_enemyList;		//�G�l�~�[�̃��X�g�B
	std::vector< Scaffold*> m_sacaffoldList; //����̃��X�g�B
	std::vector< Spring*> m_springList;   //�o�l���X�g
	std::vector< Coin*> m_coinList; //�R�C���̃��X�g
	std::vector<TurnScaffold*> m_turnscaffold; //��]����̃��X�g
	std::vector<Gate*> m_gateList;  //�Q�[�g�̃��X�g
	CSoundSource m_edamegese;//�G�l�~�[�̃_���[�WSE
	CSoundSource m_hakkense;//�W�����v��o������SE
	int CoinCount = 0;//�擾�R�C����
	int EnemyCount = 0;//�|�����G�l�~�[��
	bool SEflag = true;
	int Score = 0;//�X�R�A
};

