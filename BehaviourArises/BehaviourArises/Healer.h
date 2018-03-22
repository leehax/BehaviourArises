#pragma once
#include "Agent.h"
#include "BT_Composites.h"
#include "BT_Decorators.h"
#include "BT_Leaf.h"
#include "BT_Node.h"


class IGridMap;

class Healer :
	public Agent
{
public:
	Healer(IGridMap* p_world, Tile* p_tile, std::shared_ptr<BlackBoard> p_BB);
	~Healer();

	
	void CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent) override;
	void Update(float p_delta) override;
	void Draw() override;
	void Sense() override;
	void OnCollision(std::shared_ptr<Agent> p_other) override;
	void NotColliding(std::shared_ptr<Agent> p_other) override;
	void Attack(std::weak_ptr<Agent> p_target) override;
};

