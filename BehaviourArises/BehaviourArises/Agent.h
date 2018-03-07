#pragma once
#include "IEntity.h"
class BehaviourTree;
class BT_Node;

class BT_Selector; //inherit from node
class BT_Decorator;
class BT_Sequencer;
class BT_Leaf;

class BlackBoard;

class PathFindingAlgorithm;


class Agent :
	public IEntity
{
public:
	Agent();
	~Agent();

	virtual void Sense() = 0;
	virtual float GetHealth();
	virtual void AdjustHealth(float p_amount);


private:
	BlackBoard * m_blackBoard;
	BehaviourTree* m_behaviourTree;
	PathFindingAlgorithm* m_pathFinding;

	int m_visionRange;
	float m_currentHealth;
	float m_maxHealth;

};

