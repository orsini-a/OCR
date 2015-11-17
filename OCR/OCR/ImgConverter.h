#pragma once

#include "EasyBMP.h"
using namespace std;

class ImgConverter
{
	int sizeX;
	int sizeY;
	int divX;
	int divY;
	BMP Input;
	char *temp;
	std::string folder;
public:
	ImgConverter(int imgx, int imgy, int imgSubX, int imgSubY);
	~ImgConverter();

	void Greyscale(char *);
	float *parse(char *);
};

