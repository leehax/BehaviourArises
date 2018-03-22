#pragma once
#include "Agent.h"
class Ranger :
	public Agent
{
public:
	Ranger();
	~Ranger();
	void CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent) override;
	void Update(float p_delta) override;
	void Draw() override;
	void Sense() override;
};

