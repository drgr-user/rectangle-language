#pragma once
#include "Tcolor.h"

class Rec {
public:
	int top;
	int left;
	int height;
	int width;
	Tcolor color;
	std::string name;

	int down;
	int right;

	Rec() {}
	Rec(int top, int left, int height, int width, int color, std::string name) {
		this->top = top;
		this->left = left;
		this->height = height;
		this->width = width;
		this->color.color = color;
		this->name = name;
		this->down = top + height - 1;
		this->right = left + width - 1;
	}

};