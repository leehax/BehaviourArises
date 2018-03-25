#pragma once
#include "BT_Node.h"
class BT_Decorator 
	:public BT_Node
{
public:
	virtual ~BT_Decorator();

	void SetChild(std::shared_ptr<BT_Node> p_node);
	std::shared_ptr<BT_Node> GetChild() const;
	bool HasChild() const;
	void Init(std::shared_ptr<Agent> p_agent,std::shared_ptr<BlackBoard> p_pBB) override;
protected:

	std::shared_ptr<BT_Node> m_childNode;

};


class BT_Inverter: //inverts child return, fail > success and vice versa. If child is running, returns running
	public BT_Decorator
{
public:
	BT_State Update() override;
};

class BT_Repeater: //repeats child, returns the childs state
	public BT_Decorator
{
public:
	BT_Repeater(unsigned int p_repeatLimit = 0); //default repeats infinetly
	BT_State Update() override;

private:
	unsigned int m_repeatLimit = 0;
};

class BT_RepeaterFail: //repeats until child fails, returns success
		public BT_Decorator
{
public: 
	BT_State Update() override;

};

class BT_RepeaterSuccess: //repeats until child succeeds, returns success
	public BT_Decorator
{
public:
	BT_State Update() override;
};

class BT_Succeeder: //always returns success
	public BT_Decorator
{
public:
	BT_State Update() override;
};

class BT_Failer:  //poor guy, always failing no matter what
	public BT_Decorator
{
public:
	BT_State Update() override;
};

