#include "stdafx.h"
#include "Mage.h"
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
#include "BT_MoveToSafety.h"

Mage::Mage(IGridMap* p_world, Tile* p_tile, std::shared_ptr<BlackBoard> p_BB)
{
	m_visionRange = 3;
	m_maxHealth = 100.f;
	m_currentHealth = 100.f;

	m_curTile = p_tile;

	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../External/textures/mage.png", 0, 0, 32, 32);

	m_world = p_world;
	m_pathFinding = std::make_shared<AStarPath>(m_world);
	m_blackBoard = p_BB;
	m_name = "Mage";
	m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
	m_blackBoard->SetInt(m_name + "Health", 100);
	m_collider = { m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, m_sprite->GetClip().w, m_sprite->GetClip().h };
	m_sensingAreaCollider = { m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE), m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE) , (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE), (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE) };
}


Mage::~Mage()
{
}

void Mage::CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent)
{

	m_behaviourTree = std::make_unique<BehaviourTree>(m_blackBoard);

	auto attackEnemy = std::make_shared<BT_Sequencer>();
	auto enemySpotted = std::make_shared<BT_IsEnemyNear>(m_blackBoard, m_visionRange);
	auto setTargetToAttack = std::make_shared<BT_SetTargetAgent>(m_blackBoard, m_name + "SpottedEnemy");
	auto attack = std::make_shared<BT_Attack>(m_blackBoard);
	attackEnemy->AddNodesAsChildren({ enemySpotted, setTargetToAttack, attack });

	auto followTheLeader = std::make_shared<BT_Sequencer>();
	auto setTargetToHealer = std::make_shared<BT_SetTargetAgent>(m_blackBoard, "Healer");
	auto findPath = std::make_shared<BT_FindPath>(m_blackBoard);
	auto moveTowards = std::make_shared<BT_Move>(m_blackBoard);
	followTheLeader->AddNodesAsChildren({ setTargetToHealer,findPath,moveTowards });

	auto flee = std::make_shared<BT_Sequencer>();

	auto isEnemyNear = std::make_shared<BT_IsEnemyNear>(m_blackBoard, 2);
	auto findFleeDirection = std::make_shared<BT_MoveToSafety>(m_blackBoard, m_name + "SpottedEnemyPosition");

	flee->AddNodesAsChildren({ isEnemyNear,findFleeDirection,moveTowards });

	auto attackAndFlee = std::make_shared<BT_Parallel>(2, 1);
	attackAndFlee->AddNodesAsChildren({ flee, attackEnemy });


	auto root = std::make_shared<BT_Selector>();
	root->AddNodesAsChildren({ attackAndFlee, attackEnemy, followTheLeader });

	m_behaviourTree->Init(root, p_sharedPtrToThisAgent);

}

void Mage::Update(float p_delta)
{
	m_behaviourTreeTickTime -= p_delta;
	if (m_behaviourTreeTickTime <= 0) {

		Sense();
		m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
		m_blackBoard->SetVector2i(m_name + "TargetPosition", m_blackBoard->GetVector2i("TankPosition"));
		m_attackVisualizationActive = false;
		m_blackBoard->SetBool(m_name + "UnderAttack", false);
		m_behaviourTree->Update();
		
		m_sensingAreaCollider.x = m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_sensingAreaCollider.y = m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_collider.x = m_curTile->GetWorldPos().x;
		m_collider.y = m_curTile->GetWorldPos().y;

		m_behaviourTreeTickTime = 1.0f;


		
	}
	if (m_iFrame>0)
	{
		m_iFrame -= p_delta;
	}
}

void Mage::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, 1);

	if(m_attackVisualizationActive)
	{
		m_drawManager->DrawLine(GetWorldPos().x + 3, GetWorldPos().y + 5, m_attackVisualizationTarget.x + Config::HALF_TILE, m_attackVisualizationTarget.y + Config::HALF_TILE, 0, 255, 255, 255);
	
	}

	m_drawManager->DrawLine(GetWorldPos().x, GetWorldPos().y, GetWorldPos().x + m_blackBoard->GetInt(m_name + "Health") / 3, GetWorldPos().y, 0, 255, 0, 255);
}


void Mage::OnCollision(std::weak_ptr<Agent> p_other)
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

void Mage::Attack(std::weak_ptr<Agent> p_target)
{
	
	auto sptr = p_target.lock();
	m_attackVisualizationTarget = sptr->GetWorldPos();
	if (sptr) {
		m_blackBoard->SetBool(m_name + "UnderAttack", true);
		m_attackVisualizationActive = true;
		sptr->ChangeHealth(-33.3f);
		if(sptr->GetHealth()<=0)
		{
			m_attackVisualizationActive = false;
		}
	}
}
