#pragma once
#include "Agent.h"

class EnemyMob :
	public Agent
{
public:
	EnemyMob(IGridMap* p_world, Tile* p_tile);
	~EnemyMob();


	void Update(float p_delta) override;
	void Draw() override;
	void Sense() override;
	void OnCollision(std::weak_ptr<Agent> p_other) override {}
private:
	Tile * m_targetTile;
	bool m_hasTargetAgent = false;
};

