#include "stdafx.h"
#include "BT_Leaf.h"
#include <iostream>


BT_Leaf::BT_Leaf(std::string p_name, int p_probability):m_name(p_name), m_probability(p_probability)
{
}


BT_Leaf::BT_Leaf(std::shared_ptr<BlackBoard> p_BB) : m_blackBoard(p_BB)
{
}

BT_Leaf::~BT_Leaf()
{
}

BT_Node::BT_State BT_Leaf::Update()
{

	if(std::rand()%100 <m_probability)
	{
		std::cout << m_name<<" Success\n";
		return BT_State::Success;
	}
	std::cout << m_name << " Failed\n";
	return BT_State::Failure;
}


