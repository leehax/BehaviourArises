#pragma once
#include "BT_Leaf.h"
class BT_MoveAway :
	public BT_Leaf
{
public:
	BT_MoveAway(std::shared_ptr<BlackBoard> p_BB, Vector2<int> p_posToMoveAwayFrom);
	~BT_MoveAway();
	BT_State Update(std::vector<BT_Node*>& p_openNodes) override;
private:
	Vector2<int> m_posToMoveAwayFrom = Vector2<int>();
};

