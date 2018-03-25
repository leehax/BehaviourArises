#pragma once
#include "Agent.h"
class Mage :
	public Agent
{
public:
	Mage(IGridMap* p_world, Tile* p_tile, std::shared_ptr<BlackBoard> p_BB);
	~Mage();
	void CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent) override;
	void Update(float p_delta) override;
	void Draw() override;
	void OnCollision(std::weak_ptr<Agent> p_other) override;
	void Attack(std::weak_ptr<Agent> p_target) override;
private:
	Vector2<int> m_attackVisualizationTarget = Vector2<int>();
	bool m_attackVisualizationActive = false;
};

