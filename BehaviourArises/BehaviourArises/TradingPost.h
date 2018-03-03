#pragma once
#include "IEntity.h"
class TradingPost :
	public IEntity
{
public:
	TradingPost();
	~TradingPost();
	void Update(float p_delta) override;
	void Draw() override;


};

