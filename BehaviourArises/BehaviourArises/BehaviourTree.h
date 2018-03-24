#pragma once
#include "BT_Node.h"
class BlackBoard;
class BehaviourTree:
		public BT_Node
{
public:
	BehaviourTree();
	BehaviourTree(const std::shared_ptr<BT_Node> & p_rootNode);
	BehaviourTree(const std::shared_ptr<BlackBoard> & p_publicBlackBoard);
	BehaviourTree(const std::shared_ptr<BT_Node> & p_rootNode, const std::shared_ptr<BlackBoard> & p_publicBlackBoard);
	~BehaviourTree();

	BT_State Update() override;

	void Init(const std::shared_ptr<BT_Node>& p_rootNode, std::shared_ptr<Agent> p_agent);
	std::shared_ptr<BlackBoard> GetPrivateBlackBoard();
	std::shared_ptr<BlackBoard> GetPublicBlackBoard();
	void SetPublicBlackBoard(const std::shared_ptr<BlackBoard>& p_publicBlackBoard);

private:
	std::shared_ptr<BT_Node> m_rootNode = nullptr;
	std::shared_ptr<BlackBoard> m_privateBlackBoard = nullptr;
	std::shared_ptr<BlackBoard> m_publicBlackBoard = nullptr;
};

