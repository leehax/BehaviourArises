#include "stdafx.h"
#include "BT_Move.h"
#include "Tile.h"
#include "Agent.h"
BT_Move::BT_Move(std::shared_ptr<BlackBoard> p_BB):BT_Leaf(p_BB)
{
}


BT_Move::~BT_Move()
{
}

BT_Node::BT_State BT_Move::Update()
{
	

	if (m_agent->MoveToNextTile()){
		return BT_State::Running;
		
	}
	return BT_State::Success;
}
