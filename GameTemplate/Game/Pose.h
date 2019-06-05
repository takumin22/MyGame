#pragma once
#include "Pose.h"
class Pose
{
public:
	Pose();
	~Pose();
	void Updata();
	void Draw();
	enum PouseState
	{
		State_Zokkou,
		State_Title
	};
	bool GetFlag()
	{
		return Flag;
	}
private:
	Sprite m_posesprite;
	Sprite m_yaji;
	PouseState m_pousestate = State_Zokkou;
	CVector3 m_pos = {-200.0f,-40.0f,0.0f };				//–îˆó‚Ìƒ|ƒWƒVƒ‡ƒ“}
	bool Flag = false;
};

