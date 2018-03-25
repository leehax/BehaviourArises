#include "stdafx.h"
#include "BT_IsEnemyNear.h"
#include "Dungeon.h"

BT_IsEnemyNear::BT_IsEnemyNear(std::shared_ptr<BlackBoard> p_BB, int p_range):BT_Leaf(p_BB)
{
	m_range = p_range;
}


BT_IsEnemyNear::~BT_IsEnemyNear()
{
}

BT_Node::BT_State BT_IsEnemyNear::Update()
{
	
	Dungeon* dung = static_cast<Dungeon*>(m_agent->GetWorld());
	std::shared_ptr<EnemyMob> enemy = dung->ClosestEnemy(m_agent->GetGridPos()).lock();

	if (enemy) {
		if (Manhattan(m_agent->GetGridPos(), enemy->GetGridPos()) <= m_range)
		{
			m_blackBoard->SetAgent(m_agent->GetName() + "SpottedEnemy", enemy);
			m_blackBoard->SetVector2i(m_agent->GetName() + "SpottedEnemyPosition", enemy->GetGridPos());
			return BT_State::Success;
		}
	}
	return BT_State::Failure;
}
