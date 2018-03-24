#pragma once
#include "BT_Leaf.h"
class BT_SetDestination :
	public BT_Leaf
{
public:
	BT_SetDestination(std::shared_ptr<BlackBoard> p_BB, std::shared_ptr<Vector2<int>> p_pos);
	~BT_SetDestination();
	BT_State Update() override;

private:
	std::shared_ptr<Vector2<int>> m_positionToSet = nullptr;
};

