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
#include "BT_SetDestination.h"
#include "BT_FindPath.h"
#include "BT_Move.h"
#include "BT_AllyNeedsHealing.h"
#include "BT_Attack.h"
#include "BT_Heal.h"
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



Healer::Healer(IGridMap* p_world, Tile* p_tile, std::shared_ptr<BlackBoard> p_BB)
{
	m_visionRange = 3;
	m_maxHealth = 100.f;
	m_currentHealth = 100.f;

	m_curTile = p_tile;

	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../External/textures/Healer.png", 0, 0, 32, 32);

	m_world = p_world;
	m_pathFinding = std::make_shared<AStarPath>(m_world);
	m_blackBoard = std::make_shared<BlackBoard>();
	m_name = "Healer";
	m_collider = { m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, m_sprite->GetClip().w, m_sprite->GetClip().h };
	m_sensingAreaCollider = { m_curTile->GetWorldPos().x - m_visionRange*static_cast<int>(Config::TILE_SIZE), m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE) , (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE), (m_visionRange * 2+1) * static_cast<int>(Config::TILE_SIZE) };
}


Healer::~Healer()
{
}

void Healer::CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent)
{


	m_blackBoard->SetVector2i( m_name + "Position", m_curTile->GetGridPos());
	m_blackBoard->SetVector2i(m_name + "TargetLocation", m_blackBoard->GetVector2i("TankPosition"));
	m_behaviourTree = std::make_shared<BehaviourTree>(m_blackBoard);
	
	


	auto healAlly = std::make_shared<BT_Sequencer>();
	std::cout << healAlly << '\n';
	auto isAllyWounded = std::make_shared<BT_AllyNeedsHealing>(m_blackBoard);
	auto findPath = std::make_shared<BT_FindPath>(m_blackBoard);
	auto moveToTarget = std::make_shared<BT_Move>(m_blackBoard);
	auto heal = std::make_shared<BT_Heal>(m_blackBoard);

	auto rest = std::make_shared<BT_Sequencer>();
	std::cout << rest << '\n';

	//healer should have the following behaviors
	//heal ally
	//hide behind allies
	//flee
	//fight
	//follow the leader
	rest->AddNodesAsChildren({ findPath,moveToTarget,heal });

	healAlly->AddNodesAsChildren({ isAllyWounded,findPath,moveToTarget,heal });

	auto root = std::make_shared<BT_Selector>();
	root->AddNodesAsChildren({ healAlly, rest });

	m_behaviourTree->Init(root, p_sharedPtrToThisAgent);


}

void Healer::Update(float p_delta)
{
	
	m_behaviourTreeTickTime -= p_delta;
	if (m_behaviourTreeTickTime <= 0) {
	
		Sense();
		m_blackBoard->SetVector2i(m_name + "TargetLocation", m_blackBoard->GetVector2i("TankPosition"));
		std::vector<BT_Node*> foo; //TODO: fix this, creating an empty vector because too lazy to refactor the behavior tree class
		m_behaviourTree->Update(foo);
		m_behaviourTreeTickTime = 1.0f;
		m_sensingAreaCollider.x = m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_sensingAreaCollider.y = m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_collider.x = m_curTile->GetWorldPos().x;
		m_collider.y = m_curTile->GetWorldPos().y;
	}
}

void Healer::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y ,1);
	//m_pathFinding->Draw();
	m_drawManager->DrawRect(m_sensingAreaCollider, 255, 0, 0, 0);
	m_drawManager->DrawRect(m_collider, 0,0,255, 0);
}

void Healer::Sense()
{
	if (!m_sensedAgents.empty()) {
		for (auto a : m_sensedAgents)
		{
			if (a->GetName() == "Tank")
			{
				m_blackBoard->SetVector2i("TankPosition", a->GetCurrentTile()->GetGridPos());
				m_blackBoard->SetInt("TankHealth", a->GetHealth());
			}
			else if(a->GetName() == "Bat")
			{
				m_sensedEnemies.push_back(a);
			}
		}
	}
	else
	{
		m_sensedEnemies.clear();
	}
}


