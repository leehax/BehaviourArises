#pragma once
#include "IEntity.h"
#include <memory>
#include "IState.h"
#include "FiniteStateMachine.h"
#include "AStarPath.h"
#include "JPSPath.h"
class FallenStar;
class World;
class FiniteStateMachine;
class StarChaser;
class ChaserState :public IState
{
	
protected:
	StarChaser& m_starChaser;
public:
	ChaserState(StarChaser& p_chaser)
		: m_starChaser(p_chaser)
	{
	}
	virtual void UpdateTarget()=0;
};
class State_Collect :public ChaserState
{
public:

	State_Collect(StarChaser& p_chaser)
		: ChaserState(p_chaser)
	{
	}

	void Enter() override final;
	void Update(float p_delta) override final;
	void Exit() override final;
	void UpdateTarget() override final;
};
class State_Sell :public ChaserState
{
public:
	State_Sell(StarChaser& p_chaser)
		: ChaserState(p_chaser)
	{
	}

	void Enter() override final;
	void Update(float p_delta) override final;
	void Exit() override final;
	void UpdateTarget() override final;

private:
	float m_energy = 100.f;
};
class State_Rest :public ChaserState
{
public:
	State_Rest(StarChaser& p_chaser)
		: ChaserState(p_chaser)
	{
	}

	void Enter() override final;
	void Update(float p_delta) override final;
	void Exit() override final;
	void UpdateTarget() override final;

private:
	float m_timeToRest = 1.f;
};

class StarChaser :public IEntity, public FiniteStateMachine
{
public:
	StarChaser(World* p_world);
	~StarChaser();
	void Update(float p_delta) override;
	void Draw() override;
	void SetTargetTile(const std::string p_targetEntitityType);
	bool AtTargetTile();
	void Notify(const std::string p_msg);
	void RecalculatePath();
	void MoveToNextTile();
	void TogglePathFindingAlgorithm(const std::string p_name);

private:

	Tile* m_targetTile = nullptr;
	AStarPath* m_AStar;
	JPSPath* m_JPS;
	PathFindingAlgorithm* m_pathFinding;

	World* m_world;
	Sprite* m_spriteWithStar;
	Sprite* m_spriteWithoutStar;
	Sprite* m_spriteResting;
	bool m_hasStar;
	std::vector< Tile* > m_path;
	float m_actTimer = 1.f;

	Vector2<int> m_currentPos;
};

