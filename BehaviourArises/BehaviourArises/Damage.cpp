#include "stdafx.h"
#include "Damage.h"


Damage::Damage()
{
}


Damage::~Damage()
{
}

void Damage::CreateBehaviourTree(std::shared_ptr<Agent> p_sharedPtrToThisAgent)
{	//the dps should have the following behaviors
	//ranged attack
	//melee attack
	//move to cover(behind tank)
	//follow leader
}

void Damage::Update(float p_delta)
{

}

void Damage::Draw()
{
}

void Damage::Sense()
{
}
