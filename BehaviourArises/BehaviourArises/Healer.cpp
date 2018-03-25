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
#include "BT_Node.h"
#include "BT_SetDestination.h"
#include "BT_FindPath.h"
#include "BT_Move.h"
#include "BT_AllyNeedsHealing.h"
#include "BT_Attack.h"
#include "BT_Heal.h"
#include "BT_AmIInRange.h"
#include "BT_AllyUnderAttack.h"
#include "BT_MoveToSafety.h"
#include "BT_SetTargetAgent.h"
#include "BT_IsEnemyNear.h"



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
	m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
	m_blackBoard->SetInt(m_name + "Health", 100);
	m_collider = { m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, m_sprite->GetClip().w, m_sprite->GetClip().h };
	m_sensingAreaCollider = { m_curTile->GetWorldPos().x - m_visionRange*static_cast<int>(Config::TILE_SIZE), m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE) , (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE), (m_visionRange * 2+1) * static_cast<int>(Config::TILE_SIZE) };
}


Healer::~Healer()
{
}

void Healer::CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent)
{

	m_behaviourTree = std::make_unique<BehaviourTree>(m_blackBoard);
	
	
	auto flee = std::make_shared<BT_Sequencer>();

	auto isEnemyNear = std::make_shared<BT_IsEnemyNear>(m_blackBoard, 2);
	auto findFleeDirection = std::make_shared<BT_MoveToSafety>(m_blackBoard, m_name+"SpottedEnemyPosition");
	auto moveTowards = std::make_shared<BT_Move>(m_blackBoard);
	

	flee->AddNodesAsChildren({ isEnemyNear,findFleeDirection,moveTowards });

	auto followTheLeader = std::make_shared<BT_Sequencer>();

	auto setTargetToTank = std::make_shared<BT_SetTargetAgent>(m_blackBoard, "Tank");
	auto findPath = std::make_shared<BT_FindPath>(m_blackBoard);

	followTheLeader->AddNodesAsChildren({ setTargetToTank, findPath, moveTowards });


	auto healTank = std::make_shared<BT_Sequencer>();
	auto isTankWounded = std::make_shared<BT_AllyNeedsHealing>(m_blackBoard,"Tank");
	auto healTankIfInRange = std::make_shared<BT_Selector>();
	auto moveToHealTank = std::make_shared<BT_Sequencer>();
	auto rangeToTankInverter = std::make_shared<BT_Inverter>();
	auto inRangeTohealTank = std::make_shared<BT_AmIInRange>(m_blackBoard, 2, "TankPosition");
	auto healT = std::make_shared<BT_Heal>(m_blackBoard, "Tank");

	

	rangeToTankInverter->SetChild(inRangeTohealTank);
	moveToHealTank->AddNodesAsChildren({ rangeToTankInverter,setTargetToTank, findPath,moveTowards });
	healTankIfInRange->AddNodesAsChildren({ moveToHealTank, healT });

	healTank->AddNodesAsChildren({ isTankWounded, healTankIfInRange });

	auto healSelf = std::make_shared<BT_Sequencer>();
	auto amIWounded = std::make_shared<BT_AllyNeedsHealing>(m_blackBoard, "Healer");
	auto amISafe = std::make_shared<BT_Inverter>();
	auto healS = std::make_shared<BT_Heal>(m_blackBoard, "Healer");

	amISafe->SetChild(isEnemyNear);
	healSelf->AddNodesAsChildren({ amIWounded,amISafe,healS });

	auto healMage = std::make_shared<BT_Sequencer>();
	auto isMageWounded = std::make_shared<BT_AllyNeedsHealing>(m_blackBoard, "Mage");
	auto healMageIfInRange = std::make_shared<BT_Selector>();
	auto moveToHealMage = std::make_shared<BT_Sequencer>();
	auto rangeToMageInverter = std::make_shared<BT_Inverter>();
	auto setTargetToMage = std::make_shared<BT_SetTargetAgent>(m_blackBoard, "Mage");
	auto inRangeToHealMage = std::make_shared<BT_AmIInRange>(m_blackBoard, 2, "MagePosition");
	auto healM = std::make_shared<BT_Heal>(m_blackBoard, "Mage");
	auto root = std::make_shared<BT_Selector>();

	rangeToMageInverter->SetChild(inRangeToHealMage);
	moveToHealMage->AddNodesAsChildren({ rangeToMageInverter,setTargetToMage,findPath,moveTowards });
	healMageIfInRange->AddNodesAsChildren({ moveToHealMage,healM });

	healMage->AddNodesAsChildren({ isMageWounded, healMageIfInRange });

	root->AddNodesAsChildren({ healTank, healSelf, flee, healMage, followTheLeader });

	m_behaviourTree->Init(root, p_sharedPtrToThisAgent);


}


void Healer::Update(float p_delta)
{
	
	m_behaviourTreeTickTime -= p_delta;
	if (m_behaviourTreeTickTime <= 0) {
	
		Sense();
		m_blackBoard->SetVector2i(m_name + "Position", m_curTile->GetGridPos());
		//m_blackBoard->SetVector2i(m_name + "TargetPosition", m_blackBoard->GetVector2i("TankPosition"));
		m_behaviourTree->Update();
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

	m_drawManager->DrawLine(GetWorldPos().x, GetWorldPos().y, GetWorldPos().x + m_blackBoard->GetInt(m_name + "Health") / 3, GetWorldPos().y, 0, 255, 0, 255);
}


void Healer::OnCollision(std::weak_ptr<Agent> p_other)
{
	auto sptr = p_other.lock();
	if(sptr->GetName()=="Bat" && m_iFrame<=0)
	{
		m_blackBoard->SetInt(m_name + "Health", m_blackBoard->GetInt(m_name + "Health") - 5);
		m_blackBoard->SetBool(m_name + "UnderAttack", true);
		m_blackBoard->SetAgent("EnemyAttacking" + m_name, sptr);
		m_blackBoard->SetVector2i("EnemyAttacking" + m_name + "Position", sptr->GetGridPos());
		std::cout << "Collided with bat\n";
		m_iFrame = 1.0f;
	}
}




