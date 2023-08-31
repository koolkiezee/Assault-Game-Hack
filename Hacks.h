#ifndef Hacks_H
#define Hacks_H

#include <windows.h>
#include "Offsets.h"

#include <iostream>
#include <GL/GL.h>
#include "Classes.h"
#include "ExtraFunctions.h"

#pragma comment(lib, "OPENGL32.lib")

void OnRenderFrame();
void OnInitialize();

struct Color32
{
	Color32(float pR, float pG, float pB, float pA)
	{
		this->r = pR;
		this->g = pG;
		this->b = pB;
		this->a = pA;
	}

	float r;
	float g;
	float b;
	float a;
};

void DrawRect(int x, int y, int x2, int y2, Color32 color, bool bFilled = true);
void DrawLine(int x, int y, int x2, int y2, float width, Color32 color);
void DrawHealthBar(int x, int y, int w, int h, float health, Color32 color);

#endif