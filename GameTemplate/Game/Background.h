#pragma once
#include "physics/PhysicsStaticObject.h"
class Background
{
public:
	Background();
	~Background();
	void Draw();
private:
	SkinModel m_model;                     //�X�L�����f��
	PhysicsStaticObject m_phyStaticObject; //�ÓI�����I�u�W�F�N�g
};