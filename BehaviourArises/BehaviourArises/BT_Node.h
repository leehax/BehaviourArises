#pragma once
#include <memory>
#include <iostream>
class Agent;
class BT_Node
{
public:
	virtual ~BT_Node() {};

	enum class BT_State{ Null, Success, Failure, Running,};

	virtual BT_State Update() = 0;
	virtual void SetAgent(Agent* p_agent);
protected:
	BT_State m_state = BT_State::Null;
	Agent* m_agent;
};

inline void BT_Node::SetAgent(Agent* p_agent)
{

	m_agent = p_agent;
}

