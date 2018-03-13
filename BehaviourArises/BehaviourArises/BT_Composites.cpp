#include "stdafx.h"
#include "BT_Composites.h"
#include <iostream>


BT_Composite::~BT_Composite()
{
}

void BT_Composite::AddNodeAsChild(std::shared_ptr<BT_Node> p_node)
{

	m_childNodes.push_back(p_node);
}

void BT_Composite::AddNodesAsChildren(std::initializer_list<std::shared_ptr<BT_Node>> && p_nodes)
{
	for(auto node : p_nodes)
	{
		AddNodeAsChild(node);
	}
}

bool BT_Composite::HasChildren() const
{
	return !m_childNodes.empty();
}

void BT_Composite::SetAgent(Agent* p_agent)
{
	std::cout << "Setting agent\n";
	m_agent = p_agent;
	for(auto child: m_childNodes)
	{
		child->SetAgent(p_agent);
	}
}

BT_Node::BT_State BT_Selector::Update()
{
	if(!HasChildren())
	{
		return BT_State::Success;
	}

	for(auto c:m_childNodes)
	{
		const auto state = c->Update();

		if(state != BT_State::Failure) 
		{
			return state;
		}

	}
	return BT_State::Failure;
}



BT_Node::BT_State BT_Sequencer::Update()
{
	if (!HasChildren())
	{
		return BT_State::Success;
	}

	for (auto c : m_childNodes)
	{
		const auto state = c->Update();

		if (state != BT_State::Success)
		{
			return state;
		}

	}

	return BT_State::Success;
}
