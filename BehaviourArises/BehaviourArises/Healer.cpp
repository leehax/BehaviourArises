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
	if (!m_agent->GetPath().empty()) {
		{
			m_agent->GetPath().pop_back();
			m_agent->SetCurTile(m_agent->GetPath().back());
			std::cout << "MoveTo Running\n";
			return BT_State::Running;
		}
	}
	std::cout << "MoveTo Success\n";
	return BT_State::Success;

}


BT_Node::BT_State BT_SetDestination::Update()
{
	m_blackBoard->AddVector2i("TargetLocation", Vector2<int>(11, 9));
	std::cout << "SetDestination Success\n";
	return BT_State::Success;
}

BT_Node::BT_State BT_FindPath::Update()
{

	m_agent->FindPath(m_blackBoard->GetVector2i("TargetLocation"));
	std::cout << "FindPath Success\n";
	return BT_State::Success;
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

void Healer::CreateBehaviourTree()
{


	m_blackBoard->AddVector2i("HealerPosition", m_curTile->GetGridPos());
	m_behaviourTree = std::make_shared<BehaviourTree>(m_blackBoard);
	std::cout << "Healer Pos, received from BB" << m_blackBoard->GetVector2i("HealerPosition").x << m_blackBoard->GetVector2i("HealerPosition").y << '\n';


	auto sequencer0 = std::make_shared<BT_Sequencer>();



	auto setTarget = std::make_shared<BT_SetDestination>(m_blackBoard);
	auto findPath = std::make_shared<BT_FindPath>(m_blackBoard);
	auto moveTo = std::make_shared<BT_MoveTo>(m_blackBoard);
	m_behaviourTree->SetRoot(sequencer0);

	sequencer0->AddNodesAsChildren({ setTarget, findPath, moveTo });

	
	sequencer0->SetAgent(this);
}

void Healer::Update(float p_delta)
{
	m_behaviourTree->Update();
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
