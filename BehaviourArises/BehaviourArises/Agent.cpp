#include "stdafx.h"
#include "Agent.h"
#include "PathFindingAlgorithm.h"
#include <algorithm>
#include "Tile.h"
Agent::Agent()
{
}


Agent::~Agent()
{
}

float Agent::GetHealth()
{
	return m_currentHealth;
}

void Agent::AdjustHealth(float p_amount)
{
	m_currentHealth += p_amount;
	if(m_currentHealth >= m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}
}

bool Agent::FindPath(Tile* p_targetTile)
{
	m_path = m_pathFinding->FindPath(m_curTile, p_targetTile);
	if (!m_path.empty())
	{
		return true;
	}
	
	return false;
}

bool Agent::FindPath(Vector2<int> p_targetCoord)
{
	m_path = m_pathFinding->FindPath(m_curTile, m_world->GetTile(p_targetCoord));
	if(!m_path.empty())
	{
		return true;
	
	}
	return false;
}

void Agent::ClearPath()
{
	m_pathFinding->Recalculate();
}

std::vector<Tile*> Agent::GetPath()
{
	return m_path;
}

void Agent::MoveToNextTile()
{
	if (m_path.empty() == false) {
		if (m_curTile != m_path.back())
		{
			Vector2<int> direction; //normalize the x and y component individually, instead of normalizing the entire vector, to ensure proper movement
			direction.x = (m_path.back()->GetGridPos().x - m_curTile->GetGridPos().x) / std::max(std::abs(m_path.back()->GetGridPos().x - m_curTile->GetGridPos().x), 1);
			direction.y = (m_path.back()->GetGridPos().y - m_curTile->GetGridPos().y) / std::max(std::abs(m_path.back()->GetGridPos().y - m_curTile->GetGridPos().y), 1);
			m_curTile = m_world->GetTile(m_curTile->GetGridPos() + direction);
		}
		else {
			m_path.pop_back();
		}
	}
}

