// BehaviourArises.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Engine.h"

int main(int argc, char* argv[]) {
	Engine engine;
	engine.Initialise();
	engine.Run();
	engine.Destroy();
	return 0;
}
