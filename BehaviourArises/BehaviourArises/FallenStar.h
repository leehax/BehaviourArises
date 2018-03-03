#pragma once
#include "IEntity.h"

class FallenStar:public IEntity
{
public:
	FallenStar();
	~FallenStar();

	void Update(float p_delta) override;
	void Draw() override;

	void Hide(bool p_val);
private: 
	bool m_hidden = false;

};

