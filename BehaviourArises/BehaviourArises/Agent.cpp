#include "stdafx.h"
#include "Agent.h"
#include "PathFindingAlgorithm.h"
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

std::vector<Tile*> Agent::GetPath()
{
	return m_path;
}

