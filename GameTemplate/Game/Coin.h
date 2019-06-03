#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Player/Player.h"
#include "Gate.h"

class Gate;
class Game;
class Player;
class Coin
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="player"></param>
	Coin(CVector3 pos, CQuaternion rot,Player* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Coin();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �R�C���擾����
	/// </summary>
	void CoinGet();
	/// <summary>
	/// �R�C���擾���
	/// </summary>
	/// <returns>
	/// true �擾
	/// false�@���擾
	/// </returns>
	bool GetCoinGet()
	{
		return CoinGetFlag;
	}
private:
	
	SkinModel m_model;									//���f���f�[�^
	CVector3 m_position = CVector3::Zero();             //���W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rotation = CQuaternion::Identity();   //��]�B
	CVector3 ambientColor = { 1.0f, 1.0f, 1.0f };		//�����̃J���[
	Player* m_player = nullptr;							//�v���C���[
	bool CoinGetFlag = false;							//�R�C���擾�t���O
	Effekseer::Effect* m_coinEffect = nullptr;
	Effekseer::Handle m_coinEffectHandle = -1;
	bool flag = false;
	float rotspeed = 10.0f;
	int CoinTime = 0;

};

