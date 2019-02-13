#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Player.h"
class Game;
class Player;
class Coin
{
public:
	Coin(CVector3 pos, CQuaternion rot,Player* player);
	~Coin();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// ��]
	/// </summary>
	void Turn();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �R�C���擾����
	/// </summary>
	void CoinGet();
	bool GetCoinGet()
	{
		return CoinGetFlag;
	}
private:
	
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();             //���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();   //��]�B
	Player* m_player = nullptr; //�v���C���[
	bool CoinGetFlag = false; //�R�C���擾�t���O
	Game* m_game = nullptr;

};

