#include "stdafx.h"
#include "BehaviourTree.h"
#include "BlackBoard.h"
#include <algorithm>

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

BT_Node::BT_State BehaviourTree::Update(std::vector<BT_Node*>& p_openNodes)
{
	std::vector<BT_Node*> lastOpenNodes = m_privateBlackBoard->GetBTNodes("LastOpenNodes");
	std::vector<BT_Node*> currOpenNodes = std::vector<BT_Node*>();

	m_rootNode->Update(currOpenNodes);

	int openOffset = -1;
	for (int i = 0; i < std::min(lastOpenNodes.size(), currOpenNodes.size()); i++)
	{
		if(lastOpenNodes[i]!=currOpenNodes[i])
		{
			std::cout << "Mismatch at element: " << i << '\n';
			openOffset = i;
			break;
		}
	}
	if (openOffset >= 0) {
		for (int i = openOffset; i < lastOpenNodes.size(); i++)
		{
			lastOpenNodes[i]->Terminate();
		}
	}
	m_privateBlackBoard->SetBTNodes("LastOpenNodes", currOpenNodes);


	return BT_State::Success;
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
