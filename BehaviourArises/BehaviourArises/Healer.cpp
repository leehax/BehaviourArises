#include "stdafx.h"
#include "Healer.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "ServiceLocator.h"
#include "Tile.h"
#include "BehaviourTree.h"
#include "AStarPath.h"
#include "BlackBoard.h"
#include <iostream>

// MoveTo(Agent*, "targetIdentifier")
/*
   Run()
{
agent.position = calculateddirection * agent.bb.agentspeed;
}

new FindTarget(varioustypes, "woundedAlly"));
new calpath()
new MoveTo(&healer, "woundedAlly")
 */


BT_Node::BT_State BT_MoveTo::Update()
{
	//m_agent->SetCurTile()
	if (m_agent->GetCurrentTile()->GetGridPos()!=m_blackBoard->GetVector2i("TargetLocation")) {
		m_agent->MoveToNextTile();
		std::cout << "MoveTo Running\n";
		return BT_State::Running;
	}
	m_agent->ClearPath();
	std::cout << "MoveTo Success\n";
	return BT_State::Success;

}


BT_Node::BT_State BT_SetDestination::Update()
{
	m_blackBoard->SetVector2i("TargetLocation", m_target);
	std::cout << "SetDestination Success\n";
	return BT_State::Success;
}

BT_Node::BT_State BT_FindPath::Update()
{


	if(m_agent->FindPath(m_blackBoard->GetVector2i("TargetLocation")))
	{
		std::cout << "FindPath Success\n";
		return BT_State::Success;
	}
		
	std::cout << "FindPath Fail\n";
	return BT_State::Failure;
	
}

Healer::Healer(IGridMap* p_world, Tile* p_tile)
{
	m_visionRange = 5;
	m_maxHealth = 100.f;
	m_currentHealth = 100.f;

	m_curTile = p_tile;

	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../External/textures/Healer.png", 0, 0, 32, 32);

	m_world = p_world;
	m_pathFinding = std::make_shared<AStarPath>(m_world);
	m_blackBoard = std::make_shared<BlackBoard>();
}


Healer::~Healer()
{
}

void Healer::CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent)
{


	m_blackBoard->SetVector2i("HealerPosition", m_curTile->GetGridPos());
	m_behaviourTree = std::make_shared<BehaviourTree>(m_blackBoard);
	std::cout << "Healer Pos, received from BB" << m_blackBoard->GetVector2i("HealerPosition").x << m_blackBoard->GetVector2i("HealerPosition").y << '\n';


	auto patrolSequence = std::make_shared<BT_SequencerMemorize>();


	auto moveToA = std::make_shared<BT_SequencerMemorize>();
	auto setTargetA = std::make_shared<BT_SetDestination>(m_blackBoard,Vector2<int>(11,9));
	auto findPath = std::make_shared<BT_FindPath>(m_blackBoard);
	auto moveTo = std::make_shared<BT_MoveTo>(m_blackBoard);

	auto moveToB = std::make_shared<BT_SequencerMemorize>();
	auto setTargetB = std::make_shared<BT_SetDestination>(m_blackBoard, Vector2<int>(2, 11));
	auto moveToC = std::make_shared<BT_SequencerMemorize>();
	auto setTargetC = std::make_shared<BT_SetDestination>(m_blackBoard, Vector2<int>(20, 20));
	moveToA->AddNodesAsChildren({ setTargetA, findPath, moveTo });
	moveToB->AddNodesAsChildren({ setTargetB, findPath, moveTo });
	moveToC->AddNodesAsChildren({ setTargetC, findPath, moveTo });

	patrolSequence->AddNodesAsChildren({ moveToA,moveToB,moveToC });
	m_behaviourTree->Init(patrolSequence, p_sharedPtrToThisAgent);

}

void Healer::Update(float p_delta)
{
	m_behaviourTreeTickTime -= p_delta;
	if (m_behaviourTreeTickTime <= 0) {
		m_behaviourTree->Update();
		m_behaviourTreeTickTime = 1.0f;
	}
}

void Healer::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y ,1);
	m_pathFinding->Draw();
}

void Healer::Sense()
{
}

void Healer::MoveTo(Tile* p_tile)
{
	//m_pathFinding->FindPath(m_curTile, p_tile);

}
