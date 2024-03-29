#include "stdafx.h"
#include "Tank.h"
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
#include "BT_Composites.h"
#include "BT_Attack.h"
#include "BT_AllyUnderAttack.h"
#include "BT_AmIInRange.h"
#include "BT_Decorators.h"
#include "BT_SetTargetAgent.h"
#include "BT_IsEnemyNear.h"
#include "BT_AllyNeedsHealing.h"

Tank::Tank(IGridMap* p_world, Tile* p_tile, std::shared_ptr<BlackBoard> p_BB)
{


	m_visionRange = 3;
	m_maxHealth = 100.f;
	m_currentHealth = 100.f;

	m_curTile = p_tile;

	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../External/textures/Tank.png", 0, 0, 32, 32); //praise the sun \[T]/

	m_world = p_world;
	m_pathFinding = std::make_shared<AStarPath>(m_world);
	m_blackBoard = p_BB;
	m_name = "Tank";
	m_collider = { m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, m_sprite->GetClip().w, m_sprite->GetClip().h };
	m_sensingAreaCollider = { m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE), m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE) , (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE), (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE) };
	m_randomTarget = std::make_shared<Vector2<int>>(m_world->GetRandomPosition());

}
Tank::~Tank()
{
}

void Tank::CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent)
{
	m_blackBoard->SetVector2i( m_name + "Position", m_curTile->GetGridPos());
	m_blackBoard->SetVector2i("RandomPosition", m_world->GetRandomPosition());
	m_blackBoard->SetInt(m_name + "Health", 100);

	m_behaviourTree = std::make_unique<BehaviourTree>(m_blackBoard);

	auto roamRandomly = std::make_shared<BT_Sequencer>();
	auto setRandomDestination = std::make_shared<BT_SetDestination>(m_blackBoard, m_randomTarget);
	auto findPath = std::make_shared<BT_FindPath>(m_blackBoard);
	auto moveTowards = std::make_shared<BT_Move>(m_blackBoard);

	roamRandomly->AddNodesAsChildren({ setRandomDestination,findPath,moveTowards });



	auto helpHealer = std::make_shared<BT_Sequencer>();
	auto moveToHealer = std::make_shared<BT_Sequencer>();
	auto isHealerUnderAttack = std::make_shared<BT_AllyUnderAttack>(m_blackBoard, "Healer");
	auto setTargetToHealer = std::make_shared<BT_SetTargetAgent>(m_blackBoard, "Healer");

	moveToHealer->AddNodesAsChildren({ setTargetToHealer, findPath, moveTowards });

	auto lookForHealing = std::make_shared<BT_Sequencer>();
	auto needHealing = std::make_shared<BT_AllyNeedsHealing>(m_blackBoard, m_name);

	lookForHealing->AddNodesAsChildren({ needHealing,moveToHealer });

	auto attackEnemy = std::make_shared<BT_Sequencer>();
	auto enemySpotted = std::make_shared<BT_IsEnemyNear>(m_blackBoard, m_visionRange);
	auto setTargetToAttack = std::make_shared<BT_SetTargetAgent>(m_blackBoard, m_name + "SpottedEnemy");
	auto attack = std::make_shared<BT_Attack>(m_blackBoard);

	auto attackMoveSelector = std::make_shared<BT_Selector>();
	auto moveToAttack = std::make_shared<BT_Sequencer>();
	auto inRangeToAttack = std::make_shared < BT_AmIInRange> (m_blackBoard, 0, m_name + "SpottedEnemyPosition");
	auto attackInverter = std::make_shared<BT_Inverter>();

	attackInverter->SetChild(inRangeToAttack);
	moveToAttack->AddNodesAsChildren({ attackInverter,findPath,moveTowards });
	attackMoveSelector->AddNodesAsChildren({ moveToAttack,attack });

	attackEnemy->AddNodesAsChildren({ enemySpotted, setTargetToAttack, attackMoveSelector });

	helpHealer->AddNodesAsChildren({ isHealerUnderAttack,moveToHealer,attackEnemy });
	
	auto helpMage = std::make_shared<BT_Sequencer>();
	auto moveToMage = std::make_shared<BT_Sequencer>();
	auto isMageUnderAttack = std::make_shared<BT_AllyUnderAttack>(m_blackBoard, "Mage");
	auto setTargetToMage = std::make_shared<BT_SetTargetAgent>(m_blackBoard, "Mage");

	moveToMage->AddNodesAsChildren({ setTargetToMage,findPath,moveTowards });

	helpMage->AddNodesAsChildren({ isMageUnderAttack,moveToMage,attackEnemy });

	auto selfDefense = std::make_shared<BT_Sequencer>();
	auto enemyInMeleeRange = std::make_shared<BT_IsEnemyNear>(m_blackBoard, 1);


	selfDefense->AddNodesAsChildren({ enemyInMeleeRange,setTargetToAttack,attackMoveSelector });


	auto root = std::make_shared<BT_Selector>();
	root->AddNodesAsChildren({selfDefense, helpHealer , helpMage ,lookForHealing, roamRandomly });

	m_behaviourTree->Init(root, p_sharedPtrToThisAgent);




}

void Tank::Update(float p_delta)
{
	m_behaviourTreeTickTime -= p_delta;
	if (m_behaviourTreeTickTime <= 0) {

		m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
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
	if(GetGridPos() == *m_randomTarget)
	{
		*m_randomTarget = m_world->GetRandomPosition();
	}
}

void Tank::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, 1);

	//draw a healthB... healthLine
	m_drawManager->DrawLine(GetWorldPos().x, GetWorldPos().y, GetWorldPos().x + m_blackBoard->GetInt(m_name + "Health")/3, GetWorldPos().y, 0, 255, 0, 255);
}



void Tank::OnCollision(std::weak_ptr<Agent> p_other)
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

void Tank::Attack(std::weak_ptr<Agent> p_target)
{
	
	auto sptr=p_target.lock();
	if(sptr)
		sptr->ChangeHealth(-50.f);
}
