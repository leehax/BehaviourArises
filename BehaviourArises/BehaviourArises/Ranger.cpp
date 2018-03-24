#include "stdafx.h"
#include "Ranger.h"
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
#include "BT_Composites.h"
#include "BT_Decorators.h"
#include "BT_Leaf.h"
#include "BT_SetDestination.h"
#include "BT_FindPath.h"
#include "BT_Move.h"
#include "BT_AmIInRange.h"
#include "BT_Attack.h"
#include "BT_IsEnemyNear.h"
#include "BT_SetTargetAgent.h"

Ranger::Ranger(IGridMap* p_world, Tile* p_tile, std::shared_ptr<BlackBoard> p_BB)
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
	m_name = "Ranger";
	m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
	m_blackBoard->SetInt(m_name + "Health", 100);
	m_collider = { m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, m_sprite->GetClip().w, m_sprite->GetClip().h };
	m_sensingAreaCollider = { m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE), m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE) , (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE), (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE) };
}


Ranger::~Ranger()
{
}

void Ranger::CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent)
{

	m_behaviourTree = std::make_unique<BehaviourTree>(m_blackBoard);

	auto attackEnemy = std::make_shared<BT_Sequencer>();
	auto enemySpotted = std::make_shared<BT_IsEnemyNear>(m_blackBoard, m_visionRange);
	//auto inRangeToAttack = std::make_shared<BT_AmIInRange>(m_blackBoard, m_visionRange);
	auto setTargetToAttack = std::make_shared<BT_SetTargetAgent>(m_blackBoard, m_name + "SpottedEnemy");
	auto attack = std::make_shared<BT_Attack>(m_blackBoard);
	attackEnemy->AddNodesAsChildren({ enemySpotted, setTargetToAttack, attack });

	auto followTheLeader = std::make_shared<BT_Sequencer>();
	auto setTargetToTank = std::make_shared<BT_SetTargetAgent>(m_blackBoard, "Tank");
	auto findPath = std::make_shared<BT_FindPath>(m_blackBoard);
	auto moveTowards = std::make_shared<BT_Move>(m_blackBoard);
	followTheLeader->AddNodesAsChildren({ setTargetToTank,findPath,moveTowards });
	//the dps should have the following behaviors
	//ranged attack
	//melee attack
	//move to cover(behind tank)
	//follow leader

	auto root = std::make_shared<BT_Selector>();
	root->AddNodesAsChildren({ attackEnemy, followTheLeader });

	m_behaviourTree->Init(root, p_sharedPtrToThisAgent);

}

void Ranger::Update(float p_delta)
{
	m_behaviourTreeTickTime -= p_delta;
	if (m_behaviourTreeTickTime <= 0) {

		Sense();
		m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
		m_blackBoard->SetVector2i(m_name + "TargetPosition", m_blackBoard->GetVector2i("TankPosition"));
		std::vector<BT_Node*> foo; //TODO: fix this, creating an empty vector because too lazy to refactor the behavior tree class
		m_behaviourTree->Update();
		m_sensingAreaCollider.x = m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_sensingAreaCollider.y = m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_collider.x = m_curTile->GetWorldPos().x;
		m_collider.y = m_curTile->GetWorldPos().y;

		m_behaviourTreeTickTime = 1.0f;


		m_blackBoard->SetBool(m_name + "UnderAttack", false);
	}
	if (m_iFrame>0)
	{
		m_iFrame -= p_delta;
	}
	m_attackVisualizationTimer -= p_delta;
}

void Ranger::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, 1);

	if(m_attackVisualizationTimer>0)
	{
		m_drawManager->DrawLine(GetWorldPos().x + Config::HALF_TILE, GetWorldPos().y + Config::HALF_TILE, m_attackVisualizationTarget.x + Config::HALF_TILE, m_attackVisualizationTarget.y + Config::HALF_TILE, 0, 255, 255, 255);
	
	}

	m_drawManager->DrawLine(GetWorldPos().x, GetWorldPos().y, GetWorldPos().x + m_blackBoard->GetInt(m_name + "Health") / 3, GetWorldPos().y, 0, 255, 0, 255);
}

void Ranger::Sense()
{
}

void Ranger::OnCollision(std::weak_ptr<Agent> p_other)
{
	auto sptr = p_other.lock();
	if (sptr->GetName() == "Bat" && m_iFrame <= 0)
	{
		m_blackBoard->SetInt(m_name + "Health", m_blackBoard->GetInt(m_name + "Health") - 5);
		m_blackBoard->SetBool(m_name + "UnderAttack", true);
		m_blackBoard->SetAgent("EnemyAttacking" + m_name, sptr);
		m_blackBoard->SetVector2i("EnemyAttacking" + m_name + "Position", sptr->GetGridPos());
		std::cout << "Collided with bat\n";
		m_iFrame = 1.0f;
	}
}

void Ranger::NotColliding(std::weak_ptr<Agent> p_other)
{
}

void Ranger::OnAgentEnteredSenseArea(std::weak_ptr<Agent> p_other)
{
}

void Ranger::Attack(std::weak_ptr<Agent> p_target)
{
	
	auto sptr = p_target.lock();
	m_attackVisualizationTarget = sptr->GetWorldPos();
	m_attackVisualizationTimer = 1.f;
	if (sptr)
		sptr->ChangeHealth(-33.3f);
}
