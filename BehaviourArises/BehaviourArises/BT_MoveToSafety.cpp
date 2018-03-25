#include "stdafx.h"
#include "BT_MoveToSafety.h"
#include <algorithm>
#include "Agent.h"

BT_MoveToSafety::BT_MoveToSafety(std::shared_ptr<BlackBoard> p_BB, const std::string p_posToMoveAwayFromName):BT_Leaf(p_BB)
{
	m_posToMoveAwayFromName = p_posToMoveAwayFromName;
}


BT_MoveToSafety::~BT_MoveToSafety()
{
}

BT_Node::BT_State BT_MoveToSafety::Update()
{
	Vector2<int> direction; //normalize the x and y component individually, instead of normalizing the entire vector, to ensure proper movement
	Vector2<int> myPos = m_blackBoard->GetVector2i(m_agent->GetName() + "Position");
	Vector2<int> posToMoveAwayFrom = m_blackBoard->GetVector2i(m_posToMoveAwayFromName);
	direction.x = (myPos.x - posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - posToMoveAwayFrom.x), 1);
	direction.y = (myPos.y - posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - posToMoveAwayFrom.y), 1);

	Vector2<int> targetPos = myPos + direction;
	m_agent->ClearPath();

	if (m_agent->FindPath(targetPos)&&targetPos!=posToMoveAwayFrom) //flee 
	{

		m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
		return BT_State::Success;
	}
	
	if (m_agent->GetName() != "Tank") //flee towards tank if the first option is blocked
	{
		direction.x = (m_blackBoard->GetVector2i("TankPosition").x - myPos.x) / std::max(std::abs(m_blackBoard->GetVector2i("TankPosition").x - myPos.x), 1);
		direction.y = (m_blackBoard->GetVector2i("TankPosition").y - myPos.y) / std::max(std::abs(m_blackBoard->GetVector2i("TankPosition").y - myPos.y), 1);
		targetPos = myPos + direction;
		if (targetPos != posToMoveAwayFrom) {

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			
				return BT_State::Success;
			}
		}
	}

	//flee in the previousescape direction 
	direction = m_blackBoard->GetVector2i(m_agent->GetName() + "PreviousEscapeDirection");
	targetPos = myPos + direction;

	m_agent->ClearPath();
	if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
	{
		m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);

		return BT_State::Success;
	}

	//if above options were all blocked, try every direction until one succeeds
	if (direction.x != 0 && direction.y != 0)//enemy pos is diagonal to us
	{
		

		direction.x = 0;
		direction.y = (myPos.y - posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - posToMoveAwayFrom.y), 1);
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			
			return BT_State::Success;
		}

		direction.x = (myPos.x - posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - posToMoveAwayFrom.x), 1);
		direction.y = 0;
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
	
			return BT_State::Success;
		}

		direction.x = (myPos.x - posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - posToMoveAwayFrom.x), 1);
		direction.y = -(myPos.y - posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - posToMoveAwayFrom.y), 1);
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			
			return BT_State::Success;
		}

		direction.x = -(myPos.x - posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - posToMoveAwayFrom.x), 1);
		direction.y = (myPos.y - posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - posToMoveAwayFrom.y), 1);
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
		
			return BT_State::Success;
		}


		direction.x = 0;
		direction.y = -(myPos.y - posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - posToMoveAwayFrom.y), 1);
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
		
			return BT_State::Success;
		}

		direction.x = -(myPos.x - posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - posToMoveAwayFrom.x), 1);
		direction.y = 0;
		targetPos = myPos + direction;

		m_agent->ClearPath();
		if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
		{
			m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
		
			return BT_State::Success;

		}
	}

	else //enemy pos is orthogonal to us
	{
		if(direction.x!=0) //horizontal
		{
			direction.x = (myPos.x - posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - posToMoveAwayFrom.x), 1);
			direction.y = 1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
		
				return BT_State::Success;
			}

			direction.x = (myPos.x - posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - posToMoveAwayFrom.x), 1);
			direction.y = -1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			
				return BT_State::Success;
			}

			direction.x = 0;
			direction.y = 1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			
				return BT_State::Success;
			}

			direction.x = 0;
			direction.y = -1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
		
				return BT_State::Success;
			}

			direction.x = -(myPos.x - posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - posToMoveAwayFrom.x), 1);
			direction.y = 1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			
				return BT_State::Success;
			}

			direction.x = -(myPos.x - posToMoveAwayFrom.x) / std::max(std::abs(myPos.x - posToMoveAwayFrom.x), 1);
			direction.y = -1;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
	
				return BT_State::Success;
			}


		}
		else //vertical
		{
			direction.x = 1;
			direction.y = (myPos.y - posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - posToMoveAwayFrom.y), 1);
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
			
				return BT_State::Success;
			}

			direction.x = -1;
			direction.y = (myPos.y - posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - posToMoveAwayFrom.y), 1);
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				
				return BT_State::Success;
			}

			direction.x = 1;
			direction.y = 0;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				return BT_State::Success;
			}

			direction.x = -1;
			direction.y = 0;
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);

				return BT_State::Success;
			}

			direction.x = 1;
			direction.y = -(myPos.y - posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - posToMoveAwayFrom.y), 1);
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				
				return BT_State::Success;
			}

			direction.x = -1;
			direction.y = -(myPos.y - posToMoveAwayFrom.y) / std::max(std::abs(myPos.y - posToMoveAwayFrom.y), 1);
			targetPos = myPos + direction;

			m_agent->ClearPath();
			if (m_agent->FindPath(targetPos) && targetPos != posToMoveAwayFrom)
			{
				m_blackBoard->SetVector2i(m_agent->GetName() + "PreviousEscapeDirection", direction);
				
				return BT_State::Success;
			}
		}
	}




	return BT_State::Running;
}

