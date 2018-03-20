#pragma once
#include "IEntity.h"
#include <memory>
class BehaviourTree;
class BT_Node;

class BT_Selector; //inherit from node
class BT_Decorator;
class BT_Sequencer;
class BT_Leaf;

class BlackBoard;

class PathFindingAlgorithm;
class IGridMap;

class Agent :
	public IEntity
{
public:
	Agent();
	~Agent();

	virtual void Sense() = 0;
	virtual float GetHealth();
	virtual void AdjustHealth(float p_amount);
	virtual void CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent){}
	virtual bool FindPath(Tile* p_targetTile);
	virtual bool FindPath(Vector2<int> p_targetCoord);
	virtual void ClearPath();
	virtual std::vector<Tile*> GetPath();
	virtual bool MoveToNextTile();
	virtual std::string GetName();
	virtual void OnCollision(std::shared_ptr<Agent> p_other) {}
	virtual void OnAgentEnteredSenseArea(std::shared_ptr<Agent> p_other);
	virtual SDL_Rect GetCollider(){	return m_collider;	}
	virtual SDL_Rect GetSensingAreaCollider(){	return m_sensingAreaCollider;	}
protected:
	std::shared_ptr<BlackBoard> m_blackBoard;
	std::shared_ptr<BehaviourTree> m_behaviourTree;
	std::shared_ptr<PathFindingAlgorithm> m_pathFinding;
	int m_visionRange;
	float m_currentHealth;
	float m_maxHealth;
	float m_behaviourTreeTickTime = 1.0f;
	std::vector<Tile*> m_path;
	std::string m_name;
	SDL_Rect m_collider;
	SDL_Rect m_sensingAreaCollider;
	std::vector<std::shared_ptr<Agent>> m_sensedAgents;
	std::vector<std::shared_ptr<Agent>> m_sensedEnemies;
};

