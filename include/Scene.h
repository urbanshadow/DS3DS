#ifndef SCENE_H
#define SCENE_H

#include <citro3d.h>

class Scene{
	public:
		virtual int GetStatus() = 0;
		virtual void RenderTop(C3D_MtxStack, C3D_MtxStack, float) = 0;
		virtual void RenderBot(C3D_MtxStack, C3D_MtxStack) = 0;
		virtual void Logic() = 0;
};

#endif