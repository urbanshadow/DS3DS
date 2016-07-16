#include "Game.h"

Game::Game()
{
	status = 0;

	//Texture loading code
	C3D_TexInit(&kitten_tex, 64, 64, GPU_RGBA8);
	C3D_TexUpload(&kitten_tex, kitten_bin);
	C3D_TexSetFilter(&kitten_tex, GPU_LINEAR, GPU_NEAREST);

	C3D_TexInit(&grass_tex, 64, 64, GPU_RGBA8);
	C3D_TexUpload(&grass_tex, grass_bin);
	C3D_TexSetFilter(&grass_tex, GPU_LINEAR, GPU_NEAREST);
}

Game::~Game()
{
	//Texture cleanup
	C3D_TexDelete(&kitten_tex);
	C3D_TexDelete(&grass_tex);
}

int Game::GetStatus()
{
	return status;
}

void Game::RenderTop(C3D_MtxStack projection, C3D_MtxStack modelview, float czDist)
{
	C3D_TexBind(0, &kitten_tex);

	C3D_TexEnv* env = C3D_GetTexEnv(0);
	C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR, 0);
	C3D_TexEnvOp(env, C3D_Both, 0, 0, 0);
	C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);

	// Isometric perspective for top screen
	Mtx_PerspTilt(MtxStack_Cur(&projection), C3D_Angle(FOVY), C3D_AspectRatioTop, 0.01f, 1000.0f);
	Mtx_Identity(MtxStack_Cur(&modelview));
	Mtx_Translate(MtxStack_Cur(&modelview), 0.0f + czDist, 0.0f, -2.0f);
	Mtx_RotateX(MtxStack_Cur(&modelview), -(M_PI/6), true);
	Mtx_RotateY(MtxStack_Cur(&modelview), M_PI/4, true);
	
	MtxStack_Update(&projection);
	MtxStack_Update(&modelview);

	// Inmediate demo code!
	C3D_ImmDrawBegin(GPU_TRIANGLES);
		// First triangle
		C3D_ImmSendAttrib(-0.5f, -0.5f, -0.5f, 0.0f); // v0=position
		C3D_ImmSendAttrib(0.0f, 0.0f, 0.0f, 0.0f); // v2=texcoord
		C3D_ImmSendAttrib(1.0f, 1.0f, 1.0f, 0.0f); // v3=color

		C3D_ImmSendAttrib(+0.5f, -0.5f, -0.5f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 0.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 1.0f, 0.0f);

		C3D_ImmSendAttrib(+0.5f, +0.5f, -0.5f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 1.0f, 0.0f);
		// Second triangle
		C3D_ImmSendAttrib(+0.5f, +0.5f, -0.5f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 1.0f, 0.0f);

		C3D_ImmSendAttrib(-0.5f, +0.5f, -0.5f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 1.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 1.0f, 0.0f);

		C3D_ImmSendAttrib(-0.5f, -0.5f, -0.5f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 0.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 1.0f, 0.0f);
	C3D_ImmDrawEnd();

	// Draw the triangle directly
	C3D_ImmDrawBegin(GPU_TRIANGLES);
		// First triangle
		C3D_ImmSendAttrib(+0.5f, -0.5f, -0.5f, 0.0f); // v0=position
		C3D_ImmSendAttrib(0.0f, 0.0f, 0.0f, 0.0f); // v2=texcoord
		C3D_ImmSendAttrib(-1.0f, 0.0f, 0.0f, 0.0f); // v3=color

		C3D_ImmSendAttrib(+0.5f, -0.5f, +0.5f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 0.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(-1.0f, 0.0f, 0.0f, 0.0f);

		C3D_ImmSendAttrib(+0.5f, +0.5f, +0.5f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(-1.0f, 0.0f, 0.0f, 0.0f);
		// Second triangle
		C3D_ImmSendAttrib(+0.5f, +0.5f, +0.5f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(-1.0f, 0.0f, 0.0f, 0.0f);

		C3D_ImmSendAttrib(+0.5f, +0.5f, -0.5f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 1.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(-1.0f, 0.0f, 0.0f, 0.0f);

		C3D_ImmSendAttrib(+0.5f, -0.5f, -0.5f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 0.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(-1.0f, 0.0f, 0.0f, 0.0f);
	C3D_ImmDrawEnd();

	C3D_TexBind(0, &grass_tex);

	C3D_ImmDrawBegin(GPU_TRIANGLES);
		// First triangle
		C3D_ImmSendAttrib(-0.5f, -0.5f, -0.5f, 0.0f); // v0=position
		C3D_ImmSendAttrib(0.0f, 0.0f, 0.0f, 0.0f); // v2=texcoord
		C3D_ImmSendAttrib(0.0f, 1.0f, 0.0f, 0.0f); // v3=color

		C3D_ImmSendAttrib(-0.5f, -0.5f, +0.5f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 0.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 1.0f, 0.0f, 0.0f);

		C3D_ImmSendAttrib(+0.5f, -0.5f, +0.5f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 1.0f, 0.0f, 0.0f);
		// Second triangle
		C3D_ImmSendAttrib(+0.5f, -0.5f, +0.5f, 0.0f);
		C3D_ImmSendAttrib(1.0f, 1.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 1.0f, 0.0f, 0.0f);

		C3D_ImmSendAttrib(+0.5f, -0.5f, -0.5f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 1.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 1.0f, 0.0f, 0.0f);

		C3D_ImmSendAttrib(-0.5f, -0.5f, -0.5f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 0.0f, 0.0f, 0.0f);
		C3D_ImmSendAttrib(0.0f, 1.0f, 0.0f, 0.0f);
	C3D_ImmDrawEnd();
}

void Game::RenderBot(C3D_MtxStack projection, C3D_MtxStack modelview)
{
	RenderTop(projection, modelview, 0.0f);
}

void Game::Logic()
{
	//Scan all the inputs
	hidScanInput();

	u32 kDown = hidKeysHeld();
	/*if(kDown & KEY_UP)
		rotation[0] -= M_PI / 180;
	if(kDown & KEY_DOWN)
		rotation[0] += M_PI / 180;
	if(kDown & KEY_LEFT)
		rotation[1] -= M_PI / 180;
	if(kDown & KEY_RIGHT)
		rotation[1] += M_PI / 180;
	if(kDown & KEY_A)
		position[2] += 0.05f;
	if(kDown & KEY_B)
		position[2] -= 0.05f;*/
	if(kDown & KEY_START)
		status = -1;
}