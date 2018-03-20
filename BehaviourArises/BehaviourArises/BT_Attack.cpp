#include "stdafx.h"
#include "BT_Attack.h"


BT_Attack::BT_Attack(std::shared_ptr<BlackBoard> p_BB) :BT_Leaf(p_BB)
{
}


BT_Attack::~BT_Attack()
{
}

BT_Node::BT_State BT_Attack::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	std::cout << "Attacking\n";
	return BT_State::Success;
}
