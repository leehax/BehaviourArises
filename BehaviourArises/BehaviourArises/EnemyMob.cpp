#include "stdafx.h"
#include "EnemyMob.h"
#include "AStarPath.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Tile.h"
#include "BlackBoard.h"
#include <algorithm>
#include "Dungeon.h"

EnemyMob::EnemyMob(IGridMap* p_world, Tile* p_tile)
{
	m_visionRange = 5;
	m_maxHealth = 100.f;
	m_currentHealth = 100.f;

	m_curTile = p_tile;

	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../External/textures/Bat.png", 0, 0, 32, 32);

	m_world = p_world;
	m_pathFinding = std::make_shared<AStarPath>(m_world);
	m_name = "Bat";
	m_collider = { m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, m_sprite->GetClip().w , m_sprite->GetClip().h };
	m_sensingAreaCollider = { m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE), m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE) , (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE), (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE) };
	m_targetTile = m_curTile;
}


EnemyMob::~EnemyMob()
{
	m_curTile->SetBlocked(false);
}

void EnemyMob::Update(float p_delta)
{
	m_behaviourTreeTickTime -= p_delta;
	if (m_behaviourTreeTickTime <= 0) {
		Sense();
		ClearPath();
		if(!m_hasTargetAgent&&m_targetTile==m_curTile)
		{
		
			m_targetTile = m_world->GetRandomTile();
		}
		
		FindPath(m_targetTile);
		MoveToNextTile();
		m_sensingAreaCollider.x = m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_sensingAreaCollider.y = m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE);
		m_collider.x = m_curTile->GetWorldPos().x;
		m_collider.y = m_curTile->GetWorldPos().y;
		m_behaviourTreeTickTime = 1.f;
	
	}
	
}

void EnemyMob::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, 1);
	m_drawManager->DrawLine(GetWorldPos().x, GetWorldPos().y + Config::TILE_SIZE-1, GetWorldPos().x + m_currentHealth / 3, GetWorldPos().y + Config::TILE_SIZE-1, 255,0, 0, 255);
}

void EnemyMob::Sense()
{
	std::vector<Vector2<int>> sensedAgentPositions;
	if (!m_sensedAgents.empty()) {
		for (auto a : m_sensedAgents)
		{
			auto sptr = a.lock();
			if(sptr){
				if (sptr->GetName() != "Bat")
				{
					sensedAgentPositions.push_back(sptr->GetCurrentTile()->GetGridPos());

				}
			}
		}
	}
	int maxDistance = INT_MAX;
	int index = -1;
	for (int i = 0; i < sensedAgentPositions.size(); i++) //get closest agent
	{
		if (Manhattan(m_curTile->GetGridPos(), sensedAgentPositions[i])<=maxDistance)
		{
			maxDistance = Manhattan(m_curTile->GetGridPos(), sensedAgentPositions[i]);
			index = i;
		}
	}
	if (index >= 0) {

		m_targetTile = m_world->GetTile(sensedAgentPositions[index]);
		m_hasTargetAgent = true; 
	}
	sensedAgentPositions.clear();
}

