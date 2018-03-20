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



BT_Node::BT_State BT_Inverter::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	auto state = GetChild()->Update(p_openNodes);

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

BT_Node::BT_State BT_Repeater::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	if(m_repeatLimit==0)
	{
		while (true)
		{
			GetChild()->Update(p_openNodes);
		}

	}
	else
	{
		for(int i=0; i<m_repeatLimit; i++)
		{
			GetChild()->Update(p_openNodes);
		}
		return GetChild()->Update(p_openNodes);
	}
}

BT_Node::BT_State BT_RepeaterFail::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	while(GetChild()->Update(p_openNodes)!=BT_State::Failure)
	{
	}
	return BT_State::Success;
}

BT_Node::BT_State BT_RepeaterSuccess::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	while(GetChild()->Update(p_openNodes)!=BT_State::Success)
	{
		
	}
	return BT_State::Success;
}

BT_Node::BT_State BT_Succeeder::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	GetChild()->Update(p_openNodes);
	return BT_State::Success;
}

BT_Node::BT_State BT_Failer::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	GetChild()->Update(p_openNodes);
	return BT_State::Failure;
}
