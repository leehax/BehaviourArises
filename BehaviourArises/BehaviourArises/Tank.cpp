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
#include "BT_Defend.h"
#include "BT_INeedHealing.h"
#include "BT_AllyUnderAttack.h"
#include "BT_AmIInRange.h"
#include "BT_Decorators.h"
#include "BT_SetTargetAgent.h"

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
}


Tank::~Tank()
{
}

void Tank::CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent)
{
	//the tank should have the following behaviors, he is the leader of the party
	//block
	//taunt
	//fight
	//look for escape

	m_blackBoard->SetVector2i( m_name + "Position", m_curTile->GetGridPos());
	m_blackBoard->SetVector2i("EscapePosition", Vector2<int>(20,20));
	m_blackBoard->SetInt(m_name + "Health", 100);

	m_behaviourTree = std::make_unique<BehaviourTree>(m_blackBoard);

	auto lookForEscape = std::make_shared<BT_Sequencer>();
	auto setEscapeAsTarget = std::make_shared<BT_SetDestination>(m_blackBoard, m_blackBoard->GetVector2i("EscapePosition"));
	auto findPath = std::make_shared<BT_FindPath>(m_blackBoard);
	auto moveTowards = std::make_shared<BT_Move>(m_blackBoard);

	lookForEscape->AddNodesAsChildren({ setEscapeAsTarget,findPath,moveTowards });

	auto waitForHealing = std::make_shared<BT_Sequencer>();
	auto defend = std::make_shared<BT_Defend>(m_blackBoard);
	auto needHealing = std::make_shared<BT_INeedHealing>(m_blackBoard);

	waitForHealing->AddNodesAsChildren({ needHealing,defend });

	auto helpHealer = std::make_shared<BT_Sequencer>();
	auto inRangeToAttack = std::make_shared < BT_AmIInRange> (m_blackBoard, 1);
	auto attackInverter = std::make_shared<BT_Inverter>();
	auto attackMoveSelector = std::make_shared<BT_Selector>();
	auto moveToAttack = std::make_shared<BT_Sequencer>();
	auto isHealerUnderAttack = std::make_shared<BT_AllyUnderAttack>(m_blackBoard,"Healer");
	auto setTargetAgentToEnemyAttackingHealer = std::make_shared<BT_SetTargetAgent>(m_blackBoard, "EnemyAttackingHealer");
	auto attack = std::make_shared<BT_Attack>(m_blackBoard);

	auto selfDefense = std::make_shared<BT_Sequencer>();
	auto amIUnderAttack = std::make_shared<BT_AllyUnderAttack>(m_blackBoard, "Tank");
	auto setTargetAgentToEnemyAttackingMe = std::make_shared<BT_SetTargetAgent>(m_blackBoard, "EnemyAttackingTank");


	attackInverter->SetChild(inRangeToAttack);
	moveToAttack->AddNodesAsChildren({ attackInverter,findPath,moveTowards });
	attackMoveSelector->AddNodesAsChildren({ moveToAttack,attack });
	helpHealer->AddNodesAsChildren({ isHealerUnderAttack,setTargetAgentToEnemyAttackingHealer,attackMoveSelector });

	selfDefense->AddNodesAsChildren({ amIUnderAttack,setTargetAgentToEnemyAttackingMe,attackMoveSelector });
	//Help ally if they are attacked sequence
	//Is ally under attack?
	//Is it one or many enemies?

	//One enemy
	//Move to that enemy
	//Kill it

	//Many enemies, taunt enemies (aura of 3x3) (taunt optional if time)
	//Armor up





	auto root = std::make_shared<BT_Selector>();
	root->AddNodesAsChildren({selfDefense, helpHealer,waitForHealing, lookForEscape });

	m_behaviourTree->Init(root, p_sharedPtrToThisAgent);




}

void Tank::Update(float p_delta)
{
	m_behaviourTreeTickTime -= p_delta;
	if (m_behaviourTreeTickTime <= 0) {

		m_blackBoard->SetInt(m_name+"Health", m_blackBoard->GetInt(m_name + "Health") - 5);
		m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
		std::vector<BT_Node*> boo; //TODO: fix this, creating an empty vector because too lazy to refactor the behavior tree class
		m_behaviourTree->Update(boo);
	
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

void Tank::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, 1);
	//m_pathFinding->Draw();
	//m_drawManager->DrawRect(m_sensingAreaCollider, 255, 0, 0, 0);
	//m_drawManager->DrawRect(m_collider, 0, 0, 255, 0);
}

void Tank::Sense()
{
}

void Tank::OnCollision(std::weak_ptr<Agent> p_other)
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

void Tank::NotColliding(std::weak_ptr<Agent> p_other)
{
}

void Tank::Attack(std::weak_ptr<Agent> p_target)
{
	
	auto sptr=p_target.lock();
	if(sptr)
		sptr->SetHealth(0);
}
