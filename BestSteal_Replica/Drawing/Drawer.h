﻿#ifndef DRAWER_H_
#define DRAWER_H_

#include <vector>
#include <map>
#include <d3d9.h>
#include <d3dx9.h>

#include "../AppCommon.h"
#include "../Drawing/DrawingCommon.h"


namespace BestStealReplica {
namespace Drawing {

class IDrawable;

class Drawer {
public:
	/* Static Functions --------------------------------------------------------------------------------- */
	static void Create(HWND hWnd, IDirect3D9* pDirect3D, D3DPRESENT_PARAMETERS* pD3dpp);
	static void Release();
	static UINT16 GetAlphaOnBlinking(int time);
	static bool AddDrawable(IDrawable* pDrawable);
	static void Draw();
	static void Blackout();

private:
	/* Constants ---------------------------------------------------------------------------------------- */
	static const TCHAR* Drawer::MAP_CHIP_FILE_PATH;
	static const TCHAR* Drawer::CHARACTER_FILE_PATH;

	/* Constructor / Destructor ------------------------------------------------------------------------- */
	Drawer();

	/* Functions ---------------------------------------------------------------------------------------- */
	static bool CreateTexture(TextureType textureType);
	static void BeginDraw();
	static void Draw(const DrawingContext& rContext);
	static void EndDraw();

};

}
}

#endif