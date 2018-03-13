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

void BT_Composite::AddNodesAsChildren(std::vector<std::shared_ptr<BT_Node>> p_nodes)
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

void BT_Composite::Init(std::shared_ptr<Agent> p_agent, std::shared_ptr<BlackBoard> p_pBB)
{
	std::cout << "Setting agent\n";
	m_agent = p_agent;
	m_privateBlackBoard = p_pBB;
	for (auto child : m_childNodes)
	{
		child->Init(p_agent, p_pBB);
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

	for (int i = 0; i < m_childNodes.size(); i++)
	{
		const auto state = m_childNodes[i]->Update();

		if (state != BT_State::Success)
		{
			return state;
		}

	}

	return BT_State::Success;
}

BT_Node::BT_State BT_SequencerMemorize::Update()
{
	if(!HasChildren())
	{
		return BT_State::Success;
	}
	
	for (int i = m_index; i < m_childNodes.size(); i++)
	{
		const auto state = m_childNodes[i]->Update();

		if (state != BT_State::Success)
		{
			if(state==BT_State::Running)
			{
				m_index = i;
			}
			return state;
		}
		
	}

	m_index = 0;
	return BT_State::Success;

}
