#pragma once
#include "BT_Leaf.h"
class BT_SetDestination :
	public BT_Leaf
{
public:
	BT_SetDestination(std::shared_ptr<BlackBoard> p_BB, Vector2<int> p_pos);
	~BT_SetDestination();
	BT_State Update(std::vector<BT_Node*>& p_openNodes) override;

private:
	Vector2<int> m_positionToSet = Vector2<int>();
};

