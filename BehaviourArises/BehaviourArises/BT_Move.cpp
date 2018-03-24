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
		std::cout << "MoveTo Running, target: " << m_blackBoard->GetVector2i(m_agent->GetName() + "TargetPosition").x << m_blackBoard->GetVector2i(m_agent->GetName() + "TargetPosition").y << '\n';
		return BT_State::Running;
		
	
	}
	//m_agent->ClearPath();
	std::cout << "MoveTo Success\n";
	return BT_State::Success;
}
