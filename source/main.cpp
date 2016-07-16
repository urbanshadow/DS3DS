/*

*/
#include <3ds.h>
#include <stdio.h>
#include "Scene.h"
#include "Game.h"
#include "Citro3dManager.h"

int main(int argc, char **argv)
{
	// Initialize graphics
	Citro3dManager gfxman;

	// Create scene
	Game g;
	
	// Play!
	return gfxman.PlayScene(&g);
}