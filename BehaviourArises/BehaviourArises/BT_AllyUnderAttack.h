#pragma once
#include "BT_Leaf.h"
class BT_AllyUnderAttack :
	public BT_Leaf
{
public:
	BT_AllyUnderAttack(std::shared_ptr<BlackBoard> p_BB, const std::string p_allyName);
	~BT_AllyUnderAttack();
	BT_State Update() override;

private:
	std::string m_allyName = "";
};

