#pragma once
#include <memory>
#include <iostream>
#include "BlackBoard.h"
class Agent;
class BT_Node
{
public:
	virtual ~BT_Node() {};

	enum class BT_State{ Null, Success, Failure, Running,};

	virtual BT_State Update() = 0;
	virtual void Init(std::shared_ptr<Agent> p_agent, std::shared_ptr<BlackBoard> p_pBB);
protected:
	BT_State m_state = BT_State::Null;
	std::shared_ptr<Agent> m_agent = nullptr;
	std::shared_ptr<BlackBoard> m_privateBlackBoard = nullptr;
};

inline void BT_Node::Init(std::shared_ptr<Agent> p_agent, std::shared_ptr<BlackBoard> p_pBB)
{

	m_agent = p_agent;
	m_privateBlackBoard = p_pBB;
}

