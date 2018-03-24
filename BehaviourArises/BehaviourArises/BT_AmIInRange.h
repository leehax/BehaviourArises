#pragma once
#include "BT_Leaf.h"
class BT_AmIInRange :
	public BT_Leaf
{
public:
	BT_AmIInRange(std::shared_ptr<BlackBoard> p_BB, int p_rangeToCheck, const std::string p_postionToCheck );
	~BT_AmIInRange();
	BT_State Update() override;
	
private:
	int m_rangeToCheck = 0;
	std::string m_positionToCheck = "";
};

