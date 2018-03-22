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
	void OnCollision(std::shared_ptr<Agent> p_other) override;
	void NotColliding(std::shared_ptr<Agent> p_other) override;
	void Attack(std::weak_ptr<Agent> p_target) override;
private:
	Tile * m_targetTile;
};

