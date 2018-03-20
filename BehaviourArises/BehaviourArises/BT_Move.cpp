#include "stdafx.h"
#include "BT_Move.h"
#include "Tile.h"

BT_Move::BT_Move(std::shared_ptr<BlackBoard> p_BB):BT_Leaf(p_BB)
{
}


BT_Move::~BT_Move()
{
}

BT_Node::BT_State BT_Move::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	if (m_agent->GetCurrentTile()->GetGridPos() != m_blackBoard->GetVector2i(m_agent->GetName()+"TargetLocation")) {
		m_agent->MoveToNextTile();
		std::cout << "MoveTo Running, target: " << m_blackBoard->GetVector2i(m_agent->GetName() + "TargetLocation").x << m_blackBoard->GetVector2i(m_agent->GetName() + "TargetLocation").y << '\n';
		return BT_State::Running;
		
	
	}
	m_agent->ClearPath();
	std::cout << "MoveTo Success\n";
	return BT_State::Success;
}
