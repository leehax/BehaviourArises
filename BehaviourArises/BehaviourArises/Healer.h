#pragma once
#include "Agent.h"
#include "BT_Composites.h"
#include "BT_Decorators.h"
#include "BT_Leaf.h"
#include "BT_Node.h";

class BT_MoveTo:
		public BT_Leaf
{
	BT_State Update() override;

	BT_MoveTo(std::shared_ptr<BlackBoard> p_BB);
	
	
	
};
class IGridMap;

class Healer :
	public Agent
{
public:
	Healer(IGridMap* p_world, Tile* p_tile);
	~Healer();

	
	void CreateBehaviourTree() override;
	void Update(float p_delta) override;
	void Draw() override;
	void Sense() override;

	
};

