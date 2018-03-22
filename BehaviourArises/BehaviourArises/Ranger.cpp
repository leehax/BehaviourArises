#include "stdafx.h"
#include "Ranger.h"


Ranger::Ranger()
{
}


Ranger::~Ranger()
{
}

void Ranger::CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent)
{
	//the dps should have the following behaviors
	//ranged attack
	//melee attack
	//move to cover(behind tank)
	//follow leader
}

void Ranger::Update(float p_delta)
{

}

void Ranger::Draw()
{
}

void Ranger::Sense()
{
}
