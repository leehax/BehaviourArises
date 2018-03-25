#pragma once
#include "BT_Leaf.h"
class BT_MoveToSafety :
	public BT_Leaf
{
public:
	BT_MoveToSafety(std::shared_ptr<BlackBoard> p_BB, const std::string p_posToMoveAwayFromName);
	~BT_MoveToSafety();
	BT_State Update() override;
private:
	std::string m_posToMoveAwayFromName = "";
};

