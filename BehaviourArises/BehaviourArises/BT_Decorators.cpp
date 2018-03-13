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

void BT_Decorator::SetAgent(Agent* p_agent)
{
	m_agent = p_agent;
	m_childNode->SetAgent(p_agent);
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
