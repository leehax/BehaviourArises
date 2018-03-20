#include "stdafx.h"
#include "BT_Defend.h"


BT_Defend::BT_Defend(std::shared_ptr<BlackBoard> p_BB) : BT_Leaf(p_BB)
{
}


BT_Defend::~BT_Defend()
{
}

BT_Node::BT_State BT_Defend::Update(std::vector<BT_Node*>& p_openNodes)
{
	std::cout << "Defending, damage reduction set to 100 \n";
	return BT_State::Success;
}
