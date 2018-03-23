#pragma once
#include "Agent.h"
class Ranger :
	public Agent
{
public:
	Ranger(IGridMap* p_world, Tile* p_tile, std::shared_ptr<BlackBoard> p_BB);
	~Ranger();
	void CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent) override;
	void Update(float p_delta) override;
	void Draw() override;
	void Sense() override;
	void OnCollision(std::weak_ptr<Agent> p_other) override;
	void OnAgentEnteredSenseArea(std::weak_ptr<Agent> p_other) override;
};

