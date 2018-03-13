#include "stdafx.h"
#include "BehaviourTree.h"
#include "BlackBoard.h"

BehaviourTree::BehaviourTree() : m_privateBlackBoard(std::make_shared<BlackBoard>())
{
}

BehaviourTree::BehaviourTree(const std::shared_ptr<BT_Node>& p_rootNode) : m_rootNode(p_rootNode), m_privateBlackBoard(std::make_shared<BlackBoard>())
{
}

BehaviourTree::BehaviourTree(const std::shared_ptr<BlackBoard>& p_publicBlackBoard) : m_privateBlackBoard(std::make_shared<BlackBoard>()), m_publicBlackBoard(p_publicBlackBoard)
{
}

BehaviourTree::BehaviourTree(const std::shared_ptr<BT_Node>& p_rootNode,
	const std::shared_ptr<BlackBoard>& p_publicBlackBoard) : m_rootNode(p_rootNode), m_privateBlackBoard(std::make_shared<BlackBoard>()), m_publicBlackBoard(p_publicBlackBoard)
{
}

BT_Node::BT_State BehaviourTree::Update()
{
	return m_rootNode->Update();
}

void BehaviourTree::Init(const std::shared_ptr<BT_Node>& p_rootNode, std::shared_ptr<Agent> p_agent)
{

	m_rootNode = p_rootNode;
	m_rootNode->Init(p_agent, m_privateBlackBoard);
}



std::shared_ptr<BlackBoard> BehaviourTree::GetPrivateBlackBoard()
{
	return m_privateBlackBoard;
}

std::shared_ptr<BlackBoard> BehaviourTree::GetPublicBlackBoard()
{
	return m_publicBlackBoard;
}

void BehaviourTree::SetPublicBlackBoard(const std::shared_ptr<BlackBoard>& p_publicBlackBoard)
{
	m_publicBlackBoard = p_publicBlackBoard;
}


BehaviourTree::~BehaviourTree()
{

}
