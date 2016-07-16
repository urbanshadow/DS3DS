#ifndef GAME_H
#define GAME_H

#include <citro3d.h>
#include "Scene.h"
#include "Globals.h"
#include "kitten_bin.h"
#include "grass_bin.h"

class Game : public Scene{
	private:
		C3D_Tex kitten_tex, grass_tex;
		int status;
	public:
		Game();
		~Game();
		void RenderTop(C3D_MtxStack, C3D_MtxStack, float);
		void RenderBot(C3D_MtxStack, C3D_MtxStack);
		int GetStatus();
		void Logic();
};

#endif