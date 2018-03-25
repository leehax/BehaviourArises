#include "stdafx.h"
#include "BT_SetDestination.h"
#include "Agent.h"

BT_SetDestination::BT_SetDestination(std::shared_ptr<BlackBoard> p_BB, std::shared_ptr<Vector2<int>> p_pos):BT_Leaf(p_BB)
{
	m_positionToSet = p_pos;
}


BT_SetDestination::~BT_SetDestination()
{
}

BT_Node::BT_State BT_SetDestination::Update()
{
	if (m_positionToSet) {
		m_blackBoard->SetVector2i(m_agent->GetName() + "TargetPosition", *m_positionToSet);
		return BT_State::Success;
	}
	return BT_State::Failure;
}
