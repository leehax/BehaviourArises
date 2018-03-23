#include "stdafx.h"
#include "BT_SetTargetAgent.h"
#include "Agent.h"

BT_SetTargetAgent::BT_SetTargetAgent(std::shared_ptr<BlackBoard> p_BB, const std::string p_agentName): BT_Leaf(p_BB)
{
	m_agentName = p_agentName;
}


BT_SetTargetAgent::~BT_SetTargetAgent()
{
}

BT_Node::BT_State BT_SetTargetAgent::Update(std::vector<BT_Node*>& p_openNodes)
{
	m_blackBoard->SetVector2i(m_agent->GetName() + "TargetPosition", m_blackBoard->GetVector2i(m_agentName+"Position"));
	m_blackBoard->SetAgent(m_agent->GetName() + "TargetAgent", m_blackBoard->GetAgent(m_agentName));
	return BT_State::Success;
}
