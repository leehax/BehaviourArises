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
#include "BT_AmIInRange.h"
#include "BT_AllyUnderAttack.h"
#include "BT_MoveAway.h"
#include "BT_SetTargetAgent.h"
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
	m_blackBoard = p_BB;
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
	m_behaviourTree = std::make_unique<BehaviourTree>(m_blackBoard);
	
	
	auto flee = std::make_shared<BT_Sequencer>();
	auto amIUnderAttack = std::make_shared<BT_AllyUnderAttack>(m_blackBoard, m_name);
	auto moveAway = std::make_shared<BT_MoveAway>(m_blackBoard, m_blackBoard->GetVector2i("EnemyAttacking" + m_name + "Position"));

	
	auto healAlly = std::make_shared<BT_Sequencer>();
	auto inRangeToheal = std::make_shared<BT_AmIInRange>(m_blackBoard, 2);
	auto rangeInverter = std::make_shared<BT_Inverter>();
	auto healAllySelector = std::make_shared<BT_Selector>();
	auto moveToHeal = std::make_shared<BT_Sequencer>();


	auto isAllyWounded = std::make_shared<BT_AllyNeedsHealing>(m_blackBoard);
	auto findPath = std::make_shared<BT_FindPath>(m_blackBoard);
	auto moveTowards = std::make_shared<BT_Move>(m_blackBoard);
	auto heal = std::make_shared<BT_Heal>(m_blackBoard);

	auto setTargetToTank = std::make_shared<BT_SetTargetAgent>(m_blackBoard, "Tank");
	
	auto followTheLeader = std::make_shared<BT_Sequencer>();


	//healer should have the following behaviors
	//heal ally
	//hide behind allies
	//flee
	//fight
	//follow the leader

	flee->AddNodesAsChildren({ amIUnderAttack,moveAway,moveTowards });
	followTheLeader->AddNodesAsChildren({ setTargetToTank, findPath, moveTowards });

	rangeInverter->SetChild(inRangeToheal);
	moveToHeal->AddNodesAsChildren({ rangeInverter,findPath,moveTowards });
	healAllySelector->AddNodesAsChildren({ moveToHeal, heal });
	healAlly->AddNodesAsChildren({ isAllyWounded, healAllySelector });

	auto root = std::make_shared<BT_Selector>();
	root->AddNodesAsChildren({ flee,healAlly, followTheLeader });

	m_behaviourTree->Init(root, p_sharedPtrToThisAgent);


}


void Healer::Update(float p_delta)
{
	
	m_behaviourTreeTickTime -= p_delta;
	if (m_behaviourTreeTickTime <= 0) {
	
		Sense();
		m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
		//m_blackBoard->SetVector2i(m_name + "TargetPosition", m_blackBoard->GetVector2i("TankPosition"));
		std::vector<BT_Node*> foo; //TODO: fix this, creating an empty vector because too lazy to refactor the behavior tree class
		m_behaviourTree->Update(foo);
		m_sensingAreaCollider.x = m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_sensingAreaCollider.y = m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_collider.x = m_curTile->GetWorldPos().x;
		m_collider.y = m_curTile->GetWorldPos().y;

		m_behaviourTreeTickTime = 1.0f;

	
		m_blackBoard->SetBool(m_name + "UnderAttack", false);
	}
	if(m_iFrame>0)
	{
		m_iFrame -= p_delta;
	}
}

void Healer::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y ,1);
	//m_pathFinding->Draw();
	//m_drawManager->DrawRect(m_sensingAreaCollider, 255, 0, 0, 0);
	//m_drawManager->DrawRect(m_collider, 0,0,255, 0);
}

void Healer::Sense()
{
	if (!m_sensedAgents.empty()) {
		for (auto a : m_sensedAgents)
		{
			auto sptr = a.lock();
			if (sptr) {
				if (sptr->GetName() == "Bat")
				{
					m_sensedEnemies.push_back(sptr);

				}
			}
		}
	}

}

void Healer::OnCollision(std::weak_ptr<Agent> p_other)
{
	auto sptr = p_other.lock();
	if(sptr->GetName()=="Bat" && m_iFrame<=0)
	{
		m_blackBoard->SetBool(m_name + "UnderAttack", true);
		m_blackBoard->SetAgent("EnemyAttacking" + m_name, sptr);
		m_blackBoard->SetVector2i("EnemyAttacking" + m_name + "Position", sptr->GetGridPos());
		std::cout << "Collided with bat\n";
		m_iFrame = 1.0f;
	}
}

void Healer::NotColliding(std::weak_ptr<Agent> p_other)
{
	auto sptr = p_other.lock();
	if (sptr->GetName() == "Bat" )
	{
		m_blackBoard->SetBool(m_name + "UnderAttack", false);
		
	}
}

void Healer::Attack(std::weak_ptr<Agent> p_target)
{
}


