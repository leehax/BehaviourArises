#include "stdafx.h"
#include "FiniteStateMachine.h"


FiniteStateMachine::FiniteStateMachine()
{
}


FiniteStateMachine::~FiniteStateMachine()
{
}

void FiniteStateMachine::SetState(const std::string p_name)
{
	
	assert(m_states.find(p_name)!=m_states.end()&&"Target State Not Found"); 
	if(m_activeState)
	{
		m_activeState->Exit();
	}
	m_activeState = m_states[p_name];
	m_activeState->Enter();
}

void FiniteStateMachine::UpdateState(float p_delta)
{
	m_activeState->Update(p_delta);
}

void FiniteStateMachine::AddState(const std::string p_name, IState* p_state)
{
	//add the state to the map if it was not found
	if(m_states.find(p_name)==m_states.end()) 
	{
		p_state->m_name = p_name;
		m_states[p_name] = p_state;
	}
}

void FiniteStateMachine::Destroy()
{
	for(auto s:m_states)
	{
		delete s.second;
		s.second = nullptr;
	}
}

std::string FiniteStateMachine::GetActiveState()
{
	return m_activeState->m_name;
}

