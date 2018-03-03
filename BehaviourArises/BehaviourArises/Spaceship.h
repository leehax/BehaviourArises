#pragma once
#include "IEntity.h"
class Spaceship :
	public IEntity
{
public:
	Spaceship();
	~Spaceship();
	void Update(float p_delta) override;
	void Draw() override;

};

