#pragma once
class Player;
class CheckPoint
{
public:
	CheckPoint();
	~CheckPoint();
	void CheckGet();
	void Update();
	void Draw();
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	SkinModel m_model;
	Player* m_player = nullptr;							//ÉvÉåÉCÉÑÅ[
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CSoundSource m_getse;
	bool seflag = true;
	CVector3 m_scale = CVector3::One();
	bool CheckFlag = false;
};

