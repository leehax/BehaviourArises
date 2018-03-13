#pragma once
#include "Agent.h"
#include "BT_Composites.h"
#include "BT_Decorators.h"
#include "BT_Leaf.h"
#include "BT_Node.h"

class BT_MoveTo:
		public BT_Leaf
{
public:
	BT_State Update() override;

	BT_MoveTo(std::shared_ptr<BlackBoard> p_BB) :BT_Leaf(p_BB)
	{
		
	}

};
class BT_SetDestination:
	public BT_Leaf
{
public:
	BT_State Update() override;
	Vector2<int> m_target;
	BT_SetDestination(std::shared_ptr<BlackBoard> p_BB, Vector2<int> p_target) : BT_Leaf(p_BB)
	{
		m_target = p_target;
	}
};
class BT_FindPath:
	public BT_Leaf
{
public:
	BT_State Update() override;

	BT_FindPath(std::shared_ptr<BlackBoard> p_BB): BT_Leaf(p_BB)
	{
	}

};

class IGridMap;

class Healer :
	public Agent
{
public:
	Healer(IGridMap* p_world, Tile* p_tile);
	~Healer();

	
	void CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent) override;
	void Update(float p_delta) override;
	void Draw() override;
	void Sense() override;
	void MoveTo(Tile* p_tile);
	
};

