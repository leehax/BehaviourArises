#pragma once
#include "Agent.h"
class Damage :
	public Agent
{
public:
	Damage();
	~Damage();
	void CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent) override;
	void Update(float p_delta) override;
	void Draw() override;
	void Sense() override;
};

