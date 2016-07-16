#include <string.h>
#include <3ds.h>
#include <citro3d.h>
#include "Globals.h"
#ifdef DEBUG
#include <stdio.h>
#endif
#include "Scene.h"
#include "test_vsh_shbin.h"
#include "test_vsh.shader.h"

#define EXTENDED_TOPSCR_RESOLUTION

#ifndef EXTENDED_TOPSCR_RESOLUTION
#define TOPSCR_WIDTH 240
#define TOPSCR_COPYFLAG 0x00001000
#else
#define TOPSCR_WIDTH (240*2)
#define TOPSCR_COPYFLAG 0x01001000
#endif

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

#define CLEAR_COLOR 0x00000000

class Citro3dManager
{
private:
	DVLB_s* vshader;
	C3D_RenderBuf rbTop, rbBot;
	C3D_MtxStack projection, modelview;
	shaderProgram_s shader;
	void InitializeHW();
	void InitializeWorld();
public:
	Citro3dManager();
	~Citro3dManager();
	int PlayScene(Scene* s);
};