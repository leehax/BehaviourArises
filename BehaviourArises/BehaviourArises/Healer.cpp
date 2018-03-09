#include "stdafx.h"
#include "Healer.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "ServiceLocator.h"
#include "Tile.h"
#include "BehaviourTree.h"
#include "AStarPath.h"
#include "BlackBoard.h"
#include <iostream>

BT_Node::BT_State BT_MoveTo::Update()
{
	//Pathfinding
	//

}

Healer::Healer(IGridMap* p_world, Tile* p_tile)
{
	m_visionRange = 5;
	m_maxHealth = 100.f;
	m_currentHealth = 100.f;

	m_curTile = p_tile;

	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../External/textures/Healer.png", 0, 0, 32, 32);

	m_world = p_world;
	m_pathFinding = std::make_shared<AStarPath>(m_world);

}


Healer::~Healer()
{
}

void Healer::CreateBehaviourTree()
{
	m_behaviourTree = std::make_shared<BehaviourTree>();

	auto selector0 = std::make_shared<BT_Selector>();
	auto selector1 = std::make_shared<BT_Selector>();
	auto selector2 = std::make_shared<BT_Selector>();

	auto sequencer0 = std::make_shared<BT_Sequencer>();
	auto sequencer1 = std::make_shared<BT_Sequencer>();
	auto sequencer2 = std::make_shared<BT_Sequencer>();
	auto sequencer3 = std::make_shared<BT_Sequencer>();

	auto walkToDoor = std::make_shared<BT_Leaf>("Walk To Door",100);
	auto openDoor1 = std::make_shared<BT_Leaf>("Open Door",15);
	auto unlockDoor = std::make_shared<BT_Leaf>("Unlock Door",25);
	auto openDoor2 = std::make_shared<BT_Leaf>("Open door after unlocking",90);
	auto smashDoor = std::make_shared<BT_Leaf>("Smash Door",60);
	auto walkThroughDoor = std::make_shared<BT_Leaf>("Walk Through Door",100);
	auto closeDoor = std::make_shared<BT_Leaf>("Close Door",100);
	auto walkToWindow = std::make_shared<BT_Leaf>("Walk To Window",100);
	auto openWindow1 = std::make_shared<BT_Leaf>("Open Window",50);
	auto unlockWindow = std::make_shared<BT_Leaf>("Unlock Window", 40);
	auto openWindow2 = std::make_shared<BT_Leaf>("Open Window After Unlocking it",85);
	auto smashWindow = std::make_shared<BT_Leaf>("Smash window",95);
	auto climbThroughWindow = std::make_shared<BT_Leaf>("Climb Through Window",85);
	auto closeWIndow = std::make_shared<BT_Leaf>("Close Window",100);

	m_behaviourTree->SetRoot(selector0);

	selector0->AddNodesAsChildren({ sequencer0, sequencer2 });
	sequencer0->AddNodesAsChildren({ walkToDoor,selector1,walkThroughDoor,closeDoor });
	selector1->AddNodesAsChildren({ openDoor1, sequencer1, smashDoor });
	sequencer1->AddNodesAsChildren({ unlockDoor, openDoor2 });
	sequencer2->AddNodesAsChildren({ walkToWindow, selector2,climbThroughWindow,closeWIndow });
	selector2->AddNodesAsChildren({ openWindow1, sequencer3,smashWindow });
	sequencer3->AddNodesAsChildren({ unlockWindow, openWindow2 });
	
}

void Healer::Update(float p_delta)
{
}

void Healer::Draw()
{
	m_drawManager->Draw(m_sprite, m_curTile->GetWorldPos().x, m_curTile->GetWorldPos().y ,1);
}

void Healer::Sense()
{
}
