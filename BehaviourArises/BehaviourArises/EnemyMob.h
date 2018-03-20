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
};

