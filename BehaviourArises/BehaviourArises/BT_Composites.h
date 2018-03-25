#pragma once
#include "BT_Node.h"
#include <vector>

class BT_Composite:
	public BT_Node
{
public:
	virtual ~BT_Composite();

	void AddNodeAsChild(std::shared_ptr<BT_Node> p_node);
	void AddNodesAsChildren(std::vector<std::shared_ptr<BT_Node>> p_nodes);
	bool HasChildren() const;
	void Init(std::shared_ptr<Agent> p_agent, std::shared_ptr<BlackBoard> p_pBB) override;

protected:
	std::vector<std::shared_ptr<BT_Node>> m_childNodes;
};


class BT_Selector:
	public BT_Composite
{
public:
	BT_State Update() override;
};

class BT_SelectorMemorize :
	public BT_Composite
{
public:
	BT_State Update() override;
	void Terminate() override;
private:
	int m_index = 0;
};

class BT_Sequencer:
		public BT_Composite
{
public:
	BT_State Update() override;
};

class BT_SequencerMemorize :
	public BT_Composite
{
public:
	BT_State Update() override;
	void Terminate() override;
private:
	int m_index = 0;
};

class BT_Parallel:
	public BT_Composite
{
public: 
	BT_Parallel(int p_minSuccess, int p_minFail) :m_minSuccess(p_minSuccess), m_minFail(p_minFail) {};
	BT_State Update() override;

private:
	int m_minSuccess;
	int m_minFail;

};
