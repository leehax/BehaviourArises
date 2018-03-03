#pragma once
#include "IState.h"
#include <map>

class FiniteStateMachine
{
public:
	FiniteStateMachine();
	~FiniteStateMachine();
	void SetState(const std::string p_name);
	void UpdateState(float p_delta);
	void AddState(const std::string p_name, IState* p_state);
	void Destroy();
	std::string GetActiveState();
protected:
	std::map<std::string, IState*> m_states;
	IState* m_activeState=nullptr;
};

