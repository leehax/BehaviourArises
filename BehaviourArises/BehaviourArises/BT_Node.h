#pragma once
#include <memory>

class BT_Node
{
public:
	virtual ~BT_Node() {};

	enum class BT_State{ Null, Success, Failure, Running,};

	virtual BT_State Update() = 0;

	bool Succeeded();
	bool Failed();
	bool IsRunning();
	bool Stopped();

	void Reset();

protected:
	BT_State m_state = BT_State::Null;
	
};

inline bool BT_Node::Succeeded()
{
	return m_state == BT_State::Success;
}

inline bool BT_Node::Failed()
{
	return m_state == BT_State::Failure;
}

inline bool BT_Node::IsRunning()
{
	return m_state == BT_State::Running;
}



inline bool BT_Node::Stopped()
{
	return m_state == BT_State::Success || m_state == BT_State::Failure;
}

inline void BT_Node::Reset()
{
}
