/**
*
**/
#include "Citro3dManager.h"

Citro3dManager::Citro3dManager()
{
	InitializeHW();
	InitializeWorld();
}

Citro3dManager::~Citro3dManager()
{
	// Unload the vertex shader on destruction
	shaderProgramFree(&shader);
	DVLB_Free(vshader);

	// Unload the graphics framework
	C3D_Fini();
	gfxExit();
}

void Citro3dManager::InitializeHW()
{
	gfxInitDefault();
	// 3D is supported and wanted, so this is ON
	gfxSet3D(STEREOSCOPY_ON);

#ifdef DEBUG
	consoleInit(GFX_BOTTOM, NULL);
#endif

	// Initialize the render buffers
	C3D_RenderBufInit(&rbTop, TOPSCR_WIDTH, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderBufInit(&rbBot, 240, 320, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	rbTop.clearColor = CLEAR_COLOR;
	rbBot.clearColor = CLEAR_COLOR;

	//Initialize library
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

	MtxStack_Init(&projection);
	MtxStack_Bind(&projection, GPU_VERTEX_SHADER, VSH_FVEC_projMtx, VSH_ULEN_projMtx);
	MtxStack_Init(&modelview);
	MtxStack_Bind(&modelview, GPU_VERTEX_SHADER, VSH_FVEC_mdlvMtx, VSH_ULEN_mdlvMtx);
}

void Citro3dManager::InitializeWorld()
{
	// Load the vertex shader
	vshader = DVLB_ParseFile((u32*)test_vsh_shbin, test_vsh_shbin_size);
	shaderProgramInit(&shader);
	shaderProgramSetVsh(&shader, &vshader->DVLE[0]);
	C3D_BindProgram(&shader);

	// Configure attributes
	C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
	AttrInfo_Init(attrInfo);
	AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // position
	AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2); // texcoord
	AttrInfo_AddLoader(attrInfo, 2, GPU_FLOAT, 3); // vertex color
	
	// Clear buffers
	C3D_RenderBufClear(&rbTop);
	C3D_RenderBufClear(&rbBot);
}

int Citro3dManager::PlayScene(Scene *s)
{
	float slider,czDist;

	while(s->GetStatus() >= 0)
	{
		// Get 3D slider state each tick
		slider = osGet3DSliderState();
		czDist = Z_3DDIST*slider/2;

		// Give a chance to consume cpu to the rest of the code!
		s->Logic();

		C3D_VideoSync();
		
		C3D_RenderBufBind(&rbTop);
			s->RenderTop(projection, modelview, -czDist);
		C3D_Flush();
		C3D_RenderBufTransfer(&rbTop, (u32*)gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL), TOPSCR_COPYFLAG);
		
		// We skip rendering and copying the stereographic pair if the 3D slider is off
		if (slider > 0.0f)
		{
			C3D_RenderBufClear(&rbTop);
			C3D_RenderBufBind(&rbTop);
				s->RenderTop(projection, modelview, +czDist);
			C3D_Flush();
			C3D_RenderBufTransfer(&rbTop, (u32*)gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL), TOPSCR_COPYFLAG);
		}
		
		C3D_RenderBufClear(&rbTop);

// We skip rendering bottom screen frames if the game is in debug mode.
#ifndef DEBUG
		C3D_RenderBufBind(&rbBot);
			s->RenderBot(projection, modelview);
		C3D_Flush();
		C3D_RenderBufTransfer(&rbBot, (u32*)gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL), 0x1000);
		C3D_RenderBufClear(&rbBot);
#endif
		
	}

	return s->GetStatus();
}