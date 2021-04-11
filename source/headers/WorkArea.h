#pragma once
#include "Tcolor.h"

class WorkArea {
public:
	int height;
	int width;
	Tcolor color;
	Tcolor** matrice;

	WorkArea() {}
	WorkArea(int height, int width, int color) {
		this->height = height;
		this->width = width;
		this->color.color = color;

		matrice = new Tcolor*[height];
		for (int i = 0; i < height; i++)
			matrice[i] = new Tcolor[width];

	}
};