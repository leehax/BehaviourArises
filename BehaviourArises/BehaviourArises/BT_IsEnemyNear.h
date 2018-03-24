#pragma once
#include "BT_Leaf.h"
class BT_IsEnemyNear :
	public BT_Leaf
{
public:
	BT_IsEnemyNear(std::shared_ptr<BlackBoard> p_BB, int p_range);
	~BT_IsEnemyNear();
	BT_State Update() override;

private:
	int m_range = 0;
};

