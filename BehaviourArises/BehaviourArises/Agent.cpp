#include "stdafx.h"
#include "Agent.h"

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
