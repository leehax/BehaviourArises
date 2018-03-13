#include "stdafx.h"
#include "BT_Decorators.h"


BT_Decorator::~BT_Decorator()
{
}

void BT_Decorator::SetChild(std::shared_ptr<BT_Node> p_node)
{
	m_childNode = p_node;
}

std::shared_ptr<BT_Node> BT_Decorator::GetChild() const
{
	return m_childNode;
}

bool BT_Decorator::HasChild() const
{
	return m_childNode != nullptr;
}

void BT_Decorator::Init(std::shared_ptr<Agent> p_agent, std::shared_ptr<BlackBoard> p_pBB)
{
	m_agent = p_agent;
	m_privateBlackBoard = p_pBB;
	m_childNode->Init(p_agent, p_pBB);
}



BT_Node::BT_State BT_Inverter::Update()
{
	auto state = GetChild()->Update();

	if (state == BT_State::Success) 
	{
		return BT_State::Failure;
	}
	if(state == BT_State::Failure)
	{
		return BT_State::Success;
	}
	
	return state;
}

BT_Repeater::BT_Repeater(unsigned p_repeatLimit)
{
}

BT_Node::BT_State BT_Repeater::Update()
{
	if(m_repeatLimit==0)
	{
		while (true)
		{
			GetChild()->Update();
		}

	}
	else
	{
		for(int i=0; i<m_repeatLimit; i++)
		{
			GetChild()->Update();
		}
		return GetChild()->Update();
	}
}

BT_Node::BT_State BT_RepeaterFail::Update()
{
	while(GetChild()->Update()!=BT_State::Failure)
	{
	}
	return BT_State::Success;
}

BT_Node::BT_State BT_RepeaterSuccess::Update()
{
	while(GetChild()->Update()!=BT_State::Success)
	{
		
	}
	return BT_State::Success;
}

BT_Node::BT_State BT_Succeeder::Update()
{
	GetChild()->Update();
	return BT_State::Success;
}

BT_Node::BT_State BT_Failer::Update()
{
	GetChild()->Update();
	return BT_State::Failure;
}
