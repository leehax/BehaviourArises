#include "stdafx.h"
#include "StarChaser.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Tile.h"
#include "World.h"
#include "FiniteStateMachine.h"
#include <iostream>
#include <algorithm>


void State_Collect::Enter()
{
	//find star
	m_starChaser.SetTargetTile("FllnStar");
	m_starChaser.RecalculatePath();
}
void State_Sell::Enter()
{
	//find trading post
	m_starChaser.SetTargetTile("TrPost");
	m_starChaser.RecalculatePath();
	m_energy = 100.f;
}
void State_Rest::Enter()
{
	//find ship
	m_starChaser.SetTargetTile("Ship");
	m_starChaser.RecalculatePath();
	m_timeToRest = 1.f;
}

void State_Collect::Update(float p_delta)
{
	
	
	//travel to star
	if (m_starChaser.AtTargetTile()==false)
	{
		m_starChaser.MoveToNextTile();
	}
	
	//once traveled to star -> SetState(sell)
	else if(m_starChaser.AtTargetTile())
	{
		//star picked up, notify world to hide it
		m_starChaser.Notify("PickedUp");
		m_starChaser.SetState("Sell");
		
		
	}
	
}

void State_Sell::Update(float p_delta)
{


	//travel to trading post
	if (m_starChaser.AtTargetTile() == false)
	{
		m_starChaser.MoveToNextTile();
		m_energy -= 10.f;
		//if fatigued ->SetState(rest)
		if (m_energy <= 0.f)
		{
			//star dropped, notify world to move star here
			m_starChaser.Notify("Dropped");
			m_starChaser.SetState("Rest");

			
		}
	}

	//once traveled to -> SetState(collect)
	else if (m_starChaser.AtTargetTile())
	{
		//star sold, notify world to make a new star
		m_starChaser.Notify("Sold");
		m_starChaser.SetState("Collect");

		
	}
}
	

void State_Rest::Update(float p_delta)
{
	

	//travel to ship
	if (m_starChaser.AtTargetTile() == false)
	{
		m_starChaser.MoveToNextTile();
	}

	//once traveled to ship -> Rest()
	else if(m_starChaser.AtTargetTile())
	{

		m_timeToRest -= p_delta*60.f;
		//once rested -> SetState(collect)
		m_starChaser.Notify("Resting");
		
		if(m_timeToRest<=0)
		{
			//find the star where we last dropped it
			m_starChaser.SetState("Collect");
			m_starChaser.Notify("Collecting");
			
		}
	}

	
}
void State_Collect::Exit()
{
}
void State_Sell::Exit()
{
}
void State_Rest::Exit()
{
}
void State_Collect::UpdateTarget()
{
	m_starChaser.SetTargetTile("FllnStar");
}

void State_Sell::UpdateTarget()
{
	m_starChaser.SetTargetTile("TrPost");
}

void State_Rest::UpdateTarget()
{
	m_starChaser.SetTargetTile("Ship");
}

StarChaser::StarChaser(World* p_world) : m_world(p_world), m_JPS(new JPSPath(p_world)), m_AStar(new AStarPath(p_world))
{
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteWithoutStar = m_spriteManager->CreateSprite("../External/textures/StarChaser.png", 0, 0, 32, 32);
	m_spriteWithStar = m_spriteManager->CreateSprite("../External/textures/StarChaserWithStar.png", 0, 0, 32, 32);
	m_spriteResting = m_spriteManager->CreateSprite("../External/textures/StarChaserResting.png", 0, 0, 32, 32);
	m_sprite = m_spriteWithoutStar;
	m_type = "StarChsr";
	
	AddState("Collect", new State_Collect(*this));
	AddState("Sell", new State_Sell(*this));
	AddState("Rest", new State_Rest(*this));

	//m_pathFinding = m_AStar;
}


StarChaser::~StarChaser()
{
	
	delete m_AStar;
	m_AStar = nullptr;
	delete m_JPS;
	m_JPS = nullptr;

	m_pathFinding = nullptr;

	
	m_spriteManager->DeleteSprite(m_spriteWithStar);
	m_spriteWithStar = nullptr;
	m_spriteManager->DeleteSprite(m_spriteWithoutStar);
	m_spriteWithoutStar = nullptr;
	m_spriteManager->DeleteSprite(m_spriteResting);
	m_spriteWithoutStar = nullptr;
	m_sprite = nullptr;

	m_spriteManager = nullptr;
	m_drawManager = nullptr;
	Destroy();

}

void StarChaser::Update(float p_delta)
{	
	m_actTimer -= p_delta;
	if (m_actTimer <= 0) {
		m_actTimer = 1.f;
		UpdateState(p_delta);
	}
}

void StarChaser::Draw()
{
	m_drawManager->Draw(m_sprite, GetWorldPos().x, GetWorldPos().y, 1);
	
	m_pathFinding->Draw();
}


void StarChaser::SetTargetTile(const std::string p_targetEntitityType)
{
	m_targetTile = m_world->GetTileWithEntity(p_targetEntitityType);
}

bool StarChaser::AtTargetTile()
{
	return m_curTile == m_targetTile;
}

void StarChaser::Notify(const std::string p_msg)
{
	if(p_msg=="Collecting")
	{
		m_sprite = m_spriteWithoutStar;
		
	}
	else if(p_msg=="PickedUp")
	{
		m_sprite = m_spriteWithStar;
		m_world->UpdateStarState("PickedUp");

	}
	else if(p_msg=="Sold")
	{
		m_sprite = m_spriteWithoutStar;
		m_world->UpdateStarState("Sold");
	}
	else if(p_msg=="Dropped")
	{
		m_sprite = m_spriteWithoutStar;
		m_world->UpdateStarState("Dropped");
	}
	else if(p_msg=="Resting")
	{
		m_sprite = m_spriteResting;
	}
}


void StarChaser::RecalculatePath()
{
	if (m_pathFinding) {
		ChaserState* state = static_cast<ChaserState*>(m_activeState);
		state->UpdateTarget();

		m_pathFinding->Recalculate();
		if (m_targetTile) {
			m_path = m_pathFinding->FindPath(GetCurrentTile(), m_targetTile);
		}
	}
}

void StarChaser::MoveToNextTile()
{
	if (m_path.empty() == false) {
		if(m_curTile!=m_path.back())
		{
			Vector2<int> direction; //normalize the x and y component individually, instead of normalizing the entire vector, to ensure proper movement
			direction.x = (m_path.back()->GetGridPos().x- m_curTile->GetGridPos().x) / std::max(std::abs(m_path.back()->GetGridPos().x - m_curTile->GetGridPos().x), 1);
			direction.y = (m_path.back()->GetGridPos().y - m_curTile->GetGridPos().y) / std::max(std::abs(m_path.back()->GetGridPos().y - m_curTile->GetGridPos().y), 1);
			m_curTile = m_world->GetTile(m_curTile->GetGridPos() + direction);
		}
		else {
			m_path.pop_back();
		}
	}
}

void StarChaser::TogglePathFindingAlgorithm(const std::string p_name)
{
	if(p_name=="A*")
	{
		m_pathFinding = m_AStar;
		RecalculatePath();
	}
	else if(p_name=="JPS")
	{
		m_pathFinding = m_JPS;
		RecalculatePath();
	}
}



