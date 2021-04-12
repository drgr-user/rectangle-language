#include "headers/toojpeg/toojpeg.h" //toojpeg by stephan brumme
#include "headers/Prog.h"
#include"headers/jpeg_generator.h"
#include <fstream>

std::ofstream myFile("RL_out.jpg", std::ios_base::out | std::ios_base::binary);

void myOutput(unsigned char byte){
	myFile << byte;
}

int JpegGenerator(WorkArea wa){

	const auto width = wa.width;
	const auto height = wa.height;

	const auto bytesPerPixel = 3;

	auto image = new unsigned char[width * height * bytesPerPixel];

	for (auto y = 0; y < height; y++)
		for (auto x = 0; x < width; x++)
		{
			auto offset = (y * width + x) * bytesPerPixel;

			image[offset] = wa.matrice[y][x].color;
			image[offset + 1] = wa.matrice[y][x].color;
			image[offset + 2] = wa.matrice[y][x].color;
		}


	const bool isRGB = true;
	const auto quality = 90;
	const bool downsample = false;
	const char* comment = "Rectangle Language";
	auto ok = TooJpeg::writeJpeg(myOutput, image, width, height, isRGB, quality, downsample, comment);

	delete[] image;

	return ok ? 0 : 1;
}