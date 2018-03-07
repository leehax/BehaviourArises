#pragma once
#include "BT_Node.h"
#include <vector>

class BT_Composite:
	public BT_Node
{
public:
	virtual ~BT_Composite();

	void AddNodeAsChild(std::shared_ptr<BT_Node> p_node);
	void AddNodesAsChildren(std::initializer_list<std::shared_ptr<BT_Node>>&& p_nodes);
	bool HasChildren() const;


protected:
	std::vector<std::shared_ptr<BT_Node>> m_childNodes;
};


class BT_Selector:
	public BT_Composite
{
public:
	BT_State Update() override;
};

class BT_Sequencer:
		public BT_Composite
{
public:
	BT_State Update() override;
};
