#pragma once
#include "BT_Node.h"
#include <string>
class BlackBoard;
class BT_Leaf :
	public BT_Node
{
public:
	BT_Leaf(std::string p_name, int p_probablity);
	BT_Leaf(std::shared_ptr<BlackBoard> p_BB);
	virtual ~BT_Leaf();
	BT_State Update() override;

protected:
	std::shared_ptr<BlackBoard> m_blackBoard;
	std::string m_name;
	int m_probability;
};

