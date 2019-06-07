#pragma once
#include "IScene.h"
#include "Sprite.h"
#include "Fade.h"
class StageSelect : public IScene
{
public:
	StageSelect();
	~StageSelect();
	void Update();
	void Draw();
	enum Select
	{
		State_Stage01,
		State_Stage02,
		State_Title
	};
private:
	SkinModel m_model;
	SkinModel m_model1;
	Sprite m_sprite;
	Select m_select = State_Stage01;
	CVector3 m_position = CVector3::Zero();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();					//拡大率。
	CVector3 m_position1 = {-300.0f,0.0f,0.0f};				//座標。
	CQuaternion m_rotation1 = CQuaternion::Identity();
	CVector3 m_scale1 = CVector3::One();					//拡大率。
	float m_mojiscale;
	bool flag = false;
	bool StratFlag = false;
	wchar_t moji[256];
	float m_fontsize = 4.0f;
	Font m_font;					//フォント
};

