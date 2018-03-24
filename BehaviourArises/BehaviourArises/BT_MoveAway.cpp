#include "stdafx.h"
#include "BT_MoveAway.h"
#include <algorithm>
#include "Agent.h"

BT_MoveAway::BT_MoveAway(std::shared_ptr<BlackBoard> p_BB, Vector2<int> p_posToMoveAwayFrom):BT_Leaf(p_BB)
{
	m_posToMoveAwayFrom = p_posToMoveAwayFrom;
}


BT_MoveAway::~BT_MoveAway()
{
}

BT_Node::BT_State BT_MoveAway::Update()
{
	Vector2<int> direction; //normalize the x and y component individually, instead of normalizing the entire vector, to ensure proper movement
	Vector2<int> myPos = m_blackBoard->GetVector2i(m_agent->GetName() + "Position");
	direction.x = (myPos.x - m_posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - m_posToMoveAwayFrom.x), 1);
	direction.y = (myPos.y - m_posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - m_posToMoveAwayFrom.y), 1);

	Vector2<int> targetPos = myPos + direction;

	m_agent->ClearPath();
	if (m_agent->FindPath(targetPos))
	{
		//m_blackBoard->SetVector2i(m_agent->GetName() + "TargetPosition", targetPos);
		m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
		std::cout << m_agent->GetName() + " Move Away Success\n";
		return BT_State::Success;
	}
	
	direction = m_blackBoard->GetVector2i(m_agent->GetName() + "PreviousEscapeDirection");
	targetPos = myPos + direction;

	m_agent->ClearPath();
	if (m_agent->FindPath(targetPos))
	{
		m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
		std::cout << m_agent->GetName() + " Move Away Success\n";
		return BT_State::Success;
	}

	if (direction.x != 0 && direction.y != 0)//enemy pos is diagonal to us
	{
		

		direction.x = 0;
		direction.y = (myPos.y - m_posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - m_posToMoveAwayFrom.y), 1);
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos))
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			std::cout << m_agent->GetName() + " Move Away Success\n";
			return BT_State::Success;
		}

		direction.x = (myPos.x - m_posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - m_posToMoveAwayFrom.x), 1);
		direction.y = 0;
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos))
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			std::cout << m_agent->GetName() + " Move Away Success\n";
			return BT_State::Success;
		}

		direction.x = (myPos.x - m_posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - m_posToMoveAwayFrom.x), 1);
		direction.y = -(myPos.y - m_posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - m_posToMoveAwayFrom.y), 1);
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos))
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			std::cout << m_agent->GetName() + " Move Away Success\n";
			return BT_State::Success;
		}

		direction.x = -(myPos.x - m_posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - m_posToMoveAwayFrom.x), 1);
		direction.y = (myPos.y - m_posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - m_posToMoveAwayFrom.y), 1);
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos))
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			std::cout << m_agent->GetName() + " Move Away Success\n";
			return BT_State::Success;
		}


		direction.x = 0;
		direction.y = -(myPos.y - m_posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - m_posToMoveAwayFrom.y), 1);
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos))
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			std::cout << m_agent->GetName() + " Move Away Success\n";
			return BT_State::Success;
		}

		direction.x = -(myPos.x - m_posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - m_posToMoveAwayFrom.x), 1);
		direction.y = 0;
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos))
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			std::cout << m_agent->GetName() + " Move Away Success\n";
			return BT_State::Success;

		}
	}

	else //enemy pos is orthogonal to us
	{
		if(direction.x!=0) //horizontal
		{
			direction.x = (myPos.x - m_posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - m_posToMoveAwayFrom.x), 1);
			direction.y = 1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}

			direction.x = (myPos.x - m_posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - m_posToMoveAwayFrom.x), 1);
			direction.y = -1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}

			direction.x = 0;
			direction.y = 1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}

			direction.x = 0;
			direction.y = -1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}

			direction.x = -(myPos.x - m_posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - m_posToMoveAwayFrom.x), 1);
			direction.y = 1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}

			direction.x = -(myPos.x - m_posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - m_posToMoveAwayFrom.x), 1);
			direction.y = -1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}


		}
		else //vertical
		{
			direction.x = 1;
			direction.y = (myPos.y - m_posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - m_posToMoveAwayFrom.y), 1);
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}

			direction.x = -1;
			direction.y = (myPos.y - m_posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - m_posToMoveAwayFrom.y), 1);
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}

			direction.x = 1;
			direction.y = 0;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}

			direction.x = -1;
			direction.y = 0;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}

			direction.x = 1;
			direction.y = -(myPos.y - m_posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - m_posToMoveAwayFrom.y), 1);
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}

			direction.x = -1;
			direction.y = -(myPos.y - m_posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - m_posToMoveAwayFrom.y), 1);
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos))
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				std::cout << m_agent->GetName() + " Move Away Success\n";
				return BT_State::Success;
			}
		}
	}



	std::cout << m_agent->GetName()+" Move Away Fail\n";
	return BT_State::Running;
}

