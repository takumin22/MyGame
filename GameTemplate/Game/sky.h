#pragma once

class sky
{
public:
	sky();
	~sky();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �X�P�[�����Đݒ肷��֐�
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// �|�W�V�������Z�b�g����֐�
	/// </summary>
	/// <param name="pos">�|�W�V����(CVector3)</param>
	void SetPositon(CVector3& pos)
	{
		m_position = pos;
	}

private:
	SkinModel			m_skinmodel;					//�X�L�����f��
	CVector3			m_scale;						//�X�P�[��
	CVector3			m_position = CVector3::Zero();	//�|�W�V����
	ID3D11ShaderResourceView*	m_srv = nullptr;	//SRV
	bool						m_isValid = false;	//�L�����ǂ����̃t���O
};

