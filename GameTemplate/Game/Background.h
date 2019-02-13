#pragma once
#include "physics/PhysicsStaticObject.h"
class Background
{
public:
	Background();
	~Background();
	void Draw();
private:
	SkinModel m_model;                     //スキンモデル
	PhysicsStaticObject m_phyStaticObject; //静的物理オブジェクト
};