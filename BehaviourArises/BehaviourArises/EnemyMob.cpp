#include "stdafx.h"
#include "EnemyMob.h"
#include "AStarPath.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Tile.h"
#include "BlackBoard.h"
#include <algorithm>

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
	m_collider = { m_curTile->GetWorldPos().x - static_cast<int>(Config::HALF_TILE)/2 , m_curTile->GetWorldPos().y- static_cast<int>(Config::HALF_TILE)/2, m_sprite->GetClip().w + static_cast<int>(Config::HALF_TILE), m_sprite->GetClip().h + static_cast<int>(Config::HALF_TILE) }; //set the collider slightly bigger than a tile to make it easier to trigger
	m_sensingAreaCollider = { m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE), m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE) , (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE), (m_visionRange * 2 + 1) * static_cast<int>(Config::TILE_SIZE) };
	m_targetTile = m_curTile;
}


EnemyMob::~EnemyMob()
{
}

void EnemyMob::Update(float p_delta)
{
	Sense();
	ClearPath();
	FindPath(m_targetTile);
	MoveToNextTile();
	m_sensingAreaCollider.x = m_curTile->GetWorldPos().x - m_visionRange * static_cast<int>(Config::TILE_SIZE);
	m_sensingAreaCollider.y = m_curTile->GetWorldPos().y - m_visionRange * static_cast<int>(Config::TILE_SIZE);
	m_collider.x = m_curTile->GetWorldPos().x - static_cast<int>(Config::HALF_TILE) / 2;
	m_collider.y = m_curTile->GetWorldPos().y - static_cast<int>(Config::HALF_TILE) / 2;
	m_curTile->SetBlocked(true);
}

void EnemyMob::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y, 1);
	m_drawManager->DrawRect(m_sensingAreaCollider, 255, 0, 0, 0);
	m_drawManager->DrawRect(m_collider, 255, 0, 0, 0);
	m_pathFinding->Draw();
	m_drawManager->DrawRect(*m_targetTile->GetRect(), 0, 255, 255,0);
}

void EnemyMob::Sense()
{
	std::vector<Vector2<int>> sensedAgentPositions;
	if (!m_sensedAgents.empty()) {
		for (auto a : m_sensedAgents)
		{
			if (a->GetName() != "Bat")
			{
				sensedAgentPositions.push_back(a->GetCurrentTile()->GetGridPos());
				

			}
		}
	}
	int maxDistance = INT_MAX;
	int index = -1;
	for (int i = 0; i < sensedAgentPositions.size(); i++)
	{
		if (Manhattan(m_curTile->GetGridPos(), sensedAgentPositions[i])<=maxDistance)
		{
			maxDistance = Manhattan(m_curTile->GetGridPos(), sensedAgentPositions[i]);
			index = i;
		}
	}
	if (index >= 0) {
		Vector2<int> direction; //normalize the x and y component individually, instead of normalizing the entire vector, to ensure proper movement
		direction.x = (sensedAgentPositions[index].x - m_curTile->GetGridPos().x) / std::max(std::abs(sensedAgentPositions[index].x - m_curTile->GetGridPos().x), 1);
		direction.y = (sensedAgentPositions[index].y - m_curTile->GetGridPos().y) / std::max(std::abs(sensedAgentPositions[index].y - m_curTile->GetGridPos().y), 1);

		m_targetTile = m_world->GetTile(sensedAgentPositions[index] - direction);
	}
	sensedAgentPositions.clear();
}

void EnemyMob::OnCollision(std::shared_ptr<Agent> p_other)
{
}

void EnemyMob::NotColliding(std::shared_ptr<Agent> p_other)
{
}

void EnemyMob::Attack(std::weak_ptr<Agent> p_target)
{
}
