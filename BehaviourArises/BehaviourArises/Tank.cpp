#include "stdafx.h"
#include "Tank.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "ServiceLocator.h"
#include "Tile.h"
#include "BehaviourTree.h"
#include "AStarPath.h"
#include "BlackBoard.h"
#include <iostream>6
#include "BT_SetDestination.h"
#include "BT_FindPath.h"
#include "BT_Move.h"
#include "BT_Composites.h"
#include "BT_Attack.h"
#include "BT_Defend.h"
#include "BT_INeedHealing.h"

Tank::Tank(IGridMap* p_world, Tile* p_tile, std::shared_ptr<BlackBoard> p_BB)
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
	m_name = "Tank";
	m_collider = m_sprite->GetClip();
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
	m_blackBoard->SetInt(m_name + "Health", 100);
	m_blackBoard->SetVector2i("EscapeLocation", Vector2<int>(20, 20));
	m_blackBoard->SetVector2i(m_name + "TargetLocation", m_blackBoard->GetVector2i("EscapeLocation"));
	m_behaviourTree = std::make_shared<BehaviourTree>(m_blackBoard);

	auto lookForEscape = std::make_shared<BT_Sequencer>();

	auto findPath = std::make_shared<BT_FindPath>(m_blackBoard);
	auto moveToTarget = std::make_shared<BT_Move>(m_blackBoard);

	lookForEscape->AddNodesAsChildren({ findPath,moveToTarget });
	auto defensiveStance = std::make_shared<BT_Sequencer>();
	auto defend = std::make_shared<BT_Defend>(m_blackBoard);
	auto needHealing = std::make_shared<BT_INeedHealing>(m_blackBoard);

	defensiveStance->AddNodesAsChildren({ needHealing,defend });

	auto root = std::make_shared<BT_Selector>();
	root->AddNodesAsChildren({ defensiveStance, lookForEscape });

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
		m_behaviourTreeTickTime = 1.0f;
		m_sensingAreaCollider.x = m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_sensingAreaCollider.y = m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_collider.x = m_curTile->GetWorldPos().x;
		m_collider.y = m_curTile->GetWorldPos().y;
		
	}
	
}

void Tank::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, 1);
	//m_pathFinding->Draw();
	m_drawManager->DrawRect(m_sensingAreaCollider, 255, 0, 0, 0);
	m_drawManager->DrawRect(m_collider, 0, 0, 255, 0);
}

void Tank::Sense()
{
}
