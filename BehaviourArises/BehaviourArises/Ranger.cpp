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
#include "BT_SetDestination.h"
#include "BT_FindPath.h"
#include "BT_Move.h"
#include "BT_AmIInRange.h"
#include "BT_Attack.h"

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
	m_collider = { m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, m_sprite->GetClip().w, m_sprite->GetClip().h };
	m_sensingAreaCollider = { m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE), m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE) , (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE), (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE) };
}


Ranger::~Ranger()
{
}

void Ranger::CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent)
{
	m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
	m_behaviourTree = std::make_unique<BehaviourTree>(m_blackBoard);

	auto attackEnemy = std::make_shared<BT_Sequencer>();
	//auto enemySpotted = std::make_shared<BT_>()
	auto inRangeToAttack = std::make_shared<BT_AmIInRange>(m_blackBoard, m_visionRange);
	auto attack = std::make_shared<BT_Attack>(m_blackBoard);
	//the dps should have the following behaviors
	//ranged attack
	//melee attack
	//move to cover(behind tank)
	//follow leader



}

void Ranger::Update(float p_delta)
{
	m_behaviourTreeTickTime -= p_delta;
	if (m_behaviourTreeTickTime <= 0) {

		Sense();
		m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
		m_blackBoard->SetVector2i(m_name + "TargetPosition", m_blackBoard->GetVector2i("TankPosition"));
		std::vector<BT_Node*> foo; //TODO: fix this, creating an empty vector because too lazy to refactor the behavior tree class
		m_behaviourTree->Update(foo);
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
}

void Ranger::Draw()
{
}

void Ranger::Sense()
{
}

void Ranger::OnCollision(std::weak_ptr<Agent> p_other)
{
	auto sptr = p_other.lock();
	if (sptr->GetName() == "Bat" && m_iFrame <= 0)
	{
		m_blackBoard->SetBool(m_name + "UnderAttack", true);
		m_blackBoard->SetAgent("EnemyAttacking" + m_name, sptr);
		m_blackBoard->SetVector2i("EnemyAttacking" + m_name + "Position", sptr->GetGridPos());
		std::cout << "Collided with bat\n";
		m_iFrame = 1.0f;
	}
}

void Ranger::OnAgentEnteredSenseArea(std::weak_ptr<Agent> p_other)
{
}
