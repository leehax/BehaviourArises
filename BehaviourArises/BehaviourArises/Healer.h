#pragma once
#include "Agent.h"



class Healer :
	public Agent
{
public:
	Healer(IGridMap* p_world, Tile* p_tile, std::shared_ptr<BlackBoard> p_BB);
	~Healer();

	
	void CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent) override;
	void Update(float p_delta) override;
	void Draw() override;
	void OnCollision(std::weak_ptr<Agent> p_other) override;

};

