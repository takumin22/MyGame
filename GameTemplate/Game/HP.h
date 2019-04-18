#pragma once
#include "Sprite.h"
class Player;
class HP
{
public:
	HP();
	~HP();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �_���[�W�J�E���g���Z�b�g
	/// </summary>
	/// <param name="k">�_���[�W��</param>
	void SetDamageCount(int k)
	{
		DamageCount = k;
	}
private:
	Sprite m_hp;									//�̗͂̃X�v���C�g�f�[�^
	Sprite m_hp2;
	Sprite m_hp3;
	Sprite m_hp4;
	CVector3 m_hppos = { 300.0f,300.0f,0.0f };		//�̗͂̕\���|�W�V����
	CVector3 m_hppos2 = { 400.0f,300.0f,0.0f };
	CVector3 m_hppos3 = { 500.0f,300.0f,0.0f };
	CVector3 m_hppos4 = { 600.0f,300.0f,0.0f };
	Player* m_player = nullptr;						//�v���C���[
	int DamageCount = 0;							//�_���[�W�J�E���g

};

